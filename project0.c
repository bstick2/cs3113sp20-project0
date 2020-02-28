
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ARRAY_SIZE 500000 //this value is used for the unicode struct array that can be found in main{}

//Struct used to hold the character and the count of that character
typedef struct unicode {
	int count; //holds the count of each character
	char Char[7]; 
} unicode;

//Comparator used to sort the list from highest character count to lowest
int uniCompare(const void * left, const void *right) {

	const unicode * a = (const unicode *) left;
	const unicode * b = (const unicode *) right;

	if (a->count > b->count) 
	{
		return -1;
	}
	else if(a->count < b->count) 
	{
		return 1;
	}
	else 
	{
		return &right - &left;
	}
}

//Print function used to print the list of unicode characters along with their count. 
void printIt(unicode* c, unsigned long k){
	for(int i = 0; i < k; i++){
		dprintf(STDOUT_FILENO, 
				"%s->%d\n", //what the output will look like. the s will be the char and the d will be the count
				c[i].Char, c[i].count); //variables being passed into the string out
	}
}


int main() {
	unsigned int numBytes; //variable to hold the number of bytes needed for the character
	unsigned char buff[7]; //buff is used to hold the current character being read
	unicode uniArray[ARRAY_SIZE]; //unicode array that holds all the unicode characters read within it
	unsigned long charCount = 0; //used to hold the number of characters added to the unicode array 
	unsigned long index; //used as an index when going through the unicode array

	while(fread(buff, 1, 1, stdin)){
		if ((buff[0] & 128) == 0) numBytes = 1; //this checks to see if the first bit of the character is 0
		else if ((buff[0] & 224) == 192) numBytes = 2; //check to see if the first bit is a 1 and the second a 0
		else if ((buff[0] & 240) == 224) numBytes = 3; //checks to see if the first and second bit are 1's and third a 0
		else if ((buff[0] & 248) == 240) numBytes = 4; //checks to see if the first 3 bits are 1's and 4th one a 0
		else if ((buff[0] & 252) == 248) numBytes = 5; //checks to see if the first 4 bits are 1's and 5th one a 0
		else numBytes = 6; //checks to see if the first 5 bits are 1 and the 6th bit is 0.
		
		fread(&buff[1], 1, numBytes - 1, stdin); //reads in the character code into buff
		buff[numBytes] = '\0'; //makes buff a string

		if (charCount == 0) //checks to see if this is the first character to be added
		{
				strcpy(uniArray[0].Char, buff);
				uniArray[0].count = 1;
				charCount++;
		}
		else 
		{
			for (index = 0; index < charCount; index++)
			{	
				if (strcmp(uniArray[index].Char, buff) == 0) //compares the two characters and if they are the same increments the count
				{
					uniArray[index].count++;
					break;				
				}
				else if (index == charCount -1) //checks to see if the entire list has been read and the character wasnt found, then adds the character to the unicode array
				{
						strcpy(uniArray[index + 1].Char, buff);
						uniArray[index + 1].count = 1;
						charCount++;
						break;
				}
			}
		}
		
	}
	qsort(uniArray, charCount, sizeof(unicode), uniCompare); //sorts unicode array with the comparator created above
	printIt(uniArray, charCount); //print out the sorted character list
	return 0;
}


