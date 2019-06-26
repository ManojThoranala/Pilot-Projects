# !/bin/bash
# Date: 26/06/2019
# Author: Manoj T M
echo "-------Accessing Environmental Variables"
echo "env gives all envionmental varables set on the system"
echo env
env
echo printenv SHELL
printenv SHELL
echo printenv PATH
echo printenv HOME
echo "*************************************************************************"
echo ""
echo "--------WHO and WHOAMI--------------"
echo who - gives user logged in username
echo who -Hub
who -Hub
echo "H - gives the column names, u gives all looged in users, b - last bootup time"
echo "*************************************************************************"
echo whoami
whoami
echo "whoami gives the effective username of current user"
echo "*************************************************************************"
echo ""
echo "---------------Network INterfaces Info----------------"
echo ip -h link show
ip -h link show
echo "*************************************************************************"
echo "ifconfig - shows all network interfaces , a- shows all even if they are down"
echo ifconfig -a
ifconfig -a
echo "Alternatively"
echo ip a
ip a
echo "*************************************************************************"
echo nmcli -p
nmcli -p -m tabular
echo "*************************************************************************"
echo ""
echo "----------------IP and MAC Info----------------"
echo "ip route list - shows all the ips configured for the user use grep default to get ip adress"
echo ip route list | grep default
ip route list | grep default
echo "*************************************************************************"
echo "ip link show - shows the MAC of the interfaces"
echo ip link show
ip link show
echo "*************************************************************************"
echo ""
echo "-------------------Network Statistics-------------"
echo "ifconfig - gives Rx and Tx packets dropped errors and so on for each inerface"
echo ifconfig
ifconfig
echo "netstat -s -shows network statistics for each interface "
echo netstat -s
netstat -s
echo "*************************************************************************"
echo ""
echo "-----------------File transfer using FTP----------------"
echo "ftp <remote_ip> -  starts connection by sending a reqeuest"
echo ftp <remote_ip>
echo "shell shows some info with confirmation mesaage and prompts for user name remote machine"
echo "If the enetered user name is correct then the shell prompts for password to login"
echo "if the credentails are right the conbection says code 230 ok and shows the ftp> prompt"
echo ftp> {cd | ldc | get | mget | put | mput | quit}
echo "These above are the basic commands for getting a file and uploading a file from or to remote machine"
echo "ldc <path> - change local directory. c=to cd in local machine" 
echo "cd - as similar to cd but this is for remote machine"
echo "get <path> - to download a file from remote machine. mget - used for multiple files"
echo "put <path> - upload file to remote machine. mput - for multiple files"
echo "quit - closes the ftp connection. bye - also can be used for closing the connection"
echo "SFTP is similar and it is more secure than FTP. SFTP uses encrypted ssh connection."
echo "*************************************************************************"
echo ""
echo "-----------------File transfer using SCP----------------"
echo "scp secure copy is the secure version of rcp remote copy, which uses ssh connection for communication"
echo scp <file_name> <user>@<server/doamin>:<destination_directory>
echo " Above scp command copies file to remote machine"
echo "*************************************************************************"
echo scp <user>@<server/doamin>:<path_to_file_to_be_copied> /detination directory
echo "Above command copies file from remote machine to local directory"
echo "*************************************************************************"
echo "-r option is used to copy the directory"
echo "*************************************************************************"
echo ""



