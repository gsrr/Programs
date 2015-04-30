#! /bin/ash

# Description: Runs VMWare diskLib nasPlugin sanity test

#
# runTest --
#
#    Runs a disk test utility that returns a disklib error as exit code
#    
#
runTest()
{
   # Run the command
   echo "  >> $1"

   if [ "$#" -lt "3" ] ; then
      $1;
   else 
      $1 > $3
   fi
   
   # Grab return code
   RETCODE=$?

   # Convert to a string
   if [ ${RETCODE} == 0 ]; then
      RETNAME="SUCCESS"
   else
      RETNAME="UNKNOWN"
   fi

   # Verify return code.
   if [ "$RETNAME" = "$2" ]; then
      return 0;
   else
      echo "expected $2 but got $RETNAME($RETCODE)"
      return 1;
   fi
}


#
# runGrep --
#
#    Runs a grep command and prints a message on error
#    
#
runGrep()
{
   # Run the command
   echo "  >> grep $1 $2"

   grep "$1" "$2"

   # Grab return code
   RETCODE=$?

   # Verify return code.
   if [ ${RETCODE} = $3 ]; then
      return 0;
   else
      echo "expected $3 but got $RETCODE"
      return 1;
   fi
}

#
# Write random data to the specified vmdk
#
# writeVMDK <vmdk name> <start %> <length %>
# 
# Note that percent start and length are of the vmdk's capacity
#
writeVMDK()
{
   local filename=$1
   local startPct=$2
   local lenPct=$3

   local extent=`awk -F"\"" '/RW/ {print $2 }' ${filename}`
   local extentBlocks=`awk '/RW/ {print $2 }' ${filename}`
   local CNT=$((${extentBlocks}*512/${DD_BSZ}*${lenPct}/100))
   local SEEK=$((${extentBlocks}*512/${DD_BSZ}*${startPct}/100))

   dd if=/dev/urandom of=${extent} bs=${DD_BSZ} count=${CNT} seek=${SEEK} conv=notrunc

   echo "  Wrote ${filename} of ${extentBlocks} seek=${startPct} pct len=${lenPct} pct"

   return 0;
}

#
# Create a Native snapshot and compare that the data is the same as the source
#
# createNS <source vmdk name> <destination vmdk name> <log file name>
#
createNS()
{
   runTest "vmkfstools -v ${VERB} -I $1 $2" SUCCESS $3 || return 1

   #check that the files are the same
   if [ ${DoCompareFiles} == "yes" ]; then
      local n1=$1
      local n2=$2
      local extent1=`awk -F"\"" '/RW/ {print $2 }' ${n1}`
      local extent2=`awk -F"\"" '/RW/ {print $2 }' ${n2}`
      runTest "diff -q ${extent1} ${extent2}" SUCCESS || return 1
      echo "  Created Native Snapshot $2 from $1 and compared that they have the same data."
   else 
      echo "  Created Native Snapshot $2 from $1."
   fi
   
   return 0;
}

#
# Create a Native Clone and compare that the data is the same as the source
# By default create zeroedthick destination, but it can be overwritten.
#
# createNC <source vmdk name> <destination vmdk name> <status> <alloc type>
#
createNC()
{
   local logfile="createNC.log"
   local status=$3
   local dtype="zeroedthick"

   if [ "$#" == "4" ]; then
      if [ $4 == "thin" ]; then 
         dtype="thin"
      elif [$4 == "eagerzeroedthick"]; then 
         dtype="eagerzeroedthick"
      fi
   fi

   rm -f ${logfile}

   runTest "vmkfstools -v ${VERB} -i $1 -d ${dtype} $2" SUCCESS ${logfile} || return 1

   if [ ${status} == "SUCCESS" ]; then 
      #check that plugin matched
      #runGrep 'Found matching NAS plugin'  ${logfile} 0 || return 1
      #runGrep "Registered plugin \"${PLUGIN_NAME}\"" ${logfile} 0 || return 1
      runGrep "Native clone on destination handle created successfully" ${logfile} 0 || return 1
   else
      runGrep "Failed to create native clone on destination handle" ${logfile} 0 || return 1
   fi     

   #check that the files are the same
   if [ ${DoCompareFiles} == "yes" ]; then
      local n1=$1
      local n2=$2
      local extent1=`awk -F"\"" '/RW/ {print $2 }' ${n1}`
      local extent2=`awk -F"\"" '/RW/ {print $2 }' ${n2}`
      runTest "diff -q ${extent1} ${extent2}" SUCCESS || return 1
      echo "  Created Native Clone $2 from $1 and compared that they have the same data."
   else 
      echo "  Created Native Clone $2 from $1."
   fi
   
   return 0;
}

