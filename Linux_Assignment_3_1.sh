
# !/bin/bash
# Date: 04/07/2019
# Author: Manoj T M
# Org: PathPartner Technology
echo "_________________________Linux_Assignment_3_1______________________________"
echo "---------------Accepting Input from the user-------------"
echo "Hi, Enter the Test to extract 3rd Character in it. Enter \"q\" to stop input."
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
#Displaying the ouputs for inputed lines in the array
echo "3rd character of each line enetered is:"
for line in ${line_arr[*]}
do 
    echo -e "\n"
#extracting the first 3 characters using head and using tail extract the 3rd character from the ouput of head
    echo "$line" | head -c 3 | tail -c 1
done
echo -e "\n"
echo "*************************************************************************"
echo -e "\n"