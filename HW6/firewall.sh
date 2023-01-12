#!/bin/bash

#make sure there is only one argument
if [[ $# != 1 ]]; then
    exit 1
fi

#clean the input of undesired characters
data=$(cat $1 | sed 's/ //g' | \
                sed 's/#.*//' | \
                sed '/^$/d' | \
                sed 's/,\{2,\}/,/g' | \
                sed 's/^,//g')

#save the packets into a variable     
pkt=$(cat)


#put the rules into an array
#and send each packet through each rule
#then print the results sorted and without spaces
#into output file
while read -r cur_rule; do
	IFS=',' 
	read -ra rule <<< "$cur_rule"
    echo "$(echo "$pkt" | ./firewall.exe "${rule[0]}" | \
                          ./firewall.exe "${rule[1]}" | \
                          ./firewall.exe "${rule[2]}" | \
                          ./firewall.exe "${rule[3]}")"

done <<< "$data" | sort --unique | sed 's/ //g' | sed '/^$/d' 
