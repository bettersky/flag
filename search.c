#include "main.h"
extern struct HEADER *list_header;
extern pthread_mutex_t flag_add_mutex;;

struct KNODE * search_insert_point(int curr_flag_level, struct KNODE *bigger_flag_point, uint64_t searching_key, int deep){
//printf("AAA\n");
	int i;
	struct KNODE *head_recorder=list_header->key_head;//bigger_flag_point;
	//printf(">>>>>search_insert_point begin, put_counter=%d>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",put_counter);
	//printf("in search_insert_point, curr_flag_level=%d, searching_key=%s\n",curr_flag_level,  searching_key );
	

	assert(bigger_flag_point!=NULL);
	struct KNODE* stay_flag=bigger_flag_point;
	struct KNODE* searching_flag=bigger_flag_point;//->flag[curr_flag_level];//may be NULL
	
	int step=0;
//print_knode_chain("",active_chain_head);
	
	int deep_flag=0;
	
	int continue_flag=0;
//printf("BBB\n");

	while(1){
		
	printf("%u:while begin, continue_flag=%d, deep_flag=%d, deep=%d,searching_flag=%p\n",pthread_self(),continue_flag, deep_flag, deep,searching_flag);
	
		
		if(continue_flag==1){
			printf("%u:trying lock: %p\n",pthread_self(), searching_flag->flag[curr_flag_level]);
			pthread_mutex_lock( &(searching_flag->flag[curr_flag_level]->mutex) );		
				printf("%u:________________________________________lock A:%p\n",pthread_self(), searching_flag->flag[curr_flag_level]);
			struct KNODE *temp=searching_flag;
			searching_flag=searching_flag->flag[curr_flag_level];
			
			pthread_mutex_unlock( &(temp->mutex) );
				printf("%u________________________________________unlock A:%p\n",pthread_self(), temp);
			
					
		}
	if(searching_flag->flag[curr_flag_level]==NULL){
				printf("%u:break, deep=%d, searching_flag=%p\n",pthread_self(),deep,searching_flag);
				break;
	}	
			
	
		if( (deep_flag==1 || deep==0)&& continue_flag==0 ){
			printf("%u:trying lock T1:%p\n", pthread_self(),searching_flag);
			
			pthread_mutex_lock( &(searching_flag->mutex) );
			printf("%u: ________________________________________lock B:%p\n",pthread_self(), searching_flag);
		}
	
		
		deep_flag=1;
		
		step++;
		//printf("______curr_flag_level=%d, step=%d \n",curr_flag_level, step);
			
		//int com_res=searching_key-searching_flag->flag[curr_flag_level]->key;
		//printf(" searching_flag->flag[curr_flag_level]=%p\n",  searching_flag->flag[curr_flag_level]);
		//printf("%d\n", searching_key > searching_flag->flag[curr_flag_level]->key);
		
		if(searching_key > searching_flag->flag[curr_flag_level]->key){
		//printf("EEEEEEEEEEEEEEEEEEEE\n");
			//add new flag --begin
			/*
			if(step>=FLAG_LEVEL_PUFFER ){//set the searching_flag->flag[curr_flag_level] as a bigger flag
			pthread_mutex_lock(&flag_add_mutex);
				printf("insert flag --------------- \n");
				struct KNODE *temp1=searching_flag->flag[curr_flag_level];
				struct KNODE *temp2=bigger_flag_point->flag[curr_flag_level+1];
				if(temp2!=NULL && temp1->key > temp2->key ){
				
				}
				else{
					if(head_recorder->flag[curr_flag_level+1]==NULL){//if //active_table->key_head
						//printf("curr_max+++++++++, active_table->key_head=%p, bigger_flag_point=%p, head_recorder=%p\n",
								//&(active_table->key_head),bigger_flag_point,head_recorder);
						list_header->curr_max++;
					}
					searching_flag->flag[curr_flag_level]->flag[curr_flag_level+1]=bigger_flag_point->flag[curr_flag_level+1];
					bigger_flag_point->flag[curr_flag_level+1]= searching_flag->flag[curr_flag_level];
					bigger_flag_point=bigger_flag_point->flag[curr_flag_level+1];//update bigger_flag_point
					
				}
				step=0;//
			pthread_mutex_unlock(&flag_add_mutex);					
			}
			*/
			//add new flag --end
			//printf("_________________________________________________unlockA:%p\n", searching_flag);
			
			
			continue_flag=1;
		//printf("FFFFFFFFFFFFFF\n");
			continue;
		}
		else if(searching_flag->flag[0]==NULL){//this is a trick. indicate a blank list
			printf("%u:return A: %p \n ",pthread_self(), searching_flag);
			return searching_flag;		//this will make the unlock in insert operation
		}
		else if(searching_key < searching_flag->flag[curr_flag_level]->key){
			if(curr_flag_level==0){
				printf("%u:return B: %p \n ", pthread_self(),searching_flag);
				return searching_flag;//this will make the unlock in insert operation
			}
			else{
				
				return search_insert_point(curr_flag_level-1, searching_flag, searching_key,1);//this will make the unlock in deeper func
			}
		}
		else if(searching_key==searching_flag->flag[curr_flag_level]->key){
		//printf("_________________________________________________unlockB:%p\n", searching_flag);
			pthread_mutex_unlock( &(searching_flag->mutex) );
			printf("%u:________________________________________unlock E:%p\n",pthread_self(), searching_flag);

			printf("return C: %p \n ", searching_flag);
			return searching_flag->flag[curr_flag_level];
		}
	
	}
	//now the searching_flag->flag[curr_flag_level] is NULL
	if(curr_flag_level==0){
		printf("%u:return D: %p \n ",pthread_self(), searching_flag);
		return searching_flag;
	}
	else{
		
		return search_insert_point(curr_flag_level-1, searching_flag, searching_key,1);
	}
	//return searching_flag;//the searching_flag->flag[curr_flag_level] is NULL
	
	
	//printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<search_insert_point end, put_counter=%d\n",put_counter);


}