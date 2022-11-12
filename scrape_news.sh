#!/bin/bash

exec > results.csv

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
		   grep -i -oP "https://(www.)?ynetnews.com/article/[A-Za-z0-9]+"| \
		   sort --unique)

arr=($articles)
echo "$(echo "$articles" | wc -l)"

for i in "${arr[@]}"
do
	article_i=$(wget --no-check-certificate -O - $i 2>/dev/null)
	bibi=$(echo $article_i | grep -ioP "Netanyahu" | wc -l)
	gantz=$(echo $article_i | grep -ioP "Gantz" | wc -l)
	lapid=$(echo $article_i | grep -ioP "Lapid" | wc -l)
	bengvir=$(echo $article_i | grep -ioP "Ben Gvir" | wc -l)
	if [[ $bibi -eq 0  &&  $gantz -eq 0 && $lapid -eq 0 && $bengvir -eq 0 ]]; then
		echo "$i, -"
	else
		echo -n "$i, Netanyahu, "
		echo -n "$bibi, Gantz, "
		echo -n "$gantz, Lapid, "
		echo -n "$lapid, Ben-gvir, "
		echo -n "$bengvir"
		echo ""
	fi
done

