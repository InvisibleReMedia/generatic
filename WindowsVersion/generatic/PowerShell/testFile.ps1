#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path, [String]$file)
cd $path
if (Test-Path $file -PathType Leaf) {
	echo "$path/$file exist"
	exit 0
} else {
	echo "$path/$file !exist"
	exit 512
}


