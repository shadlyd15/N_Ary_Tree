#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "debug.h"

#define N       (10)

struct node_t{
    void * data;
    struct node_t * child[N];
};

struct node_t * create_node(void * data){
    struct node_t * node = (struct node_t *)malloc(sizeof(struct node_t));
    if(node){
    	node->data = data;
	    for (size_t i = 0; i < N; ++i){
	        node->child[i] = NULL;
	    }
		return node;
	}
	DEBUG_ERROR("Memory Allocation Failed");
	return NULL;
}

typedef void (*callback)(struct node_t * node);

void traverse_callback(struct node_t * node){
	DEBUG_OK("Node :: %p : %s", node, (char*)node->data);
}

int itr = 0;
void traverse_tree(struct node_t * node, callback cb){
	if((node != NULL) && (cb != NULL)){
		size_t i = 0;
		cb(node);
		while(node->child[i] && (i < N)){
			if(node->child[i]){
				traverse_tree(node->child[i], cb);
			}
			i++;
		}
	}
}

void get_leaves_callback(struct node_t * node){
	DEBUG_OK("Leaf :: %p : %s", node, (char*)node->data);
}

void get_leaves(struct node_t * node, callback cb){
	if(node && cb){
		size_t i = 0;
		if(NULL == node->child[i]){
			cb(node);
		}
		else{
			while(node->child[i]){
				if(node->child[i]){
					get_leaves(node->child[i], cb);
				}
				i++;
			}
		}
	}
}

void delete_node(struct node_t * node){
	for(size_t i = 0; i < N; i++){
		if(node->child[i]){
			DEBUG_OK("%s", node->data);
			delete_node(node->child[i]);
		}
		else{
			DEBUG_OK("There");
			free(node);
			node = NULL;
		}
	}
}

int main(int argc, char const *argv[]){
	DEBUG_DIVIDER('*', 50);
	DEBUG_OK("N-Ary Tree Test");
	DEBUG_DIVIDER('*', 50);
	struct node_t * root = create_node("root");
	root->child[0] = create_node("root->child[0]");
	root->child[1] = create_node("root->child[1]");
	root->child[0]->child[0] = create_node("root->child[0]->child[0]");
	root->child[0]->child[1] = create_node("root->child[0]->child[1]");
	root->child[1]->child[0] = create_node("root->child[1]->child[0]");
	root->child[2] = create_node("root->child[2]");
	traverse_tree(root, traverse_callback);
	DEBUG_DIVIDER('*', 50);

	// delete_node(root);

	// get_leaves(root, get_leaves_callback);
	// DEBUG_DIVIDER('*', 50);
	// free(root->child[0]->child[0]);
	// free(root->child[0]->child[1]);
	// free(root->child[1]->child[0]);
	// free(root->child[0]);
	// free(root->child[1]);
	// free(root->child[2]);
	// free(root);

	// root->child[0]->child[0] = NULL;
	// root->child[0]->child[1] = NULL;
	// root->child[1]->child[0] = NULL;
	// root->child[0] = NULL;
	// root->child[1] = NULL;
	// root->child[2] = NULL;
	// root->child[3] = NULL;
	// root->child[4] = NULL;
	// root = NULL;

	get_leaves(root, get_leaves_callback);
	DEBUG_DIVIDER('*', 50);
	traverse_tree(root, traverse_callback);
	DEBUG_DIVIDER('*', 50);
	// DEBUG_OK("Iteration : %d", itr);
	return 0;
}