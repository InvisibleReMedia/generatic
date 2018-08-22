#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path, [String]$dir)
cd $path
if (Test-Path $dir) {
	echo "$path/$dir exist"
	exit 0
} else {
	echo "$path/$dir !exist"
	exit 512
}