#
# Obtain extended vmdk stats and verify expected values
#
# xStats <vmdk name>  <expected % used> <expected unshared % min> <expected unshared % max>
#
# Note that expected percents are of the vmdk's capacity. Note that for unshared '
# you specify the exepected range.
#
xStats()
{
   local expUsedPct=$2
   local expUnsharedPctMin=$3
   local expUnsharedPctMax=$4
   local logfile="xStats.log"

   rm -f ${logfile}

   runTest "vmkfstools --extendedstatinfo $1" SUCCESS ${logfile} || return 1

   local capacity=$((`awk '/Capacity/ {print $3}' ${logfile}`))
   local used=$((`awk '/Used/ {print $3}' ${logfile}`))
   local unshared=$((`awk '/Unshared/ {print $3}' ${logfile}`))

   local usedPct=$((${used}*100/${capacity}))
   local unsharedPct=$((${unshared}*100/${capacity}))

   if [ ${PLUGIN_NAME} == "ExampleNasPlugin" ]; then
      # ExampleNasPlugin always returns 100% unshared, so ignore unshared value for it
      expUnsharedPctMin=0
      expUnsharedPctMax=100
   fi   

   if [ ${usedPct} -eq ${expUsedPct} -a ${unsharedPct} -ge ${expUnsharedPctMin} -a ${unsharedPct} -le ${expUnsharedPctMax} ]; then
      echo "  xStat of $1: cap=${capacity} used=${used}/${usedPct} unshared=${unshared}/${unsharedPct}"
      return 0;
   else
      echo "\nError: xStat of $1: cap=${capacity} used=${used}/${usedPct} unshared=${unshared}/${unsharedPct} expected ${expUsedPct}, [${expUnsharedPctMin},${expUnsharedPctMax}]"
      return 1;
   fi
}

#
# Do reserve space tests
# ReserveSpace_tests <vmdk name> <size in MB>
#
ReserveSpace_tests()
{
   local sizeMB=$2
   local base="$1${sizeMB}m"
   local vmdk="${base}.vmdk"
   local thin="thin-${base}.vmdk"
   local logfile="${base}.log"

   echo -e "== Running Space Reserve Tests\n"

   # cleanup before, just in case 
   if [ -e ${thin} ]; then 
      vmkfstools -U ${thin}
   fi

   if [ -e ${vmdk} ]; then 
      vmkfstools -U ${vmdk}
   fi

   rm -f ${logfile} 
  
   echo "Test Reserve 1: Testing Reserve Space - thin"
   runTest "vmkfstools -v ${VERB} -c ${sizeMB}m -d thin ${thin}" SUCCESS ${logfile} || return 1

   xStats ${thin} 0 0 0 || return 1

   writeVMDK ${thin} 0 100 || return 1

   xStats ${thin} 100 100 100 || return 1

   # delete thin vmdk and logfile now
   runTest "vmkfstools -U ${thin}" SUCCESS || return 1
   rm -f ${logfile}

   echo "Test Reserve 2: Testing Reserve Space - zeroedthick"
   runTest "vmkfstools -v ${VERB} -c ${sizeMB}m -d zeroedthick ${vmdk}" SUCCESS ${logfile} || return 1

   xStats ${vmdk} 100 100 100 || return 1

   writeVMDK ${vmdk} 0 100 || return 1

   xStats ${vmdk} 100 100 100 || return 1

   # delete logfile but keep the vmdk
   rm -f ${logfile}

   echo "PASS: Completed all Reserve Space tests."

   return 0;
}

