#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include "sem.h"

#define PERMS 0666 //To grant read and write permissions 

int table_used = 1, generated_item[2], generated = 0;
char *item[] = {"tobacco", "paper", "matches"};
int table;
void *agent(void *arg)
{
    // agent thread function that has infinite number of ingredients
    int first_item, second_item, k = 0;
    int count = 0;
    while (1)
    {
        sleep(1);
        P(table);
        if (count == 10)
            exit(0);
        if (table_used == 1)
        {
            first_item = k;
            second_item = first_item + 1;
            if (second_item == 3)
                second_item = 0;
            k = second_item;
            generated_item[0] = first_item;
            generated_item[1] = second_item;
            printf("\nAgent produces %s,%s\n", item[first_item], item[second_item]);
            generated = 1;
            table_used = 0;
            count++;
        }
        V(table);
    }

}
void *smokeri(void *i)
{
    while (1)
    {
        sleep(1);
        P(table);
        if (table_used == 0)
        {
            if (generated && generated_item[0] != (int)i &&
                generated_item[1] != (int)i)
            {
                printf("SMOKER %d completed his smoking\n", (int)i);
;
                table_used = 1;
                generated = 0;
            }
        }
        V(table);
    }
}
main()
{
    pthread_t smoker1, smoker2, smoker0, agnt;
    table = semget(IPC_PRIVATE, 1, PERMS | IPC_CREAT); 
	sem_create(table, 1);
    printf("SMOKER 0 has tobacco\n");
    printf("SMOKER 1 has paper\n");
    printf("SMOKER 2 has matches\n");
    pthread_create(&agnt, 0, agent, 0);
    pthread_create(&smoker0, 0, smokeri, (void *)0);
    pthread_create(&smoker1, 0, smokeri, (void *)1);
    pthread_create(&smoker2, 0, smokeri, (void *)2);
    pthread_join(agnt, NULL);
}
