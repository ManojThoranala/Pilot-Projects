# !/bin/bash
# Date: 25/06/2019
# Author: Manoj T M
echo "----------Process for the user------------"
echo ps -U <real user_name> -u <effective user_name> u
ps
echo "-U indicates real user name i.e user_name of the process,"
echo "-u, U effective user name which is same as real user name until there need to some permissions to be granted to non privilaged user the effective user name is changed"
echo "u indicates the user oriented format"
echo "-o, --format indicates the user-defined format"
echo "*************************************************************************"
echo ""
echo "----------Parent Process of PID------------"
echo ps --ppid <PID>
echo "PID - id of the process running for the user"
echo "*************************************************************************"
echo ""
echo "----------Kill the Process with PID------------"
echo kill <pid>
echo "kill -l -  lists all the 64 kill signals - IPC"
echo kill -l
kill -l
echo "*************************************************************************"
echo ""
echo "----------Memory % used of the Process with PID------------"
echo ps -pid <PID> -o %mem
echo "*************************************************************************"
echo "----------Memory used RSS of the Process with PID------------"
echo "pamap <pid> - the last gives the total used so used tail and grep/awk the 4th value"
echo pmap -x $$ | tail -n 1 | awk {'print$4'}
pmap -x $$ | tail -n 1 | awk {'print$4'}
echo "*************************************************************************"
echo ""
echo "----------CPU % used of the Process with PID------------"
echo ps -pid <PID> -o %cpu
echo "*************************************************************************"
echo ""
