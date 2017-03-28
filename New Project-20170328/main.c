#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem0,sem1;


void* func (void* arg)
{
    int n=*((int*)arg);

    sem_t* sem_begin;
    sem_t* sem_end;
    
    sem_begin=  (n) ? &sem0 : &sem1;
    sem_end=   (!n) ? &sem0 : &sem1;
    
    
    for(int idx=0;idx<20;++idx)
    {
        sem_wait(sem_begin);        
        printf("%d  ",idx*2+n);
        fflush(stdout);
        sem_post(sem_end);
    }
    return NULL;
}


int main()
{
    int a=0;
    int b=1;
    pthread_t id0,id1;

    sem_init(&sem0, 0, 0);    
    sem_init(&sem1, 0, 1);    

    pthread_create (&id0, NULL, &func, &a);
    pthread_create (&id1, NULL, &func, &b);
    
    pthread_join(id0,NULL);
    pthread_join(id1,NULL);
    
    printf("\n");
    
    return 0;
}

