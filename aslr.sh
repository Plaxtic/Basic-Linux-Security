#!/bin/sh

## check option
if [[ $1 == "on" ]]
then
    VAL=2
elif [[ $1 == "off" ]]
then
    VAL=0
else
    echo "Usage $0: on|off"
    exit 1
fi

## toggle aslr
echo $VAL | sudo tee /proc/sys/kernel/randomize_va_space >/dev/null &&
echo aslr $1
