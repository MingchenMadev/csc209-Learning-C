#include <stdio.h>
#include "gc.h"
#include "gc_list.h"
#include "gc_tree.h"

mem_chunk * root;

/* A wrapper around malloc to keep track of dynamically allocated memory
 */
void *gc_malloc(int nbytes){
	mem_chunk * r = root;
	mem_chunk * m = malloc(sizeof(struct mem_chunk));
	m->address = malloc(sizeof(nbytes));
	m->in_use = USED;
	if(r == NULL){
		root = m;
	}
	while(r != NULL){
		if(r->next == NULL){
			r->next = r;
		}
		r = r->next;
	}
	return m->address;
}

/* Executes the garbage collector.
 * mark_obj will traverse the data structure rooted at obj, calling
 * mark_one for each dynamically allocated chunk of memory to mark
 * that it is still in use.
 */

void *mark_obj(void*obj){

}


void mark_and_sweep(void *obj, void (*mark_obj)(void *)){
	//Step1, Reset:
	mem_chunk * r = root;
	while(r != NULL){
		r->in_use = NOT_USED;
		r = r->next;
	}

	//Step2, Make:
	mark_obj(obj);

	//Step3,Sweep:
	mem_chunk * r2 = root;
	if(r2 != NULL){
		while(r2->next!= NULL){
			if(r2->next->in_use = NOT_USED){
				free(r2->next->address);
			}
			tmp = r2->next->next;
			free(r2->next);
			r2->next = tmp;
		}
		if(r2->next == NULL){
			if(r2->in_use = NOT_USED){
				free(r2->next->address);
			}
			free(r2);
		}
	}
}
/* Mark vptr as still in use
 * Return code:
 *   0 on success
 *   1 if memory chunk pointed to by vptr was already marked as in use
 */
int mark_one(void *vptr){
	mem_chunk *r = root;
	if(r == NULL){
		return 0
	}
	while(r =! NULL){
		if(r->address = vptr){
			if(r->in_use = USED){
				return 1;
			}
			else{
				r->in_use = USED;
				return 0;
			}
		}
		r = r->next;
	}
}






