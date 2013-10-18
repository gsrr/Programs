#!bin/sh

function transformAll 
{
	find $1 -type f > files

	while read file_name
	do
		echo $file_name
		dos2unix $file_name $file_name
	done<files
	rm -f files
}

function transformFolder 
{
	find $1 -type f > files

	while read file_name
	do
		echo $file_name
		dos2unix $file_name $file_name
	done<files

	rm -f files

	cd $1
	make clean
	make
}

case "$1" in
'All')
	transformAll $2
	;;
'Folder')
	transformFolder $2
	;;
*)
	echo "script option path"
	;;
esac

