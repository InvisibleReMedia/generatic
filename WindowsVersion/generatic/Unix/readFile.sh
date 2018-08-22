#!/bin/sh

#   Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

cd $1
if [ -e $2 ]
then
    sed = $2 | sed 'N;s/\n/ /'
    exit 0
else
    echo $2 !file
    exit 2
fi
