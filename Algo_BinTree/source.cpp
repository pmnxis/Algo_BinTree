#include <stdio.h>
#include <stdlib.h>

//   VISUAL STUDIO 코딩용
#if _MSC_VER >= 1600
#pragma warning(disable:4996)
#include <Windows.h>
#define STOP { printf("\n\n"); system("PAUSE");}
#else
#define STOP {}
#endif

//  C++에는 bool이 있고 C에는 bool이없는것을 고려.
#ifndef __cplusplus
typedef int bool;
#define true   1
#define false 0
#endif

//  struct node에서 nodeType 이 0면 nil, 1이면 key로 인식
enum {
	nil = 0,
	key = 1
}nodeType;

//  싱글 링크드 리스트와 비슷한 형태로 struct구성.
struct node {
	bool nodeType;
	struct node * zero;
	struct node * one;
}typedef node;

//  재귀형식으로 input에 해당되는 노드를 만듭니다.
void insertNode(node * root, char input[]);

//  재귀형식으로 input에 해당되는 노드를 삭제하거나 nil로하고, 삭제한 노드의 부모노드를 지울수 있으면 지웁니다.
bool deleteNode(node * pretarget, node * target, char input[]);

//  지정한 type ( nil , key )에 해당되는 노드를 동적할당해서 생성한 노드의 주소를 리턴해줍니다.
node * mkNode(bool type);

//  전위순회 ( target , left , right )
void preorder_tranversal(node * target);

//  중위순회 ( left , target , right )
void inorder_tranversal(node * target);

//  후위순회 ( left , right , target )
void postorder_tranversal(node * target);

//  파라미터로 넘긴 노드가 nil인지 key인지 'N', 'K' 로 PRINTF합니다.
bool tellType(node * target);

//  파라미터로 넘긴 노드를 기준으로 그 아래 에있는 모든 노드를 메모리에서 해제합니다.
void removeTree(node * target);

int main() {
	int inputAmount = 0;
	char cstrBuff[513];
	int ii;
	// 루트노드 생성
	node * root = mkNode(nil);

	//  GET INPUT
	scanf("%d", &inputAmount);
	for (ii = 0; ii < inputAmount; ii++) {
		scanf("%s", cstrBuff);
		//  입력한 순간 실시간으로 buff의 첫번쨰 글자가 '+'면 buff의 기호 뒷부분부터 insert함수에 넘깁니다.
		if (cstrBuff[0] == '+') {
			insertNode(root, &cstrBuff[1]);
		}
		//  입력한 순간 실시간으로 buff의 첫번쨰 글자가 '-'면 buff의 기호 뒷부분부터 delete함수에 넘깁니다.
		else if (cstrBuff[0] == '-') {
			deleteNode(NULL, root, &cstrBuff[1]);
		}
		else {
			goto exception;
		}
	}

	//  PRINT RESULT  ,  전위,중위,후위 순회 차례대로 수행합니다.
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
	//  -  경로 찾기 파트 -
	//  전달 받은 배열의 맨앞 char이 '0'인지 '1'인지 확인하고 0 이면 재귀로 input[1] (바로 뒤부터)의 주소와
	//  해당하는 경로의 노드 주소를 가지고 넘긴다.
	if (input[0] == '0') {
		//  만약 가야하는 경로에 해당하는 노드가 있다면 그대로 재귀를 한다
		if (target->zero != NULL)insertNode(target->zero, &input[1]);
		else {
			//  해당하는 경로에 노드가 없다면 노드를 생성하고 링크후 , 재귀를 한다.
			target->zero = mkNode(nil);
			insertNode(target->zero, &input[1]);
		}
	}
	//  '1'도 비슷하게 진행을 한다.
	else if (input[0] == '1') {
		if (target->one != NULL)insertNode(target->one, &input[1]);
		else {
			target->one = mkNode(nil);
			insertNode(target->one, &input[1]);
		}
	}
	//  END of -  경로 찾기 파트 -

	// 만약 Input[]을 전부다 읽고 eof '0' '1'이아닌  NULL이 나오면 (다른값도 인정) 
	//  현재 위치가 생성해야할 위치라고 인지하고 KEY로서 노드를 만들고 끝낸다.
	else {
		if (target != NULL)target->nodeType = key;
		else {
			target = mkNode(key);
		}
	}
	return;
}

