#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int randInt(){

	int integer[1];

	int file = open("/dev/random",O_RDONLY);
	if(file==-1) printf("Error %d: Error: %s\n",errno,strerror(errno));

	int error = read(file,integer,sizeof(integer[1]));
	if(error==-1) printf("Error %d: Error: %s\n",errno,strerror(errno));

	close(file);
	return *integer;
}

int main(){

	int randNum[10];
	int i;

	printf("Generating Random Numbers\n");
	for(i=0;i<10;i++){
		randNum[i] = randInt();
		printf("\tRandom Number %d: %d\n",i,randNum[i]);
	}

	printf("Writing numbers to file...\n");
	int fileOut = open("./outFile",O_RDWR | O_CREAT,0764);
	if(fileOut==-1) printf("Error %d: Error: %s\n",errno,strerror(errno));

	int error = write(fileOut, randNum, sizeof(randNum));
	if(error==-1) printf("Error %d: Error: %s\n",errno,strerror(errno));

	printf("Reading numbers from file...\n");
	int copyArr[10];
	error = read(fileOut, copyArr, sizeof(copyArr));
	if(error==-1) printf("Error %d: Error: %s\n",errno,strerror(errno));

	printf("Verification that the numbers were the same\n");
	for(i=0;i<10;i++){
		printf("\tRandom Number %d: %d\n",i,randNum[i]);
	}
	close(fileOut);
	return 0;
}
