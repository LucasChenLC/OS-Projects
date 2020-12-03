#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int com_data[5];
int index_t;
sem_t mutex, empty, full;

void *reader(void *mode){
    int buffer[2];
    int *mod = (int *)mode;
    int count = 0;
    int flag = 0;
    do{
    sem_wait(&full);
    sem_wait(&mutex);
    count++;
    if (!flag)
        buffer[0] = com_data[index_t];
    else
        buffer[1] = com_data[index_t];
    flag = !flag;
    index_t = (index_t+4)%5;
    if (flag==0)
    {
        if(*mod)
            printf("%d + %d = %d\n", buffer[0], buffer[1], buffer[0] + buffer[1]);
        else
            printf("%d * %d = %d\n", buffer[0], buffer[1], buffer[0] * buffer[1]);
    }
    sem_post(&mutex);
    sem_post(&empty);
    if(count >= 10)
        break;
    }while(1);
}

void *producer(void *file_path){
    char *f  = (char *)file_path;
    FILE *fp = fopen(f, "r");
    int count = 0;
    do {
        sem_wait(&empty);
        sem_wait(&mutex);
        count++;
        index_t = (index_t + 1) % 5;
        fscanf(fp, "%d", &com_data[index_t]);
        sem_post(&mutex);
        sem_post(&full);
        if (count>=10)
            break;
    }while(1);
    fclose(fp);
}

int main(void){
    pthread_t r1,r2,p1,p2;
    char *file_path1 = "testcase/data1.txt";
    char *file_path2 = "testcase/data2.txt";
    int mode0 = 0, *mod0, mode1 = 1, *mod1;
    mod0 = &mode0;
    mod1 = &mode1;
    index_t = 0;
    if(sem_init(&mutex, 0, 1)<0){
        printf("Error: sem_init\n");
        return 1;
    }
    if(sem_init(&empty, 1, 5)<0){
        printf("Error: sem_init\n");
        return 1;
    }
    if(sem_init(&full, 1, 0)<0){
        printf("Error: sem_init\n");
        return 1;
    }
    pthread_create(&p1, NULL, producer, (void *)file_path1);
    pthread_create(&p2, NULL, producer, (void *)file_path2);
    pthread_create(&r1, NULL, reader, (void *)mod0);
    pthread_create(&r2, NULL, reader, (void *)mod1);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);

    return EXIT_SUCCESS;
}
