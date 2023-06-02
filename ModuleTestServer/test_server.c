#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "test_server.h"
#include <semaphore.h>
#define P(sem) sem_wait(&sem)
#define V(sem) sem_post(&sem)
#define P(sem2) sem_wait(&sem2)
#define V(sem2) sem_post(&sem2)
#define P(mutex) sem_wait(&mutex)
#define V(mutex) sem_post(&mutex)
#define P(mutex2) sem_wait(&mutex2)
#define V(mutex2) sem_post(&mutex2)
sem_t mutex;
sem_t mutex2;
sem_t sem;
sem_t sem2;
int actif = 0, prod = 0, back = 0, is_exec=0;

void * production(void * arg){
    if(is_exec==0){
        P(mutex);
        prod = 1;
        back = 0;
        is_exec = 1;
        creerListProd("Production", "elementProd.txt");
        V(mutex2);
        V(mutex);
    }
    return NULL;
}

void * backup(void * arg){
    if(is_exec==0){
        P(mutex);
        prod = 0;
        back = 1;
        is_exec=1;
        creerListProd("Backup", "elementBack.txt");
        V(mutex2);
        V(mutex);
    }
    return NULL;
}

void * test_disponibilite_thread(void *arg){
    P(mutex2);
     if(prod == 1){
         actif = 1;
         printf("Serveur de production actif...\n");
         save_data_log("ModLog/log.txt", "Module test dispo: Serveur de production actif pour le transfère de donnée.");
     }else{
         actif = 2;
         printf("Serveur de backup actif...\n");
         save_data_log("ModLog/log.txt", "Module test dispo: Serveur de backup actif pour le transfère de donnée.");
     }
     V(sem);
     return NULL;
}