#
# Do Native Snapshot Dry Run tests
# NS_DryRun_tests <vmdk name> <size in MB>
#
NS_DryRun_tests()
{
   local sizeMB=$2
   local base="$1${sizeMB}m"
   local vmdk="${base}.vmdk"
   local snap1="${base}-ns1.vmdk"
   local logfile="${base}-ns1-dry.log"

   if [ ! 'which diskCreate' ] ; then
      echo "== Native Snapshot Dry Run tests won't be run - diskCreate is missing.\n"
      return 0
   fi

  echo -e "== Running Native Snapshot Dry Run Tests\n"

   #base needs to exist
   if [ ! -e ${vmdk} ]; then 
      echo ">> Creating ${vmdk}."
      runTest "vmkfstools -c ${sizeMB}m -d zeroedthick ${vmdk}" SUCCESS || return 1
   fi

   echo "Test NS DryRun 1: Native snap dry run to the same directory"
   runTest "diskCreate -T -n -f ${vmdk} ${snap1}" SUCCESS ${logfile} || return 1

   # Verify that the snap file was not actually created
   runTest "vmkfstools -U ${snap1}" UNKNOWN || return 1

   echo "Test NS DryRun 2: Native snap dry run to a different volume"
   runTest "diskCreate -T -n -f ${vmdk} ${VMFS_DIR}/${snap1}" UNKNOWN ${logfile} || return 1
   runTest "vmkfstools -U ${VMFS_DIR}/${snap1}" UNKNOWN || return 1

   rm -f ${logfile}

   echo "PASS: Completed all NS Dry Run tests."

   return 0;
}

#
# Do Native Snapshot Basic tests (Lazy Clone and Xstats functionality)
# NS_Basic_tests <vmdk name> <size in MB>
#
NS_Basic_tests()
{
   local sizeMB=$2
   local size2MB=$((2*$2))
   local base="$1${sizeMB}m"
   local vmdk="${base}.vmdk"
   local snap1="${base}-ns1.vmdk"
   local snap2="${base}-ns2.vmdk"
   local logfile="${base}.log"
   local N

   echo -e "== Running Native Snapshot Basic Tests\n" 
 
   #base needs to exist
   if [ ! -e ${vmdk} ]; then 
      echo ">> Creating ${vmdk} of ${sizeMB} MB."
      runTest "vmkfstools -c ${sizeMB}m -d zeroedthick ${vmdk}" SUCCESS || return 1
      writeVMDK ${vmdk} 0 100 || return 1
   fi

   # check again that the base is thick
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Basic 1: Create Native ns1 of ${base}."
   createNS ${vmdk} ${snap1} ${logfile} || return 1
   xStats ${snap1} 100 0 0 || return 1

   echo "Test NS Basic 2: Create Native ns2 of ${base}."
   createNS ${vmdk} ${snap2} ${logfile} || return 1
   xStats ${snap2} 100 0 0 || return 1

   echo "Test NS Basic 3:  Write 0%-40% of ns1."  
   writeVMDK ${snap1} 0 40 || return 1
   xStats ${snap1} 100 40 40 || return 1

   echo "Test NS Basic 4:  Punch Zero to ns1."  
   runTest "vmkfstools --punchzero ${snap2}" SUCCESS || return 1
   xStats ${snap1} 100 40 40 || return 1

   echo "Test NS Basic 5:  Delete ns1; write 0%-20% to  ${base}."  
   runTest "vmkfstools -U ${snap1}" SUCCESS || return 1
   xStats ${vmdk} 100 100 100 || return 1
   writeVMDK ${vmdk} 0 20 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Basic 6: Extend Native ns2 to  ${size2MB} MB."
   runTest "vmkfstools --extendvirtualdisk ${size2MB}m ${snap2}" SUCCESS ${logfile} || return 1
   xStats ${snap2} 100 50 50 || return 1

   echo "Test NS Basic 7:  Write 20%-40% of ns2."  
   writeVMDK ${snap2} 20 20 || return 1
   # There are only 20% "new" snap bytes, but there are 70% total unshared bytes
   xStats ${snap2} 100 20 70 || return 1

   echo "Test NS Basic 8:  Delete ns2; write 20%-40% to  ${base}."  
   runTest "vmkfstools -U ${snap2}" SUCCESS || return 1
   xStats ${vmdk} 100 100 100 || return 1
   writeVMDK ${vmdk} 20 20 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Basic 9:  Create 12 Native snapshots; write 20%-30% to them; delete them." 
   for N in $(seq 1 1 12); do 
      local snapN="${base}-ns${N}.vmdk"
      createNS ${vmdk} ${snapN} ${logfile} || return 1
      xStats ${snapN} 100 0 0 || return 1
      writeVMDK ${snapN} 20 10 || return 1
      xStats ${snapN} 100 10 10 || return 1
   done
   xStats ${vmdk} 100 100 100 || return 1
   for N in $(seq 1 1 12); do 
      local snapN="${base}-ns${N}.vmdk"
      runTest "vmkfstools -U ${snapN}" SUCCESS || return 1
   done
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Basic 10: Try Native snap of ${base} to a different volume. Should fail."
   runTest "vmkfstools -v ${VERB} -I ${vmdk}  ${VMFS_DIR}/${snap1}" UNKNOWN ${logfile} || return 1
   runTest "vmkfstools -U ${VMFS_DIR}/${snap1}" UNKNOWN || return 1
                       
   echo "PASS: Completed all NS Basic tests."

   rm -f ${logfile}

   return 0;
}

