// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/MemManager.h"
#include "include/sbrk.h"

#ifndef ENABLE_BUDDY


typedef char ALIGN[16];

union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;
header_t *head, *tail;
// pthread_mutex_t global_malloc_lock;


header_t *get_free_block(size_t size);


void *malloc(size_t size)
{
	if(size%8!=0){
		size+=(8-size%8);
	}
	size_t total_size;
	void *block;
	header_t *header;
	if (size<=0)
		return NULL;
	// pthread_mutex_lock(&global_malloc_lock);
	header = get_free_block(size);
	if (header) {
		header->s.is_free = 0;
		// pthread_mutex_unlock(&global_malloc_lock);
		return (void*)(header + 1);
	}
	total_size = sizeof(header_t) + size;
	sbrk_handler(total_size,&block);

	if (block == NULL) {
		// pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}
	header = block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;
	if (!head)
		head = header;
	if (tail)
		tail->s.next = header;
	tail = header;
	// pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(header + 1);
}

header_t *get_free_block(size_t size)
{
	header_t *curr = head;
	header_t *next;
	int flag;
	while(curr) {
		flag=1;
		if (curr->s.is_free==1) {
			if(curr->s.size == size|| (curr->s.size>size && curr->s.size<(size+sizeof(header_t)))){
				return curr;
			}
			else if(curr->s.size > size){
				header_t * new=(header_t *)(((char *)(curr+1))+size);
				new->s.size=(curr->s.size)-size-sizeof(header_t);
				new->s.next=curr->s.next;
				new->s.is_free=1;
				curr->s.size=size;
				curr->s.next=new;
				if(curr==tail)
					tail=new;
				return curr;
			}	
			else if((next=curr->s.next)!=NULL && next->s.is_free){
				curr->s.size+=next->s.size+sizeof(header_t);
				curr->s.next=next->s.next;
				if(next==tail)
					tail=curr;	
				flag=0;
			}

		}
		if(flag)
			curr = curr->s.next;
	}
	return NULL;
}

void free(void *block)
{
	header_t *header, *tmp;
	void *programbreak;

	if (!block)
		return;
	// pthread_mutex_lock(&global_malloc_lock);
	header = (header_t*)block - 1;

	sbrk_handler(0,&programbreak);
	if ((char*)block + header->s.size == programbreak) {
		if (head == tail) {
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if(tmp->s.next == tail) {
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		}
		int x=(0 - sizeof(header_t)) - header->s.size;
		void * aux;
		sbrk_handler(x,&aux);
		// pthread_mutex_unlock(&global_malloc_lock);
		return;
	}
	header->s.is_free = 1;
	// pthread_mutex_unlock(&global_malloc_lock);
}

#endif