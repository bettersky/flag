#include "main.h"

#include <time.h>


extern uint64_t size;  
extern uint64_t total;  

int random_write(){
	//printf("i am random_write\n");	
	srand( (unsigned)time( NULL ) );
	
	for(;size<total;){		
		//printf("sdf, %d, %d\n", size, total);
		insert(rand());
		size++;
	}
	printf("end\n");

}

/*


	uint64_t i;
	uint64_t size=0;
	size=1000000;
	printf("Input size:\n");
	scanf("%llu",&size);
	printf("%llu\n",size);
	srand( (unsigned)time( NULL ) );
	
	char key[MAX_KEY_LENGTH]={0};//=malloc(10);
	char value[MAX_VALUE_LENGTH]={0};// =malloc(20);
double duration=0;
struct timespec begin, end; 
clock_gettime(CLOCK_MONOTONIC,&begin); //begin insert , so begin counting 	
	
	
	
	clock_gettime(CLOCK_MONOTONIC,&end); //begin insert , so begin counting
duration=( (int)end.tv_sec+((double)end.tv_nsec)/s_to_ns ) - ( (int)begin.tv_sec+((double)begin.tv_nsec)/s_to_ns );
printf("write duration=%f s\n",duration);		
	//int lev0_nums=0;
	
	
	//printf("lev1 tip entry %d: serial=%d, first_key=%s | last_key=%s\n",1, tip_tables_entry[1]->serial_num , tip_tables_entry[1]->first_key,  tip_tables_entry[1]->last_key);	
	

	memset(key,0,MAX_KEY_LENGTH);
		
		memset(key,0,MAX_VALUE_LENGTH);
		
		sprintf(key,"%19llu",rand());
		
		generate_string(value, MAX_VALUE_LENGTH);
		
		//printf("key=%s, value=%s\n",key,value);
*/