#
# Do Native Snapshot Chain tests (Lazy Clone and Xstats functionality)
# NS_Chain_tests <vmdk name> <size in MB>
#
NS_Chain_tests()
{
   local sizeMB=$2
   local size2MB=$((2*$2))
   local base="$1${sizeMB}m"
   local vmdk="${base}.vmdk"
   local snap1="${base}-ns1.vmdk"
   local snap2="${base}-ns2.vmdk"
   local snap3="${base}-ns3.vmdk"
   local snap4="${base}-ns4.vmdk"
   local snap5="${base}-ns5.vmdk"
   local snap6="${base}-ns6.vmdk"

   local logfile="${base}.log"

   echo -e "== Running Native Snapshot Chain Tests\n" 
 
   #base needs to exist
   if [ ! -e ${vmdk} ]; then 
      echo ">> Creating ${vmdk} of ${sizeMB} MB."
      runTest "vmkfstools -c ${sizeMB}m -d zeroedthick ${vmdk}" SUCCESS || return 1
      writeVMDK ${vmdk} 0 100 || return 1
   fi

   # check again that the base is thick
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Chain 1: Create ns1 and ns2 of base, extend ns2, and write data to snaps"
   createNS ${vmdk} ${snap1} ${logfile} || return 1
   createNS ${vmdk} ${snap2} ${logfile} || return 1
   writeVMDK ${snap1} 0 40 || return 1
   runTest "vmkfstools --extendvirtualdisk ${size2MB}m ${snap2}" SUCCESS ${logfile} || return 1
   writeVMDK ${snap2} 20 20 || return 1
   xStats ${snap1} 100 40 40 || return 1
   
   xStats ${snap2} 100 20 70 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Chain 2: Create Native ns3 of ns1; write ns3 80%-100%; delete ns3."
   createNS ${snap1} ${snap3} ${logfile} || return 1
   xStats ${snap3} 100 0 0 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   
   writeVMDK ${snap3} 80 20 || return 1
   xStats ${snap3} 100 20 20 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   runTest "vmkfstools -U ${snap3}" SUCCESS || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Chain 3: Create Native ns4 of ns1; write ns4 0%-20%; delete ns4."
   createNS ${snap1} ${snap4} ${logfile} || return 1
   xStats ${snap4} 100 0 0 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   
   writeVMDK ${snap4} 0 20 || return 1
   xStats ${snap4} 100 20 20 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   runTest "vmkfstools -U ${snap4}" SUCCESS || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Chain 4: Create Native ns5 of ns1; write ns5 0%-20%; delete ns1."
   createNS ${snap1} ${snap5} ${logfile} || return 1
   xStats ${snap5} 100 0 0 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   
   writeVMDK ${snap5} 0 20 || return 1
   xStats ${snap5} 100 20 20 || return 1
   xStats ${snap1} 100 40 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   runTest "vmkfstools -U ${snap1}" SUCCESS || return 1
   # Note that here we are not sure is unshared for snap5 is now 20% or 40%
   xStats ${snap5} 100 20 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1

   echo "Test NS Chain 5: Create Native ns6 of ns5; write ns6 80%-100%; delete ns5, ns6."
   createNS ${snap5} ${snap6} ${logfile} || return 1
   xStats ${snap6} 100 0 0 || return 1
   xStats ${snap5} 100 20 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   
   writeVMDK ${snap6} 80 20 || return 1
   xStats ${snap6} 100 20 20 || return 1
   xStats ${snap5} 100 20 40 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   runTest "vmkfstools -U ${snap5}" SUCCESS || return 1
   xStats ${snap6} 100 20 60 || return 1
   xStats ${vmdk} 100 100 100 || return 1
   runTest "vmkfstools -U ${snap6}" SUCCESS || return 1
   xStats ${vmdk} 100 100 100 || return 1

   runTest "vmkfstools -U ${snap2}" SUCCESS || return 1

   echo "Test NS Chain 6: Create Native Chain of "\
        "base->ns1->ns2->ns3->ns4->ns5->ns6->ns7->ns8; Write each; delete all."
   local N
   local snapP=${vmdk}
   for N in $(seq 1 1 8); do 
      local snapN="${base}-ns${N}.vmdk"
      createNS ${snapP} ${snapN} ${logfile} || return 1
      xStats ${snapN} 100 0 0 || return 1
      writeVMDK ${snapN} 50 10 || return 1
      xStats ${snapN} 100 10 10 || return 1
      snapP=${snapN}
   done

   for N in $(seq 1 1 8); do 
      local snapN="${base}-ns${N}.vmdk"
      runTest "vmkfstools -U ${snapN}" SUCCESS || return 1
   done

   xStats ${vmdk} 100 100 100 || return 1

   echo "PASS: Completed all Native Snapshot Chain tests."

   #cleanup
   rm -f ${logfile}

   return 0;
}

