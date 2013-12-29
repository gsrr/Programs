#!bin/bash

function myGitPull
{
	git fetch --all
	git reset --hard origin/master
}

case $1 in
'pull')
	myGitPull
	;;
*)
	echo "command error"
	;;
esac
