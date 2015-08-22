#include "main.h"
extern struct HEADER *list_header;

int insert(uint64_t key){

	struct KNODE *new_key=(struct KNODE *)malloc(sizeof(struct KNODE));
	memset(new_key,0, sizeof(struct KNODE));
	new_key->key=key;
	
	if(list_header->key_head->flag[0]!=NULL){		//active_table->key_head replaces  active_chain_head
			uint64_t searching_key=key;
			struct KNODE* insert_point=search_insert_point(list_header->curr_max, list_header->key_head, searching_key);
			//int com_res=key - insert_point->key;
			if(key!=insert_point->key){//then must be >0 and less than the next key, so we insert
				new_key->flag[0]=insert_point->flag[0];
				insert_point->flag[0]=new_key;
			}
			else if(key==insert_point->key){
				//printf("YYYYYYYYYYYYYY, equal\n");
			}
	}
	else{
		//active_chain_head->next=new_kv;
		list_header->key_head->flag[0]=new_key;
	
	}
	
	//print_knode_chain("",active_chain_head);
	return 1;
	
}