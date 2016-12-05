#!/bin/bash

################################################################
# New C++ file template (by JinWoo Lee)
# Usage :
#	new.sh filename.cpp
################################################################

if [ "$1" = "" ]
then
	echo "Usage :"
	echo "	`basename $0` filename"
	exit
fi

if [ -e "$1" ]
then
	echo "Error : $1 already exist."
	exit
fi

file_path=$1
file_dir=${file_path%/*}
file_name=${file_path##*/}
file_suffix=${file_name##*.}

year=`date +%Y`

cat > $file_path <<EOF
/**
 * @file	$file_name
 * @brief
 *
 *	(c) Copyright JinWoo Lee $year
 */

EOF

if [ "$file_suffix" = "h" ]
then
header_def=`echo $file_name | tr 'a-z.' 'A-Z_'`
cat >> $file_path <<EOF
#ifndef $header_def
#define $header_def

#endif // $header_def

EOF
fi

