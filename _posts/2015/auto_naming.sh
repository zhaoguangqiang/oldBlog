#!/bin/sh

myvalue="$1"
mydate="$(date +%Y-%m-%d)"
myfile="$mydate-$myvalue.markdown"

if [ ! -n "$myvalue" ];then
    echo "file name is null"
    exit 0;
fi

if [ ! -f "$myfile" ];then
    touch "$myfile"
    cp model.markdown "$myfile"
else
    echo "$myfile have been exist"
    exit 0;
fi


