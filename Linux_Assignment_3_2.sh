# !/bin/bash
# Date: 04/07/2019
# Author: Manoj T M
# Org: PathPartner Technology
echo "_________________________Linux_Assignment_3_2______________________________"
echo "---------------Accepting Input from the user-------------"
i=0
echo -e "\n"
while IFS="";read -r line
do 
    let i=$i+1
    if [[ i -ge $2 || i -le $3 ]]; then
        echo "$line"
    fi
done < $1
echo -e "\n"
echo "*************************************************************************"
echo -e "\n"