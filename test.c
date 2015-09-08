#include "main.h"
extern struct HEADER *list_header;

int globle;
int thread_sleep=0;//100000;

uint64_t size=0;
uint64_t total=0;
int thread_total=1;
void print_tail2();
void print_list(struct KNODE *list);
pthread_mutex_t flag_add_mutex;

int test(){

	list_header=(struct HEADER *)malloc(sizeof(struct HEADER));
	memset(list_header , 0, sizeof(struct HEADER));
	list_header->key_head=(struct KNODE*)malloc(sizeof(struct KNODE));
	memset(list_header->key_head,0 , sizeof(struct KNODE));
	pthread_mutex_init(&(list_header->key_head->mutex),NULL);
	
	pthread_mutex_init(&flag_add_mutex, NULL);
	
	thread_total=20 ;
	total=100;
	
	printf("Input thread_total:\n");
	printf("Input bench size:\n");
	
	
	//scanf("%d",&thread_total);
	//scanf("%d",&total);
	
	printf("%d threads\n",thread_total);
	
	
	
	printf("%d KV\n",total);
	
	
	create_thread(0);
	//random_write();
	print_tail2();
	print_list(list_header->key_head);
	
}

void print_list(struct KNODE *list){
	while(list!=NULL){
		//printf("%llu\n",list->key);
		if(list->flag[0]==NULL ){
		}
		else if(list->key >= list->flag[0]->key){
			printf("List is not in order\n");
			exit(2);
		
		}
		list=list->flag[0];
	}
}

void print_tail2(){
	int i;
	for(i=0;i<FLAG_LEVEL_MAX;i++){
		if(list_header->key_head->flag[i]!=NULL){
			int j=0;
			struct KNODE *temp= list_header->key_head->flag[i];
			while(temp!=NULL){
				j++;
				temp=temp->flag[i];
				if(j>10000){
					printf("in tail2, j is bigger than 10000, i=%d, exit\n", i);
					exit(3);
				}
			}
			
			printf("flags in level %d:   %d\n",i,j);
		}
	}
	

}


void printx(int thread){
	//printf("%d: globle=%d\n",thread, globle);

}
void * thread1( void *para){
	while(1){
		usleep(thread_sleep);
		//printf("thread1\n");
		globle++;
		printx(1);
		if(globle>=10000){
			printf("xxxx\n");
			pthread_exit(NULL);
			printf("yyyy\n");
		}
	}
}

void * thread2( void *para){
	while(1){
		usleep(thread_sleep);
		//printf("thread2\n");
		globle++;
		printx(2);
		if(globle>=10000) pthread_exit(NULL);
	}
}