
# !/bin/bash
# Date: 05/07/2019
# Author: Manoj T M
echo "Hi, See below to know whose marks are missing in the file."
val=4
echo -e "\n"
while read line
do
    count="$(echo $line | wc -w)"
    if [[ $count -lt $val ]]; then
        name=$(echo $line | awk '{print $1;}')
        echo "Not all scores are available for $name" 
    fi
done < $1

echo -e "\n"
echo "*************************************************************************"
echo -e "\n"
