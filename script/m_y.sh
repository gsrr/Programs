#!/bin/bash

function killProcess
{
	ps -ef | grep $1 | grep -v vim | awk '{print $2}' | xargs kill -9		
}


function showDiskInfo
{
	echo "-----Available disks-----"
	echo | format -e
	echo
	echo "-----Configuration of disks-----"
	cfgadm | grep disk
	echo
}

function testRsyncConnection
{
	echo "-----ping test-----"
	ping $1 5
	echo
	echo "-----rsh connection test-----"
	rsh $1 "ift zfs list"
	echo
	echo "-----ssh connection test-----"
	ssh admin@$1
	echo
	echo "-----rsync dry run test-----"
	rsync -nvv "$2" admin@$1:"$3"
	echo
}


function errorMessage
{
	echo "parameter error"
	echo
}

function checkDiskStatus
{
	echo "-----Disk smart result-----"
	python /var/apache/tomcat/webapps/NAS/WEB-INF/python/setup/checkDiskSmart.py disk $1
	echo 
	read -p "show smart information?(Y/n):" ans
	
	if [ $ans == 'y' ];then
		echo "-----Disk smart information-----"
		python /var/apache/tomcat/webapps/NAS/WEB-INF/python/disk/smart.py $1 | more
	fi
	echo
}

function setStaticIP
{
	
	echo "-----set ip-----"
	echo "-----set netmask(broadcast)-----"
	echo "-----add router in Routing table-----"
	route add $1 $2
	echo
}

#---------------------------------------------------
# Description: Reload the library of HA Server
# Example: reloadHALibrary RROperation
#---------------------------------------------------
function reloadHALibrary
{
	python /var/apache/tomcat/webapps/NAS/misc/HAAgent/testHA.py 99 $1
}

function doRR
{
	echo ""
}

#---------------------------------------------------
# Description: Set the color of terminal
# Example: setColor
#---------------------------------------------------
function setColor
{
	#use source to execute
	echo "-----color setting-----"
	export TERM=xterm-color
}


#---------------------------------------------------
# Description: Get total size of a directory
# Example: getDirectorySize /Pool-1/folder
#---------------------------------------------------
function getDirectorySize
{
	echo "-----get directory size-----"
	du -s $1
	echo
}


function createFile
{
	echo "-----createFile-----"
	read -p "directory number:" d_num
	read -p "file number:" f_num
	read -p "file size:" f_size
	read -p "directory path:" d_path
	for i in `seq 1 1 $d_num`
	do	
		destination=$d_path"dir_"$i
		mkdir $destination
		for j in `seq 1 1 $f_num`
		do
			dd if=/dev/urandom of=$destination"/file_"$j bs=$f_size count=1
		done
	done
}

function listAllCommands
{
	echo "---------------------"
	echo "kill [name] : kill process by name"
	echo "diskInfo : show information of disk"
	echo "rsync [ip srcPath tgtPath]: test rsync connection"
	echo "setStaticIP"
	echo "reload [libraryName]"
	echo "---------------------"
}

case "$1" in
'createFile')
	createFile
	;;
'color')
	setColor
	;;
'RR')
	doRR
	;;
'reload')
	reloadHALibrary $1
	;;
'setStaticIP')
	setStaticIP
	;;
'smart')
	checkDiskStatus $2
	;;
'kill')
	killProcess $2
	;;
'disk')
	showDiskInfo
	;;
'rsync')
	if [ $# -ne 4 ];then
		errorMessage
		exit 1
	fi
	testRsyncConnection $2
	;;
*)
	listAllCommands
	;;
esac

