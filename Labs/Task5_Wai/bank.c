#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include <unistd.h>
#include "sem.h"


#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

// ##################### ( Added Code: Variables needed to use Semaphores ) ####################

#define BUFSIZE 6				// Changed to 6 for calculating wait time  
#define PERMS 0666 //0666 - To grant read and write permissions 

int* buffer;			// Shared memory array
int mutex;    // semaphore variable : Mutex

// ####################### ( Added Code Ends Here ) ###########################################

main()
{
	
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	int dad_pid = 0;				// Dad process Pid
	int son1_pid = 0;				// Son 1 process pid
	int son2_pid = 0;				// Son 2 process pid
	
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
	
// #############(Added code: Code for shared memory, linking the memory to dynamic array & semaphores )################
	int shmid,no=1;
	int n;

	if((shmid=shmget(1234,BUFSIZE,IPC_CREAT | PERMS)) < 0)
	{
	printf("\n unable to create shared memory");
	return;
	}
	if((buffer=(int*)shmat(shmid,(char*)0,0)) == (int*)-1)
	{
	printf("\n Shared memory allocation error\n");
	exit(1);
	}

	// semaphore creation
	if((mutex=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
	printf("\n can't create mutex semaphore");
	exit(1);
	}

	// initialze the semaphore 	
	sem_create(mutex,1);
	
	// Initialization buffer for different processes to keep track of waiting time
	
	buffer[0] = 0;		// Wait Time For parent process
	buffer[1] = 0;		// Wait Time For Son-1 Process
	buffer[2] = 0;		// Wait TIme For Son-2 Process
	buffer[3] = dad_pid;
	buffer[4] = son1_pid;
	buffer[5] = son2_pid;

 // ######################## (Added code Ends Here) ###############################################
	

	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
		dad_pid = getpid();
		N=5;
		for(i=1;i<=N; i++)
		{	
			buffer[3] = dad_pid;
			P(mutex); // ################ ( Mutex semaphore Used ) ##############
			if ( buffer[4] != 0 )			// Checking and updating waiting time
				buffer[1]++;
			if ( buffer[5] != 0 )
				buffer[2]++;   
			
			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */
			
			buffer[3] = 0;
			V(mutex); // ################ ( Mutex semaphore Used ) ##############
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{	
			son1_pid = getpid();
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{	
				buffer[4] = son1_pid;
				P(mutex); //  ################ ( Mutex semaphore Used ) ##############
				if ( buffer[3] != 0 )			// Checking and updating waiting time
					buffer[0]++;
				if ( buffer[5] != 0 )
					buffer[2]++;  
					
				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{	
			
						fclose(fp2);
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
						
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				buffer[4] = 0;
				V(mutex); // ################ ( Mutex semaphore Used ) ##############
			}
		
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{	
				son2_pid = getpid();
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{	
					buffer[5] = son2_pid;
					P(mutex); //  ################ ( Mutex semaphore Used ) ##############
					if ( buffer[3] != 0 ) 			// Checking and updating waiting time
						buffer[0]++;
					if ( buffer[4] != 0 )
						buffer[1]++;	
					
					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{	
						
						fclose(fp3);
						flag1 = TRUE;
						
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{	
				
							fclose(fp2);
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
							
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					buffer[5] = 0;
					V(mutex); // ################ ( Mutex semaphore Used ) ##############
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
				
				printf("Dad_process waited: %d times\nSon1_Process Waited: %d times\nSon2_Process waited: %d times\n",buffer[0],buffer[1],buffer[2]); // Printing out wait times for N attempts
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}