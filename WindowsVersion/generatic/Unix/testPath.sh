#!/bin/sh

#   Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

if [ -d $1 ]
then
    echo $1 exist
    exit 0
else
    echo $1 !exist
    exit 2
fi

