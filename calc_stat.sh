#!/bin/bash

course=$1
if [ $# -ne 1 ]; then 
	 echo "Wrong Number of arguments" >&2
	 exit 1
fi
CheckCourse=$(ls | grep -o $course)
if [ -v $CheckCourse ]; then 
	echo "Course not found" >&2
         exit 1
	 
fi
#path=$(pwd)$course maybe not needed

gcc -o mean.exe mean.c
gcc -o median.exe median.c
gcc -o max.exe max.c
gcc -o min.exe min.c
gcc -o hist.exe hist.c	
folder_name=$course"_stat"
rm -rf $folder_name	
mkdir $folder_name
touch $folder_name/histogram.txt
touch $folder_name/statistics.txt
avg=$(./mean.exe $course)
median=$(./median.exe $course)
max=$(./max.exe $course)
min=$(./min.exe $course)
./hist.exe $course -nbins 10 > $folder_name/histogram.txt

statistics=$avg"	"$median"	"$min"	"$max #possible room for error as tabs?

echo $statistics >> $folder_name/statistics.txt

	









