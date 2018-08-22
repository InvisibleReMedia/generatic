#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path)

if (Test-Path $path) {
	echo "$path exist"
	exit 0
} else {
	echo "$path !exist"
	exit 512
}


