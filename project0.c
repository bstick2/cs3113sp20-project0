
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ARRAY_SIZE 100

typedef struct unicode {
	int count;
	char Char[7];
} unicode;

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

void printIt(unicode* c, unsigned long k){
	for(int i = 0; i < k; i++){
		dprintf(STDOUT_FILENO, 
				"%s->%d\n", //what the output will look like. the s will be the char and the d will be the count
				c[i].Char, c[i].count); //variables being passed into the string out
	}
}


int main() {
	unsigned int leading;
	unsigned int numBytes;
	unsigned char buff[7];
	unicode uniArray[ARRAY_SIZE];
	unsigned long charCount = 0;
	unsigned long index;

	while(fread(buff, 1, 1, stdin)){
		if ((buff[0] & 128) == 0) numBytes = 1;
		else if ((buff[0] & 224) == 192) numBytes = 2;
		else if ((buff[0] & 240) == 224) numBytes = 3;
		else if ((buff[0] & 248) == 240) numBytes = 4;
		else if ((buff[0] & 252) == 248) numBytes = 5;
		else numBytes = 6;
		
		fread(&buff[1], 1, numBytes - 1, stdin);
		buff[numBytes] = '\0';

		if (charCount == 0) 
		{
				strcpy(uniArray[0].Char, buff);
				uniArray[0].count = 1;
				charCount++;
		}
		else 
		{
			for (index = 0; index < charCount; index++)
			{	
				if (strcmp(uniArray[index].Char, buff) == 0)
				{
					uniArray[index].count++;
					break;				
				}
				else if (index == charCount -1)
				{
						strcpy(uniArray[index + 1].Char, buff);
						uniArray[index + 1].count = 1;
						charCount++;
						break;
				}
			}
		}
		
	}
	qsort(uniArray, charCount, sizeof(unicode), uniCompare);
	printIt(uniArray, charCount);
	return 0;
}


