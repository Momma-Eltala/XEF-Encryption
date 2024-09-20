nodes structure
32 bytes for hexadecimal md5 hash as string
4 byte binary for node parent {if zero it means it is in root of the directory it is saved too}
4 byte binary for directory node {the inode that the file or folder is asigned too}
256 byte for file name {null as terminated, if file is 256 byte no null is present after}
8 byte file size
2 byte flags that tells the program what it is
<xxxxxxxxxxxxxBA> A tells the program the node is used, B if is true, it is a folder, if false, it is a file
204 bytes of nothing