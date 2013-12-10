#!/bin/bash

function killProcess
{
	ps -ef | grep $1 | grep -v vim | awk '{print $2}' | xargs kill -9		
}

function listAllCommands
{
	echo "---------------------"
	echo "kill - [name] : kill process by name"
	echo "---------------------"
}

case "$1" in
'kill')
	killProcess $2
	;;
*)
	listAllCommands
	;;
esac
