#!/bin/bash

PL0=./main


for i in `ls tests/ok/*.pl0`
do
    output=`$PL0 $i 2>&1`
    _=`echo $output | grep 'error'`
    if [ $? == 0 ]
    then
        echo "test failed: $i"
        echo "$output"
        exit 1
    fi
done

for i in `ls tests/error/*.pl0`
do
    output=`$PL0 $i 2>&1`
    _=`echo $output | grep 'error'`
    if [ $? == 1 ]
    then
        echo "test failed: $i"
        echo "$output"
        exit 1
    fi
done

echo "all tests passed"
