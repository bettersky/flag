#include "main.h"




extern int thread_total;

extern uint64_t size;  
extern uint64_t total;  

void *real_thread(void *args);
void *control_thread(void *args);


int  create_thread(int thread_num){


	//printf("thread:%d\n", thread_num);
	printf("begin create %d threads\n", thread_total);
	pthread_t pth[thread_total];
	pthread_t ctr;
	int i;
	
double duration=0;
struct timespec begin, end; 
clock_gettime(CLOCK_MONOTONIC,&begin); //begin insert , so begin counting 

	
	for(i=0;i<thread_total;i++){
		char arg[10];
		//sprintf(arg, "helo:%d\0",i);
		pthread_create(&(pth[i]), NULL,real_thread, (void*)arg);
		
	}
	
	for(i=0;i<thread_total;i++){
		pthread_join( pth[i], NULL);
	}
	

	//pthread_create(&ctr, NULL,control_thread,NULL);
	//for(i=0;i<thread_total;i++){
	//pthread_join(ctr, NULL);
	//}
	

	
clock_gettime(CLOCK_MONOTONIC,&end); //begin insert , so begin counting
duration=( (int)end.tv_sec+((double)end.tv_nsec)/s_to_ns ) - ( (int)begin.tv_sec+((double)begin.tv_nsec)/s_to_ns );
printf("write duration=%f s\n",duration);	


}

void *real_thread(void *args){
	//while(1);
	random_write();
}

void *control_thread(void *args){
	while(1){
		//printf("%d\n",size);
		if(size>=total){
			printf("final %d\n",size);
			break;
		}
	}

}

