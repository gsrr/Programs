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

case "$1" in
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

function listAllCommands
{
	echo "---------------------"
	echo "kill [name] : kill process by name"
	echo "diskInfo : show information of disk"
	echo "rsync [ip srcPath tgtPath]: test rsync connection"
	echo "---------------------"
}
