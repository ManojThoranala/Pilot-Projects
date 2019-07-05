
# !/bin/bash
# Date: 05/07/2019
# Author: Manoj T M
# Org: PathPartner Technology
echo "_________________________Linux_Assignment_3_3______________________________"
echo "---------------Accepting Input from the user-------------"
echo "Hi, Enter the Test to replace first character with the your pattern as argument. Enter \"q\" to stop input."
line_arr=()
#IFS - Internal field separtor. Removing the defualt space as delimiter.
#while loop to take inputs
while IFS="";read -r line
do
    if [[ "$line" == "q" ]]; then 
        break;
    fi
#appending inputs to an array
    line_arr+=("$line")
done
echo "---------------Input End-------------------"
echo "Enter the pattern:"
read pattern
echo "-----------OUPUT-------------"
for line in ${line_arr[*]}
do 
    echo -e "\n"
#extracting the first 3 characters using head and using tail extract the 3rd character from the ouput of head
    echo "$line" | sed 's/./'"$pattern"'/'
done
echo -e "\n"
echo "*************************************************************************"
echo -e "\n"