#
# Do Native Clone Basic tests
# NC_Basic_tests <vmdk name> <size in MB>
#
NC_Basic_tests()
{
   local sizeMB=$2
   local base="$1${sizeMB}m"
   local vmdk="${base}.vmdk"
   local nc1="${base}-nc1.vmdk"
   local logfile="${base}-nc1.log"

   echo -e "== Running Native Clone Basic Tests\n"

   #base needs to exist
   if [ ! -e ${vmdk} ]; then 
      echo ">> Creating ${vmdk}."
      runTest "vmkfstools -c ${sizeMB}m -d zeroedthick ${vmdk}" SUCCESS || return 1
      writeVMDK ${vmdk} 0 100 || return 1
   fi

   if [ 'which diskCreate' ]; then
      echo "Test NC Basic 1: Native Clone dry run to the same directory."
      runTest "diskCreate -T -C ${vmdk} ${nc1}" SUCCESS ${logfile} || return 1
      runTest "vmkfstools -U ${nc1}" UNKNOWN || return 1
   else
      echo "Test NC Basic 1: Native Clone Dry Run tests won't be run - diskCreate is missing.\n"
      echo "               : Assume that Native Clones are supported on this datastore.\n"
   fi

   echo "Test NC Basic 2: Native clone to the same volume."
   createNC ${vmdk} ${nc1} SUCCESS || return 1
   xStats ${nc1} 100 100 100 || return 1

   echo "Test NC Basic 3: Native clone to the a VMFS volume; should fail-back to non-native clone."
   createNC ${vmdk} ${VMFS_DIR}/${nc1} UNKNOWN
   runTest "vmkfstools -U ${VMFS_DIR}/${nc1}" SUCCESS || return 1

   # Try to clone file to a different NFS dir - should succeed
   if [ -d "${NAS_VOLUME2}" ] ; then
      echo "Test NC Basic 4: Native Clone to a different NFS datastore."
      createNC ${vmdk} ${NAS_DIR2}/${nc1} SUCCESS || return 1
      xStats ${nc1} 100 100 100 || return 1
      runTest "vmkfstools -U ${NAS_DIR2}/${nc1}" SUCCESS || return 1
   else
      echo "Test NC Basic 4: Not testing Native Clone to a different NFS datastore."
   fi

   # cleanup
   runTest "vmkfstools -U ${nc1}" SUCCESS || return 1
   rm -f ${logfile}

   echo "PASS: Completed all Native Clone Basic tests."

   return 0;
}

