#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define numRow 5 /* power of 2 (2, 4, 8, 16, ...)가 아닌 값으로 설정 */
#define numCol 10
int matrix[numRow][numCol] = {
{ 200,90,200,9,80,80,200,90,7,90 },
{ 100,30,30,51,160,160,160,51,160,59 },
{ 500,100,7000,100,900,600,100,100,650,100 },
{ 1000,300,41,300,41,41,41,900,900,950 },
{ 90,81,81,95,81,83,81,90,81,90 }
};


typedef struct node *TreePointer;
typedef struct node {
	int run;
	int value;
	int count;
	TreePointer leftChild, rightChild;
}node;

TreePointer root = NULL;

typedef struct tree {
	int run;
	int value;
	int count;
}TreeArr;

TreePointer BST_insert(TreePointer root, int value, int i) {
	if (root == NULL) {	//초기 root값 설정
		root = (node*)malloc(sizeof(node));
		root->leftChild = root->rightChild = NULL;
		root->value = value;
		root->run = i;
		root->count = 1;
		return root;
	}
	else {
		if (root->value > value) //입력받은 값이 root값보다 작을 때 ==> root의 왼쪽에 삽입
			root->leftChild = BST_insert(root->leftChild, value, i);
		else if (root->value < value) //입력받은 값이 root값보다 클 때 ==> root의 오른쪽에 삽입
			root->rightChild = BST_insert(root->rightChild, value, i);
		else
			(root->count)++;
	}
	return root;
}
void MAX_count_search(TreePointer root, int* num) {
	if (root) {
		MAX_count_search(root->leftChild, num);
		if (root->count > *num) {
			*num = root->count;
		}
		MAX_count_search(root->rightChild, num);
	}
}
void MAX_run(TreePointer root, int* num, TreePointer* temp) {
	if (root) {
		MAX_run(root->rightChild, num, temp);
		if (root->count == *num) {
			//num은 최대 count수 이므로 num++해서 다시 if문을 충족할 수 없도록 한다.
			(*num)++;
			*temp = root;
		}
		MAX_run(root->leftChild, num, temp);
	}
}
//count 크고, key값 큰 순으로 우선순위 나열하기
TreePointer traverse(TreePointer root) { //num번째 run을 찾는다.
	TreePointer temp = NULL;
	TreePointer *RUN = &temp;
	int num = 0;	//MAX값 저장
	int *ptr = &num;
	MAX_count_search(root, ptr);
	MAX_run(root, ptr, RUN);

	return temp;
}
TreeArr winner(TreeArr root1, TreeArr root2) {
	if (root1.count > root2.count) return root1;
	else if (root1.count < root2.count) return root2;
	else {	//count수가 같을 때
		if (root1.value > root2.value) return root1;
		else if (root1.value < root2.value) return root2;
		else {	//count수 ,value값 둘 다 같을 때
			if (root1.count > root2.count) return root1;
			else return root2;
		}
	}
}
TreeArr loser(TreeArr root1, TreeArr root2) {
	if (root1.count > root2.count) return root2;
	else if (root1.count < root2.count) return root1;
	else {	//count수가 같을 때
		if (root1.value > root2.value) return root2;
		else if (root1.value < root2.value) return root1;
		else {	//count수 ,value값 둘 다 같을 때
			if (root1.count > root2.count) return root2;
			else return root1;
		}
	}
}
void make_winnertree(TreeArr* ptr, int tree_level) {
	int i, j, leftmost;
	//가장 왼쪽 ==> 1,2,4(2^2),8(2^3)... 즉 (2^tree_level)
	for (i = tree_level; i > 0; i--) {
		leftmost = (int)pow(2, i);
		for (j = 0; j < leftmost; j += 2) {
			ptr[(leftmost + j) / 2] = winner(ptr[leftmost + j], ptr[leftmost + j + 1]);
		}
	}
}
void make_losertree(TreeArr* ptr, int tree_level) {
	ptr[0] = ptr[1];
	int i, j, leftmost;
	//가장 왼쪽 ==> 1,2,4(2^2),8(2^3)... 즉 (2^tree_level)
	for (i = 1; i <= tree_level; i++) {
		leftmost = (int)pow(2, i);
		for (j = 0; j < leftmost - 1; j += 2) {
			ptr[(leftmost + j) / 2] = loser(ptr[leftmost + j], ptr[leftmost + j + 1]);
		}
	}
}

void make_clean(TreePointer root) {
	root->count = 0;
	root->run = 0;
	root->value = 0;
}

int main() {
	int timeComplex = (int)sqrt(numRow) + 1;
	int loserLength = (int)pow(2, timeComplex);
	int i, run = 0;

	TreePointer BST[numRow];	//조건: row당 1개의 BST를 생성
	TreePointer temp;
	TreeArr* tptr = malloc(sizeof(TreeArr)*loserLength * 2);

	for (i = 0; i < numRow; i++) {
		root = NULL;
		for (int j = 0; j < numCol; j++)
			root = BST_insert(root, matrix[i][j], i); 	//TreePointer에 각 row별 BST 저장
		BST[i] = root;
	}

	//루저트리를 만들기 위해 leaf 노드에 각 행의 우선순위 값을 불러와 초기화한다.
	for (i = 0; i < numRow; i++) { //numRow개의 run에서 모두 가져옴.
		temp = traverse(BST[i]); //각 row의 최고 우선순위를 가져옴
		tptr[loserLength + i].value = temp->value;	//leafnode의 시작은 loserLength + i번 이다.
		tptr[loserLength + i].run = temp->run;
		tptr[loserLength + i].count = temp->count;
		make_clean(temp);
	}// 초기 run값을 loser tree 배열에 불러오기

	printf("(row,value,count)\n----------------\n");
	while (1) {
		make_winnertree(tptr, timeComplex);
		make_losertree(tptr, timeComplex);
		if (tptr[0].count == 0) break;
		printf("(%d, %d, %d)\n", tptr[0].run, tptr[0].value, tptr[0].count);
		run = tptr[0].run;	//출력되어 다시 꺼내와야 될 run의 번호
		tptr[0].run = 0; tptr[0].value = 0; tptr[0].count = 0;

		temp = traverse(BST[run]);
		tptr[loserLength + run].value = temp->value;
		tptr[loserLength + run].run = temp->run;
		tptr[loserLength + run].count = temp->count;
		make_clean(temp);
	}
}