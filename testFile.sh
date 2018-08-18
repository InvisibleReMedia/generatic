#!/bin/sh

#   Langage C
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

cd $1
if [ -e $2 ]
then
    exit 0
else
    exit 2
fi

