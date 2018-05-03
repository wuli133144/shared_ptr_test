#!/bin/bash


rm -rf test

make 

if [ $? -ne 0 ];then
        echo "build files failed..."
        sleep 1
        exit 1
fi


