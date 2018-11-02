#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

//INPUT: X = # chapters, Y = #HW(s) per chapter(s)
//invaild x & y & input file will no process

int main () {

	int input;
	int cNumber;
	int rNumber = 10;
	int count = 0;
	int count2 = 0;
	int i = 0, j =0, k =0, x = 0, y = 0;		// Counters for various uses 
	
	int chaptNumber = 0;
	int hwNumber = 0;
	int studentNumber = 10;
	char fileName[20];
	
	// Reading Arguements
	printf("Please input the file path/name:  ");
	scanf("%[^\n]s", fileName);
	printf("Please input the value of x:  ");
	scanf("%d", &chaptNumber);
	printf("Please input the value of y:  ");
	scanf("%d", &hwNumber);
	
	cNumber = chaptNumber * hwNumber;
	
	// Allocating memory to the 2D array
	
	int *arr[rNumber];
	for ( i = 0; i < rNumber; i++) 
	{
		arr[i] = (int *) malloc(cNumber * sizeof(int));
	} 
	
	// Read file & Load the values into 2D Array
	
	FILE *p_file = fopen(fileName, "r");
		
		for (x = 0; x <  rNumber; x++) {
     			for (y = 0; ( y < cNumber) && ( (fscanf( p_file, "%d", &input) ) ) > 0 ; y++) {
				arr[x][y] = input;
			}
		}
		
	fclose(p_file);

	
	
	// Forking process & calculating average
	
	
	int total = 0;				// For calculating total
	int coloumn1 = 0;			// Keeping track of index type (coloumn1,coloumn2) in to 2D Array
	int coloumn2 = 0;			// Keeping track of index type (coloumn1,coloumn2) in to 2D Array
	
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;		// Counters using for looping
	
	int status1 = 0;
	int status2 = 0;
	
	for ( c1 = 0; c1 < chaptNumber; c1++) {
		
		status1 = fork();
		wait(&status1);
		if ( status1 == 0) {
			for ( c2 = 0; c2 < hwNumber; c2++) {
				status2 = fork();
				wait(&status2);
				if ( status2 == 0 ) {
					coloumn2 += c2;
				
					for (coloumn1 = 0; coloumn1 < 10 ; coloumn1++) {
						total += arr[coloumn1][coloumn2];	
					}
					printf("(Chapter %d)'s %dth HW average is: %0.2f\n",(c1+1),(c2+1),total/10.0);	
					return 1;	
				}
				
			}
		return 1;
		}
	coloumn2 += hwNumber;
	}
	return 0;
}
