#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path, [String]$file)
cd $path
Remove-Item -Path $path -Filter $file

