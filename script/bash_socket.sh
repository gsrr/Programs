#!/bin/bash
exec 3<>/dev/tcp/www.yahoo.com.tw/80
echo -e "GET / HTTP/1.0\r\nConnection: close\r\n\r\n" >&3
cat <&3


