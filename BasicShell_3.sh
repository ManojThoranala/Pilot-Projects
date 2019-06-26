# !/bin/bash
# Date: 25/06/2019
# Author: Manoj T M
echo "----------CPU Info------------"
echo lscpu
lscpu
echo "Alternative. Above command gives better details"
echo lshw -C cpu
lshw -C cpu
echo "*************************************************************************"
echo ""
echo "---------- Linux kernel Info------------"
echo "uname - gets the system information. -s kernel name, -r kernel release -v kernel version"
echo uname -srv
uname -srv
echo "*************************************************************************"
echo ""
echo "---------- System Uptime Info------------"
#Uptime command is included in procps package. It provides the current system time, number of logged in users and current CPU load.
echo uptime -p
uptime -p
echo "-p gives human presentable format ..pretty.., -s gives the up time in the context of since when the system is up in yyyy-mm-dd HH:MM:SS format"
echo "*************************************************************************"
echo ""
echo "---------- Tasks Running Info------------"
echo gnome-terminal -- top
gnome-terminal -- top
echo "Similar to task manager in windows, the shell shows all current processes details running"
echo "*************************************************************************"
echo ""
echo "----------Service Related Commands------------"
echo service <service_name> start
echo service <service_name> stop
echo service <service_name> restart
echo "Above are the service related commands. service_name can be script or service like sshd"
echo "*************************************************************************"
echo ""
echo "----------Checking Available Memory Info------------"
echo free -lhw
free -lhw
echo "free shows the available memory and memory in use -h human readable format, l- shows low and high memory details, w - shows the details in wide view"
echo mkdir zipable
mkdir zipable
echo cd zipable
cd zipable
echo touch file_1 && touch file_2
touch file_1 && touch file_2
cd ..
echo "------Zipping-----"
echo zip zipable
zip zipable zipable.zip
echo "*************************************************************************"
echo "-----Unzipping----"
echo rm -r zipable
rm -r zipable
echo unzip zipable.zip
unzip zipable.zip
echo "*************************************************************************"
echo ""
echo ""
