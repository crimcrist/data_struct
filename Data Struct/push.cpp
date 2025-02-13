#include <stdio.h>
#include <string.h>

struct tnode {
	int valueNode;
	struct tnode *next;
}*h, *t, *c;

void pushHead (int value){
	c = (struct tnode*)malloc(sizeof(struct tnode));
	c -> valueNode = value;
	c -> next = NULL;
	if(!h){
		h = t = c;
	}else{
		c -> next = h;
		h = c;
	}
}

void pushTail (int value){
	c = (struct tnode*)malloc(sizeof(struct tnode));
	c -> valueNode = value;
	c -> next = NULL;
	if(!h){
		h = t = c;
	}else{
		t -> next = c;
		t = c;
	}
}

void pushMiddle (int value){
	c = (struct tnode*)malloc(sizeof(struct tnode));
	c -> valueNode = value;
	c -> next = NULL;
	if(!h){
		h = t = c;
	} else if(h -> valueNode > value){
		c -> next = h;
		h = c;
	} else if(t -> valueNode < value){
		t -> next = c;
		t = c;
	} else {
		struct tnode *temp;
		temp = h;
		while (value > temp -> next -> valueNode)
			temp = temp -> next;
		c -> next = temp -> next;
		temp -> next = c;
	}

