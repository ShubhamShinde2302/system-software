Assignment 1: Hard Link, Symbolic Link & FIFO 
    • Hard Link: Creates another filename for the same inode, so both files share the same data blocks. 
    • Hard links have the same inode number and increase the link count. 
    • Deleting one hard link does not remove the file until the link count becomes 0. 
    • Command: ln file1.txt hardlink.txt 
    • Symbolic (Soft) Link: Creates a new file with a different inode that stores the path of the original file. 
    • Soft links do not increase the link count and become dangling if the original file is deleted or renamed. 
    • Command: ln -s file1.txt softlink.txt 
    • FIFO (Named Pipe): A special file used for Inter-Process Communication (IPC) between processes. 
    • FIFO follows the First In, First Out principle and transfers data without permanently storing it. 
    • The writer blocks if no reader exists, and the reader blocks if no writer exists. 
    • Commands: mkfifo mypipe, echo "Hello" > mypipe (writer), cat mypipe (reader). 
    • Verification: ls -li (inode & link count), ls -l (p indicates a FIFO).