# Main code

# Fail script on any unchecked error
set -e

#Input:
if [ "$#" -lt "3" ] ; then
   echo "Usage: "
   echo " #nasPlugin-test.sh <nasPluginName> <nasDir1> <vmfsDir> [<nasDir2>] "
   echo "  Where " 
   echo "     <nasPluginName> is the name of the diskLib NAS plugin "
   echo "     <nasDir1> is test directory on a NAS datastore "
   echo "     <vmfsDir> is a test directory on a VMFS datastore "
   echo "     <nasDir2> is a test directory on a second NAS datastore on the "
   echo "               same NAS server for cross-datastore clone tests."
   return 1
fi

#File and directory names
TEST_DIR="nasPluginTest"

PLUGIN_NAME=$1
NAS_VOLUME2=$4
NAS_DIR=$2/$TEST_DIR
VMFS_DIR=$3/$TEST_DIR
NAS_DIR2=$4/$TEST_DIR

# Block size used for dd
DD_BSZ=4096
MB=1024*1024

#Test file sizes in MB
TF1_SZM=100

#Verbosity for vmkfstools 
VERB=20

#Compare file flag
DoCompareFiles=yes

# Prepare test directories and files

# create test vmdk and fill it with random data
if [ ! -d "${NAS_DIR}" ] ; then
   echo " ${NAS_DIR} does not exit; creating it"
   mkdir "${NAS_DIR}"
fi 

if [ ! -d "${VMFS_DIR}" ] ; then
   echo " ${VMFS_DIR} does not exit; creating it"
   mkdir "${VMFS_DIR}"
fi 

if [ -d "${NAS_VOLUME2}" ] ; then
   if [ ! -d "${NAS_DIR2}" ] ; then
      echo " ${NAS_DIR2} does not exit; creating it"
      mkdir "${NAS_DIR2}"
   fi

   rm -f ${NAS_DIR2}/*
   # */
fi 

if [ ! -d "${NAS_DIR}" ] ; then
   echo "Unable to create ${NAS_DIR} directory"
   return 1
fi 

if [ ! -d "${VMFS_DIR}" ] ; then
   echo "Unable to create $VMFS directory"
   return 1
fi 
 
cd "${NAS_DIR}"

# cleanup old files 
rm -f *
rm -f "${VMFS_DIR}"/*
# */

#check that NAS VAAI is supported on this data store
runTest "vmkfstools -v ${VERB} -P ${NAS_DIR}" SUCCESS support.log || return 1
runGrep "VAAI Supported: YES" support.log 0 || return 1


ReserveSpace_tests "rstest" ${TF1_SZM}
NS_DryRun_tests "nsdrtest" ${TF1_SZM}
NS_Basic_tests "nsbase" ${TF1_SZM}
NS_Chain_tests "nschain" ${TF1_SZM}
NC_Basic_tests "ncbase" ${TF1_SZM}

echo "End of testing"


