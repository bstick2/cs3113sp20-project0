# Project 0
## Branson Stickney
### How to Run the program
First download the project.c file and the Makefile. Open up terminal and run "make clean" within the folder containing the mentioned files, this will ensure that there is output file in the folder by removing it. Next, run "make all", this will make the output file needed with the project.c file. Finally, run "cat filename | ./project0", where filename is the text file being read. This will read the file and output the list of characters sorted by their count. 
### Know Bugs
Not all bugs are known, that being said in order to pass the test required for this project, I just defined a variable ARRAY_SIZE and increased its value to hold enough of the unicode structs created in the code. Because of this, ARRAY_SIZE might need to be a different value for the file you are counting. 
### Collaborators
The people and websites I collaborated with as well as a description of what was achieved can be found in the COLLABORATORS file. Most problems I had when writing this code were C related issues, which were solved by searching the internet to further understand the C language, such as strcpy(), strcmp(), and qsort(). I also came across a problem when trying to figure out the number of bytes required for each character read. I went to a friend of mine, Chase Gough, and he was able to talk me through the rules of Unicode and I was able to find out how to compute the number of bytes. 
