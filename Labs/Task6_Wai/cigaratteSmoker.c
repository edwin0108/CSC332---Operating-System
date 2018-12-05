#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include <unistd.h>
#include "sem.h"

main() {

	#define PERMS 0666 //To grant read and write permissions 
	#define SMOKER 0 
	
	// Integers to hold semaphore(lock) values
	int lock;
	int smoker_tobacco;
	int smoker_paper;
	int smoker_match;
	int agent;
	
	// Other integers that will be used 
	int randNum;
	int pid;


	// 'lock' semaphore creation
	if((lock=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	  printf("\n can't create mutex semaphore");
	  exit(1);
	}

	// 'smoker_tobacco' semaphore creation
	if((smoker_tobacco=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	  printf("\n can't create mutex semaphore");
	  exit(1);
	}

	// 'smoker_paper' semaphore creation
	if((smoker_paper=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	  printf("\n can't create mutex semaphore");
	  exit(1);
	}

	// 'smoker_match' semaphore creation
	if((smoker_match=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	  printf("\n can't create mutex semaphore");
	  exit(1);
	}
	
	// 'agent' semaphore creation
	if((agent=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	  printf("\n can't create mutex semaphore");
	  exit(1);
	}

	// initialze the semaphores 	
	sem_create(lock,1);
	sem_create(smoker_tobacco,0);
	sem_create(smoker_paper,0);
	sem_create(smoker_match,0);
	sem_create(agent,0);
	
	// Parent process is forking
	//Create child processes as Smokers
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	// First Smoker  ( Only First Smoker will exceute this and it will never go beyond this becuase it will stuck on inifinite loop forever. It will smoke through the while loop only when it will be signaled by the agent )
	if (pid == SMOKER) {
		while (1) {
			 P(smoker_tobacco);  // Sleep right away
	     		 P(lock);
	    		 // Pick up match
	    		 // Pick up paper
	    		 printf("smoker_tobacco is smoking!\n");	// Smoke 
	     		 V(agent);
	     		 V(lock);
		}
	}
	
	// Parent Process is forking
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	// Second Smoker  ( Only Second Smoker will exceute this and it will never go beyond this becuase it will stuck on inifinite loop forever. It will smoke through the while loop only when it will be signaled by the agent )	
	if (pid == SMOKER) {
		while (1) {
			P(smoker_paper);  // Sleep right away
     			P(lock);
    			// Pick up match
    			// Pick up paper
    			printf("smoker_paper is smoking!\n");	// Smoke 
     			V(agent);
     			V(lock);
		}			
	}
	
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	// Third Smoker ( Only Third Smoker will exceute this and it will never go beyond this becuase it will stuck on inifinite loop forever. It will smoke through the while loop only when it will be signaled by the agent )	
	if (pid == SMOKER) {
		while (1) {
			P(smoker_match);  // Sleep right away
     			P(lock);
    			// Pick up match
    			// Pick up paper
    			printf("smoker_match is smoking!\n");	// Smoke 
     			V(agent);
     			V(lock);
		}			
	}
	
	// Only agent( Parent ) process will execute codes given below
	
	for ( int i = 0; i < 10; i++ ) {		// Run 10 times
		
		P(lock);
		randNum = rand() % 3; 		// Pick a ramdom smoker
		if (randNum == 1) {
         		// Put tobacco on table
         		// Put paper on table
         		printf("The agent will now let smoker_match to smoke!\n");
        		V(smoker_match);  // Wake up smoker with match
       		} 
       		else if (randNum == 2) {
         		// Put tobacco on table
        		// Put match on table
        		printf("The agent will now let smoker_paper to smoke!\n");
       	 		V(smoker_paper);  // Wake up smoker with paper
      		} 
      		else {
     			// Put match on table
    			// Put paper on table
    			printf("The agent will now let smoker_tobacco to smoke!\n");
	        	V(smoker_tobacco); // Wake up smoker with tobacco
			} 
		
		V(lock);
		P(agent);

	} 

	printf("\nProgram exited successfully\n\n");

	exit(0);

}