bool deleteNode(node * pretarget, node * target, char input[])
{
	//  -  경로 찾기 파트  -
	//  전달 받은 배열의 맨앞 char이 '0'인지 '1'인지 확인하고 '0' 이면 재귀로 input[1] (바로 뒤부터)의 주소와
	//  해당하는 경로의 노드 주소를 가지고 넘긴다. 그리고 재귀해서 받은 값이 FALSE 이면 다시 FALSE을 리턴한다.
	//  리턴 받은것이 TRUE이면 RELEAY 섹션으로 JUMP (goto) 한다.
	if (input[0] == '0') {
		//  만약 경로가 존재하지않으면 종료하기위해 FALSE를 리턴한다.
		if (target->zero == NULL)return 0;
		//  재귀를 실행 -> (자기자신, 현재 과정에서 재귀로 넘긴 일들이 다 끝나고 돌아오면) 리턴한 값을 판단해
		//  TRUE면 RELAY 섹션으로 JUMP.
		if (deleteNode(target, target->zero, &input[1]))goto relay;
		//  아니면 FALSE를 선행 과정에 반환.
		else return 0;
	}
	//  '1'인 경우도 위와 같은 과정을 거친다.
	else if (input[0] == '1') {
		if (target->one == NULL)return 0;
		if (deleteNode(target, target->one, &input[1]))goto relay;
		else return 0;
	}
	//  END of -  경로 찾기 파트  -

	//  만약 현재 삭제할 노드를 찾으면 FIRST RELAY 섹션으로 점프한다.
	else goto firstrelay;
	return 0;

	//  SECTION : RELAY
relay:
	//  RELAY섹션은 최초 삭제를 지정한 노드가 삭제한후 간선과 없어져야할 NIL을 정리하는데 사용합니다.
	//  앞에서 설명한것과 같이 다시 강조하면 
	//  [ 경로 찾기 파트 ] -> [ 앞에서 호출한 재귀와 그 재귀의 재귀 재사용 ] -> [여부에 따라 릴레이 섹션진입] -> [ 여부에 따라 선행 과정의 릴레이 섹션으로 진입]

	//  만약 pretarget이 NULL이면 이는 ROOT 이다. ROOT 노드를 삭제하면 프로그램실행에 문제가 생기므로 
	//  여부를 따지지않고 즉시 종료한다.
	if (pretarget == NULL) return 0;
	//   만약 삭제를 고려중인 노드가 자식노드가 하나도없고 key가 아닌 경우
	//  부모노드에서 왼쪽(ZERO), 오른쪽(ONE)인지 확인하고
	//  부모노드에서 타겟에 해당하는 위치의 링크(간선)을 제거한다.
	//  그후 메모리해제 후 TRUE반환.
	else if ((target->zero == NULL) && (target->one == NULL) && (target->nodeType == nil)) {
		if (pretarget->zero == target)pretarget->zero = NULL;
		if (pretarget->one == target)pretarget->one = NULL;
		free(target);
		return 1;
	}
	// 자식노드가 하나도없고 NIL , 이 것을 만족하지않으면 삭제 불가능하다고 판단하고 FALSE를 반환후 끝냄.
	// 이렇게 되면 뒤에서는 RELAY섹션을 실행하지않고 끝나게된다.
	else {
		return 0;
	}

	//   SECTION : FIRST RELAY
firstrelay:
	//  만약 pretarget이 NULL이면 이는 ROOT 이다. ROOT 노드를 삭제하면 프로그램실행에 문제가 생기므로 
	//  여부를 따지지않고 즉시 종료한다.
	if (pretarget == NULL) return 0;
	//  만약 삭제를 선택한 노드의 자식노드가 존재하지 않는다면 
	//  부모노드(pretarget)의 왼쪽(zero) , 오른쪽(one)인지 확인하고 
	//  부모노드에서 타겟에 해당하는 위치의 링크(간선)을 제거한다.
	//  그후 삭제할 노드를 메모리에서 해제한다. 그후 TRUE를 반환한다.
	else if ((target->zero == NULL) && (target->one == NULL)) {
		if (pretarget->zero == target)pretarget->zero = NULL;
		if (pretarget->one == target)pretarget->one = NULL;
		free(target);
		return 1;
	}
	else {
		//  만약 삭제할노드에 자식노드가 존재한다면 그냥 NIL속성으로 바꾸고 FALSE리턴하고 끝낸다.
		target->nodeType = nil;
		return 0;
	}

	//  exception
exception:
	printf("delNode Func : Error occured : %s, recursive\n", input);
	return 0;
}

node * mkNode(bool type) {
	//  왼쪽(zero), 오른쪽(one) 링크(간선)이 NULL인 상태로 사용자가 입력하는 노드타입으로 동적할당을한후
	// 메모리 주소를 리턴합니다.
	node * temp = (node *)malloc(sizeof(node));
	if (type == nil)temp->nodeType = nil;
	else temp->nodeType = key;
	temp->zero = NULL;
	temp->one = NULL;
	return temp;
}

//  ( root , left , right )
//  전위 순회, 재귀로 모든 노드를 탐색하면서 탐색중인 노드가 nil인지 key인지 printf해줍니다.
void preorder_tranversal(node * target) {
	tellType(target);
	if (target->zero != NULL)preorder_tranversal(target->zero);
	if (target->one != NULL)preorder_tranversal(target->one);
}

//  ( left , root , right )
//  중위 순회, 재귀로 모든 노드를 탐색하면서 탐색중인 노드가 nil인지 key인지 printf해줍니다.
void inorder_tranversal(node * target) {
	if (target->zero != NULL)inorder_tranversal(target->zero);
	tellType(target);
	if (target->one != NULL)inorder_tranversal(target->one);
}

//  ( left , right , root )
//  후위 순회, 재귀로 모든 노드를 탐색하면서 탐색중인 노드가 nil인지 key인지 printf해줍니다.
void postorder_tranversal(node * target) {
	if (target->zero != NULL)postorder_tranversal(target->zero);
	if (target->one != NULL)postorder_tranversal(target->one);
	tellType(target);
}

//  자기가 무슨 타입인지 말해줍니다.
bool tellType(node * target) {
	if (target == NULL)return 0;
	if (target->nodeType == nil)printf("N");
	else if (target->nodeType == key)printf("K");
	return target->nodeType;
}

//  후위 순회로 재귀로 트리를 전체 삭제합니다. 
void removeTree(node * target) {
	if (target->zero != NULL && target->one != NULL) {}
	else {
		if (target->zero != NULL)removeTree(target->zero);
		if (target->one != NULL)removeTree(target->one);
	}
	free(target);
	return;
}