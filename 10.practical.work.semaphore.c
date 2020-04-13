#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void *prime(void *args){
//	printf("All prime numbers from 2 to 1,000,000:\n");
	int c = 0;
	for(int i = 2; i <= 1000000; i++){
		c = 0;
		for(int j = 1; j <= i; j++){
			if(!(i%j))
				c++;
			if(c > 2)
				break;
		}
		if (c == 2){
			sem_wait(&mutex);
            printf("%d\n", i);
            sem_post(&mutex);
        }
	}

}

void *fibonacci(void *args){
//	printf("Fibonacci sequence from 2 to 1,000,000:\n");
	int a=1,
	    b=1,
	    d;
	while(1){
		d = a + b;
		a = b;
		b = d;
		if(d > 1000000)
			break;
        sem_wait(&mutex);
		printf("%d\n", d);
        sem_post(&mutex);
	};

}

int main(){
	pthread_t id1, id2;
    sem_init(&mutex, 0, 1);//man sem_init for more info
	pthread_create(&id1, NULL, prime, NULL);
	pthread_create(&id2, NULL, fibonacci, NULL);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
    sem_destroy(&mutex);
	return 0;
}
