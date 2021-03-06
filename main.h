#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>
#include <string.h>
#include <assert.h>
#define FLAG_LEVEL_MAX 50
#define FLAG_LEVEL_PUFFER 5

#define s_to_ns 1000000000	

struct KNODE{
	uint64_t key;
	pthread_mutex_t mutex;
	struct KNODE *flag[FLAG_LEVEL_MAX];

};

struct HEADER{

	struct KNODE *key_head;
	int curr_max;
}; 


int test();
int random_write();
int insert(uint64_t key);
struct KNODE * search_insert_point(int curr_flag_level, struct KNODE *bigger_flag_point, uint64_t searching_key, int deep);

int  create_thread(int thread_num);
#endif