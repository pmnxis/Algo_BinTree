#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 10

#if _MSC_VER >= 1600
#pragma warning(disable:4996)
#include <Windows.h>
#define STOP { printf("\n\n"); system("PAUSE");}
#else
#define STOP {}
#endif

#ifndef bool
#define bool int
#endif

enum {
	nil = 0,
	key = 1
}nodeType;

struct node {
	//bool bin;
	bool nodeType;
	node * zero;
	node * one;
}typedef node;

struct doublelist {
	doublelist * prev;
	node * data;
	doublelist * next;
}typedef doublelist;


void insertNode(node * root, char input[]);

bool deleteNode(node * target, char input[]);

node * mkNode(bool type);

//  ( target , left , right )
void preorder_tranversal(node * target);

//  ( left , target , right )
void inorder_tranversal(node * target);

//  ( left , right , target )
void postorder_tranversal(node * target);

bool tellType(node * target);

bool findEmptyNil(node * target);

void removeTree(node * target);

int main() {
	int inputAmount = 0;
	char cstrBuff[513];
	int ii;
	node * root = mkNode(nil);
		//(node *)malloc(sizeof(node));

	//  GET INPUT
	scanf("%d", &inputAmount);
	for (ii = 0; ii < inputAmount; ii++) {
		scanf("%s", cstrBuff);
		if (cstrBuff[0] == '+') {
			insertNode(root, &cstrBuff[1]);
		}
		else if (cstrBuff[0] == '-') {
			deleteNode(root, &cstrBuff[1]);
		}
		else {
			goto exception;
		}
	}

	//  PRINT RESULT
	preorder_tranversal(root);
	printf("\n");
	inorder_tranversal(root);
	printf("\n");
	postorder_tranversal(root);

	removeTree(root);
	STOP
		return 0;

	// error
exception:
	printf("main-Parse Func : Error occured : %s, looper %d\n", cstrBuff, ii);
	return 0;
}

void insertNode(node * root, char input[]) {
	node * temp = root;
	for (int i = 0; i < MAX_DEPTH; i++)
	{
		if (input[i] == '0') {
			printf(" $ ");
			if (temp->zero == NULL)temp->zero = mkNode(nil);
			else 	temp = temp->zero;
		}
		else if (input[i] == '1') {
			printf(" # ");
			if (temp->one == NULL)temp->one = mkNode(nil);
			else 	temp = temp->one;
		}
	else if (input[0] == '1') {
		if (target->one != NULL)insertNode(target->one, &input[1]);
		else {
			target->one = mkNode(nil);
			insertNode(target->one, &input[1]);
		}
	}
	else {
		if(target != NULL)target->nodeType = key;
		else {
			target = mkNode(key);
}
	}
	return;
}

bool deleteNode(node * target, char input[])
	{
	bool listener = 0;

	if (target->nodeType == key)listener = 1;

	if (input[0] == '0') {
		if (target->zero != NULL)listener = deleteNode(target->zero, &input[1]) || listener;
		else goto exception;
	}else if (input[0] == '1') {
		if (target->one != NULL)listener = deleteNode(target->one, &input[1]) || listener;
			else goto exception;
		}
		else {
		if (target->nodeType == nil) {
			free(target);
			return 0;
		}
		else if (target->nodeType == key) {
			return 1;
	}
	else {
			goto exception;
			return 1;
				}
			}

	if (listener == 0) {
		free(target);
		return 0;
		}
	else {
		return 1;
	}

exception:
	printf("delNode Fucn : Error occured : %s, looper %d", input, i);
	return;
}

node * mkNode(bool type) {
	//printf(" ^ ");
	node * temp = (node *)malloc(sizeof(node));
	//printf(" & ");
	if (type == nil)temp->nodeType = nil;
	else temp->nodeType = key;
	//printf(" ( ");
	temp->zero = NULL;
	temp->one = NULL;
	//printf(" ) ");
	return temp;
}

//  ( root , left , right )
void preorder_tranversal(node * target) {
	tellType(target);
	if (target->zero != NULL)preorder_tranversal(target->zero);
	if (target->one != NULL)preorder_tranversal(target->one);
}

//  ( left , root , right )
void inorder_tranversal(node * target) {
	if (target->zero != NULL)inorder_tranversal(target->zero);
	tellType(target);
	if (target->one != NULL)inorder_tranversal(target->one);
}

//  ( left , right , root )
void postorder_tranversal(node * target) {
	if (target->zero != NULL)postorder_tranversal(target->zero);
	if (target->one != NULL)postorder_tranversal(target->one);
	tellType(target);
}

bool tellType(node * target) {
	if (target == NULL)return 0;
	if (target->nodeType == nil)printf("N");
	else if (target->nodeType == key)printf("K");
	return target->nodeType;
}

bool findEmptyNil(node * target) {
	if (target->one == NULL && target->zero == NULL) {
		if (target->nodeType == nil)return 0;
		else return 1;

	}

	if (findEmptyNil(target) == nil)return 0;
	if (target->zero != NULL) {
		if (findEmptyNil(target->zero) == nil)return 0;
	}
	if (target->one != NULL) {
		if (findEmptyNil(target->one) == nil)return 0;
	}

	else return 1;
}

void removeTree(node * target) {
	if (target->zero != NULL && target->one != NULL) {}
	else {
		if (target->zero != NULL)removeTree(target->zero);
		if (target->one != NULL)removeTree(target->one);
	}
	free(target);
	return;
}