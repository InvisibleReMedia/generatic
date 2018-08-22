#!/bin/sh

#   Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

cd $1
if [ -d $2 ]
then
    echo $2 exist
    exit 0
else
    echo $2 !exist
    exit 2
fi
