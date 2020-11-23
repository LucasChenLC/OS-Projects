#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int com_data[5];
int start = 0, end = 0;
pthread_mutex_t mutex;

void *reader(void *mode){
    int buffer[2];
    int *mod = (int *)mode;
    for(int i=0; i<10;){
        pthread_mutex_lock(&mutex);
        if (end - start >= 2) {
            buffer[0] = com_data[(start++)%5];
            buffer[1] = com_data[(start++)%5];
            i+=2;
            if (*mod)
                printf("%d + %d = %d\n", buffer[0], buffer[1], buffer[0] + buffer[1]);
            else
                printf("%d * %d = %d\n", buffer[0], buffer[1], buffer[0] * buffer[1]);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *producer(void *file_path){
    char *f  = (char *)file_path;
    FILE *fp = fopen(f, "r");
    for(int i=0; i<10;){
        pthread_mutex_lock(&mutex);
        if(end - start < 5) {
            //printf("%d %d\n", start, end);
            fscanf(fp, "%d", &com_data[(end++)%5]);
            printf("deliever data %d to pool[%d]\n", com_data[(end-1)%5], (end-1)%5);
            i++;
        }
        pthread_mutex_unlock(&mutex);
    }
    fclose(fp);
    pthread_exit(NULL);
}

int main(void){
    pthread_t r1,r2,p1,p2;
    char *file_path1 = "data1.txt";
    char *file_path2 = "data2.txt";
    int mode0 = 0, *mod0, mode1 = 1, *mod1;
    mod0 = &mode0;
    mod1 = &mode1;
    pthread_mutex_init(&mutex, NULL);
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