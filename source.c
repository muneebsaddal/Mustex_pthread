#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *addition();
pthread_mutex_t mutexObj = PTHREAD_MUTEX_INITIALIZER;
int arr[100];
int sum=0;

main(){
	int i;
	for (i=0; i<sizeof(arr);i++){
		arr[i]=i+1;
	}

	int thr1,thr2,thr3,thr4;
	pthread_t thread1,thread2,thread3,thread4;
	clock_t t;
	t=clock();
	thr1=pthread_create( &thread1, NULL, &addition, (int *)0);
	thr2=pthread_create( &thread2, NULL, &addition, (int *)1);
	thr3=pthread_create( &thread3, NULL, &addition, (int *)2);
	thr4=pthread_create( &thread4, NULL, &addition, (int *)3);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);

	printf("The computed sum is: %d \n",sum );
	t=clock()-t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time taken is: %f seconds \n", time_taken );
	exit(EXIT_SUCCESS);
}

void *addition(int threadID){
	pthread_mutex_lock(&mutexObj);
	int j;
	for (j=(threadID*25); j<((threadID+1)*25) ;j++){
		sum+=arr[j];
	}
	pthread_mutex_unlock(&mutexObj);
}
