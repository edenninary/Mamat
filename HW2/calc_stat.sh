#!/bin/bash

if [ "$#" -ne 1 ]; then 
	echo "Wrong number of arguments" 1>&2
	exit 0
fi

if [ ! -f "$*.txt" ];then
	echo "Course not found" 1>&2
	exit 0
fi

if [ -d "$*_stat" ];then
	rm -r "$*_stat"
fi

mkdir "$*_stat"

data=$(cat "$*.txt")

n=$(echo "$data" | wc -l)

hist=$(echo "$data" | ./hist.exe -n_bins 10)

echo "$hist" > ./"$*_stat"/histogram.txt

mean=$(echo "$data" | ./mean.exe)
median=$(echo "$data" | ./median.exe)
min=$(echo "$data" | ./min.exe)
max=$(echo "$data" | ./max.exe)

hist_stat=$(echo "$data" | ./hist.exe -n_bins 20)

arr=($hist_stat)
pass_count=0

for (( i=23; i<=40; i=i+2 ))
do
	pass_count=$((${arr[$i]}+pass_count))
done

prec_pass1=$(( $pass_count*100 ))
prec_pass2=$(( $prec_pass1/$n ))

echo -e "$mean"' \t'"$median"' \t'"$min"' \t'"$max"' \t'"$prec_pass2" > ./"$*_stat"/statistics.txt
