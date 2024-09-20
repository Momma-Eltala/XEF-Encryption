nodes structure
32 bytes for hexadecimal md5 hash as string 0
4 byte binary for node parent {if zero it means it is in root of the directory it is saved too} 32
4 byte binary for directory node {the inode that the file or folder is asigned too} 36
4 bytes for the sibling node pointer 40
256 byte for file name {null as terminated, if file is 256 byte no null is present after} 44
8 byte file size
2 byte flags that tells the program what it is
<xxxxxxxxxxxxxBA> 
A tells the program the node is used
B if is true, it is a folder, if false, it is a file
offset from 0 of the file
192 bytes of nothing