#
#   Power Shell Script
#   Projet Generatic
#   17/7/18 CET 10:00
#   business.forward.technology@gmail.com
#
#

param([String]$path, [String]$dir)
Remove-Item -Path @($path,$dir) -Recurse


