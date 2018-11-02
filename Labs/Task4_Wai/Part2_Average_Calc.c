#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

double Average(int hw_num){
  int rdfd;
  rdfd = open("input_file.txt", O_RDONLY);
  errno = 0;
  if (-1 == rdfd)
  {
    printf("\nopen() failed with error [%s]\n", strerror(errno));
    return 1;
  }
  else 
  {
   int int_grade, buf_used=0, sum=0, start_point=0, student_num=10;
   char check;
   char grade[3];
   for (int j=0; j<student_num; j++)
   { 
     start_point = (hw_num-1)*4+(j*41);
     lseek(rdfd, start_point , SEEK_SET);
     for (int i=start_point; i<start_point+3; i++)//in input_text, the format of each homework grade is "### ", which is (0-3,4-7,8-11,...), but we only read first three numbers.
     {
       read(rdfd,&check,1);
       if (check!=' ') {grade[buf_used]=check; buf_used++;}
     }
     int_grade=atoi(grade);
     sum=sum+int_grade;
     //clean buffer
     buf_used = 0;
     memset(grade, 0x0, 3);
   }
   return sum/10.0;
  }
}

int main ()
{
  double average;
//Manager 1
  int Manager1=fork(); 
  if (Manager1 == 0)
  {
    int Worker1=fork();
    if (Worker1 == 0) 
    {
       int Worker2=fork();
       if (Worker2 != 0) 
       {
	average=Average(1);
        printf("The HW1 average is:%.2f\n",average);
        
        exit(0);
       }
       else
       {
        average=Average(2);
        printf("The HW2 average is:%.2f\n",average);
	exit(0);
       }
     }
     else
     {
       printf("I am Manager 1, my pid is: %d\n",getpid());
       exit(0);
     }
     //exit(0);
  }
  else 
  {
    printf("I am Director and let Manager 1 start, my pid is: %d\n",getpid());
  }

  usleep(10000);
//Manager 2
  int Manager2=fork();
  if (Manager2 == 0) 
  {
    int Worker3=fork();
    if (Worker3 == 0) 
    {
       int Worker4=fork();
       if (Worker4 != 0) 
       {
	average=Average(3);
        printf("The HW3 average is:%.2f\n",average);
        exit(0);
       }
       else
       {
        average=Average(4);
        printf("The HW4 average is:%.2f\n",average); 
	exit(0);
       }
     }
     else
     {
       printf("I am Manager 2, my pid is: %d\n",getpid());
       exit(0);
     }
     //exit(0);
  }
  else 
  {
    printf("\nI am Director and let Manager 2 start, my pid is: %d\n",getpid());
  }

  usleep(10000);
//Manager 3
  int Manager3=fork();
  if (Manager3 == 0) 
  {
    int Worker5=fork();
    if (Worker5 == 0) 
    {
       int Worker6=fork();
       if (Worker6 != 0) 
       {
	average=Average(5);
        printf("The HW5 average is:%.2f\n",average);
        exit(0);
       }
       else
       {
        average=Average(6);
        printf("The HW6 average is:%.2f\n",average); 
	exit(0);
       }
     }
     else
     {
       printf("I am Manager 3, my pid is: %d\n",getpid());
       exit(0);
     }
     //exit(0);
  }
  else 
  {
    printf("\nI am Director and let Manager 3 start, my pid is: %d\n",getpid());
  }

  usleep(10000);
//Manager 4
  int Manager4=fork();
  if (Manager4 == 0) 
  {
    int Worker7=fork();
    if (Worker7 == 0) 
    {
       int Worker8=fork();
       if (Worker8 != 0) 
       {
	average=Average(7);
        printf("The HW7 average is:%.2f\n",average);
        exit(0);
       }
       else
       {
        average=Average(8);
        printf("The HW8 average is:%.2f\n",average); 
	exit(0);
       }
     }
     else
     {
       printf("I am Manager 4, my pid is: %d\n",getpid());
       exit(0);
     }
     //exit(0);
  }
  else 
  {
    printf("\nI am Director and let Manager 4 start, my pid is: %d\n",getpid());
  }

  usleep(10000);
//Manager 5
  int Manager5=fork();
  if (Manager5 == 0) 
  {
    int Worker9=fork();
    if (Worker9 == 0) 
    {
       int Worker10=fork();
       if (Worker10 != 0) 
       {
	average=Average(9);
        printf("The HW9 average is:%.2f\n",average);
        exit(0);
       }
       else
       {
        average=Average(10);
        printf("The HW10 average is:%.2f\n",average); 
	exit(0);
       }
     }
     else
     {
       printf("I am Manager 5, my pid is: %d\n",getpid());
       exit(0);
     }
     //exit(0);
  }
  else 
  {
    printf("\nI am Director and let Manager 5 start, my pid is: %d\n",getpid());
    exit(0);
  }
  
  exit(0);
}
