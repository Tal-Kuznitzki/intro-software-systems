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
# echo -e $data
# process each rule - OR
for rule in $rules; do
    fields=$(echo $rule | sed 's/,/ /g')
    # procees each field - AND
    temp=$data
    for field in $fields; do
        field=$(echo $field| sed 's/ //g' | sed 's/\n//g')
        if [ -z "$field" ]; then
            echo "Encountered an empty field, skipping..."
            continue
        fi
        
        temp=$(echo $temp|./firewall.exe $field)
        # echo $temp | head
        # temp=$(./firewall.exe $field <&0)
        # echo $field
        # echo -e $temp
    done
    
    output+=$temp
    # output+="\n"
    # echo -e "\n"
done

echo -e $output|sort|uniq
