# !/bin/bash
# Date: 26/06/2019
# Author: Manoj T M
echo "---------------Finding the files staring with letter s-------------"
echo find . -maxdepth 1 -type f -name 's*'
find . -maxdepth 1 -type f -name 's*'
echo "*************************************************************************"
echo "---------------Finding the file test in current and subdirectories-------------"
echo find . -type f -name 'test'
find . -type f -name 'test'
echo "*************************************************************************"
echo "---------------Selective display of ls -ltr listing 3rd column-------------"
echo ls -ltr | awk '{ print $3 }'
ls -ltr | awk '{ print $3 }'
echo "*************************************************************************"
echo "---------------Accepting Input from the user-------------"
echo "Hi, Please enter your name below:"
read response
echo Hello, $response. Welcome! to PathPartner. 
echo "*************************************************************************"
