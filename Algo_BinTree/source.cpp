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

bool deleteNode(node * pretarget, node * target, char input[]);

node * mkNode(bool type);

//  ( target , left , right )
void preorder_tranversal(node * target);

//  ( left , target , right )
void inorder_tranversal(node * target);

//  ( left , right , target )
void postorder_tranversal(node * target);

bool tellType(node * target);

bool detectNilKeyProblem(node * target);

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
			deleteNode(NULL, root, &cstrBuff[1]);
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

void insertNode(node * target, char input[]) {

	if (input[0] == '0') {
		if (target->zero != NULL)insertNode(target->zero, &input[1]);
		else {
			target->zero = mkNode(nil);
			insertNode(target->zero, &input[1]);
		}
	}
	else if (input[0] == '1') {
		if (target->one != NULL)insertNode(target->one, &input[1]);
		else {
			target->one = mkNode(nil);
			insertNode(target->one, &input[1]);
		}
	}
	else {
		if (target != NULL)target->nodeType = key;
		else {
			target = mkNode(key);
		}
	}
	return;
}

bool deleteNode(node * pretarget , node * target, char input[])
{
	bool listener = 0;
	int or01 = -1;

	if (input[0] == '0') {
		printf("0");
		or01 = 0;
		if (target->zero != NULL) { listener = deleteNode(target, target->zero, &input[1]) || listener; }
		else goto exception;
	}
	else if (input[0] == '1') {
		printf("1");
		or01 = 1;
		if (target->one != NULL)listener = deleteNode(target, target->one, &input[1]) || listener;
		else goto exception;
	}
	else {
		printf(" ]- ");
		if (target->zero == NULL && target->one == NULL) {
			printf(" nil removed\n");
			free(target);
			//   만약 1이 리턴되면 이제 그앞 재귀프로세서는 후삭제 확인을 해야한다고 알려주는것이다.
			//  만약 0이 리턴되면 그럴필요없이 끝내도 된다.
			return 1;
		}
		else if (target->nodeType == key) {
			//free(target);
			return 0;
		}
		else {
			goto exception;
			return 0;
		}
	}

	if (listener == 0)return 0;
	else if(listener == 1){
		// after get returned 
		if (or01 == 0) {
			if (pretarget == NULL) {
				goto exception;
			}
			else {
				if (pretarget->one == NULL) {
					free(target);
					pretarget->zero = NULL;
					return 1;
				}
			}
		}
		else if (or01 == 1) {
			if (pretarget == NULL) {
				goto exception;
			}
			else {
				if (pretarget->zero == NULL) {
					free(target);
					pretarget->one = NULL;
					return 1;
				}
			}

		}
	}



		exception:
	printf("delNode Func : Error occured : %s, looper\n", input);
	return 0;
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

bool detectNilKeyProblem(node * target) {
	bool t0 = 0, t1 = 0;
	if (target->one == NULL && target->zero == NULL) {
		if (target->nodeType == nil)return 1;
		else return 0;
	}

	if (target->zero != NULL) {
		if (target->zero->nodeType == key)t1 =
			t0 = detectNilKeyProblem(target->zero);
	}
	if (target->one != NULL) {
		t1 = detectNilKeyProblem(target->one);
	}
	return (t0 || t1);
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