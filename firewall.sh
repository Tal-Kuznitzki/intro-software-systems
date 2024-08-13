#!/bin/bash

# arg check
if [ $# -ne 1 ]; then 
	echo "Wrong Number of arguments" >&2
	exit 1
fi

#read files
rules=$(cat $1 | sed 's/#/\n#/g' | grep -v -e '^#' -e '^$' | sed 's/ //g')
data=$(cat -)
output=

# process each rule - OR
for rule in $rules; do
    fields=$(echo $rule | sed 's/,/ /g')
    # procees each field - AND
    temp=$data
    for field in $fields; do
        temp=$(echo $temp|./firewall.exe $field)
        # echo $field
    done
    ourput+=$temp"\n"
done

echo -e $output|sort|uniq
