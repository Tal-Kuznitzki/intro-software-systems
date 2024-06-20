#!/bin/bash

Course=$1
CheckCourse=$(ls -l | grep -o $Course)
if [${#} != 1]; then 
	 echo "Wrong Number of argument" >&2
	 return 1
fi

if [$CheckCourse -eq 0]; then 
	echo "Course not found" >&2
         return 1
	 
fi









