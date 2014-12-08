#!/bin/bash

shopt -s expand_aliases
alias get_ret="egrep -ve \"Unknowd Command\" -ve \"input command\""
function getLedInfo
{
	echo "elem led\n \nquit" | java -cp HWMonitorClient.jar:log4j.jar test.ClientTest 2> /dev/null | get_ret
}

function getSlotInfo
{
	echo "elem slot\n \nquit" | java -cp HWMonitorClient.jar:log4j.jar test.ClientTest 2> /dev/null | get_ret
}

function getRole
{
	echo "Role (GPIO pin 11 & 22):"
	echo "8\n22\nq\n" | ./MBCmdTest | grep "read #gpio"
	echo "8\n11\nq\n" | ./MBCmdTest | grep "read #gpio"
}

function getFanInfo
{
	echo "fan info:"
	echo "elem fan\n \nquit" | java -cp HWMonitorClient.jar:log4j.jar test.ClientTest 2> /dev/null | get_ret
	echo ""
	echo "fanc info:"
	echo "elem fanc\n \nquit" | java -cp HWMonitorClient.jar:log4j.jar test.ClientTest 2> /dev/null | get_ret

}

case "$1" in
'fan')
	getFanInfo
	;;
'led')
	getLedInfo
	;;
'slot'):
	getSlotInfo
	;;
'role')
	getRole
	;;
*)
	java -cp HWMonitorClient.jar:log4j.jar test.ClientTest
	;;
esac



