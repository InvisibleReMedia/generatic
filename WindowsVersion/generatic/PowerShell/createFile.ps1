#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path, [String]$file)
cd $path
New-Item -Name $file -ItemType File

