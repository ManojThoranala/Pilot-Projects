# !/bin/bash
# Date: 24/06/2019
# Author: Manoj T M

echo "----------Lisiting files and its options------------"
echo "ls - Command used to list the files / directories in the directory"
echo ls
ls
echo "*************************************************************************"
echo "Options for ls are shown below:"
echo "*************************************************************************"
echo "*************************************************************************"
echo "-a option lists all the contents of the directory including files with ."
echo "*************************************************************************"
echo ls -a
ls -a
echo "*************************************************************************"
echo "-l option is long listing to list all the details about files listed using ls"
echo "*************************************************************************"
echo ls -l
ls -l
echo "*************************************************************************"
echo "-t option is to list all the files in newest accessed fisrt order"
echo "-r option is to list all the files in reverse order."
echo "*************************************************************************"
echo ls -ltr
ls -ltr
echo "*************************************************************************"
echo "-h human readable format of properties while listing files"
echo "*************************************************************************"
echo ls -ltrh
ls -ltrh
echo "*************************************************************************"
echo ""
echo "----------------File Handling-------------------"
echo "vi <file_name> or gedit <file_name> or nano <file_name> - depends on the user choice for the editor vi / gedit / nano /emacs"
echo "Above command opens file matching to file_name if file is not present it creates the file with file_name"
echo ""
echo "*************************************************************************"
echo ""
echo "------------------------Editor Example------------------------------"
echo "use <apropos editor> command to find all the available editors"
echo vi editor.txt
gnome terminal -vi editor.txt
echo "*************************************************************************"
echo gnome-terminal -- ls editor.txt
gnome-terminal -- ls editor.txt
echo "*************************************************************************"
echo "Above command lists the file created or empty if not"
echo "*************************************************************************"
echo ""
echo "---------------------------Move Example---------------------------------"
echo "*************************************************************************"
echo "mv - move the file contents from source to destination directory. Can be used to rename source name to destination name"
echo "*************************************************************************"
echo mkdir moving_dest
mkdir moving_dest
echo touch exapmle_move.txt
touch exapmle_move.txt
echo mv exapmle_move.txt moving_dest
mv exapmle_move.txt moving_dest
echo "*************************************************************************"
echo ""
echo "------------------------Rename_Example------------------------------"
echo touch example_rename.txt
echo mv example_rename.txt example.txt
echo "*************************************************************************"
echo ""
echo "------------------------Copy_Example------------------------------"
echo "*************************************************************************"
echo "copy a file / directory ot destination location" > example.txt
echo "*************************************************************************"
echo cp example.txt example_copy.txt
cp example.txt example_copy.txt
echo "*************************************************************************"
echo "showing the file contents"
echo diff -y example.txt example_copy.txt
diff -y example.txt example_copy.txt
echo "*************************************************************************"
echo ""
echo "------------------------Remove_Example------------------------------"
echo rm example_copy.txt
rm example_copy.txt
echo rm example_copy.txt
rm example.txt
echo "----------Verification--------------"
echo ls example.txt
ls example.txt
echo "*************************************************************************"
echo ""
echo "------------------------Symbolic_Example------------------------------"
echo touch file_1
touch file_1
echo ln -s file_1 file_1_link
echo "link creates link file_2 as a link to file_1"
ln -s file_1 file_1_link
echo "*************************************************************************"
echo "rm file_1_link - Removes the link and if the file is removed the link also gets dicarded"
echo rm file_1
rm file_1
echo "*************************************************************************"
echo ""
echo "------------------------Redirections------------------------------"
echo "Hello, redirection example" > file_redirect.txt
echo "Hi Redirection overwrite" > file_redirect.txt
echo "Redirection Append at end of file" >> file_redirect.txt
echo "*************************************************************************"
echo ""
echo "------------------------Ownerships------------------------------"
echo "chown user:user_group file - changes the ownership of file given to user and user group given."
echo "chown :user_group file - changes only group ownership"
echo "chown user file - changes only user ownership"
echo "*************************************************************************"
echo "users -  gives users present in the system"
echo users
users
echo "*************************************************************************"
echo ""
echo "------------------------Line Count------------------------------"
echo "Hello World is the kick start program for any programming lanuage" > line_count_file.txt
echo "to know the basic work how and syntax" >> line_count_file.txt
echo wc -l line_count_file.txt
wc -l line_count_file.txt
rm line_count_file.txt
echo "*************************************************************************"






