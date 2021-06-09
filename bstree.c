#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#define ARRAY_LENGTH 20
//二叉树

typedef int KEY_VALUE;

//二叉树性质数据结构和业务分离
#if 0
struct bstree_node { //结点

	KEY_VALUE data;
	struct bstree_node *left;
	struct bstree_node *right;

};

//二叉树结构
struct bstree {
	struct bstree_node *root;
};

#else

#define BSTREE_ENTRY(name, type) \
	struct name {		\
		struct type *left; \
		struct type *right; \
	}

struct bstree_node {
	KEY_VALUE data;
	BSTREE_ENTRY(,bstree_node) bst;
};


struct bstree {
	struct bstree_node *root;
	struct bstree_node *nil;	//不指向空，而是开辟一个叶子结点
};

#endif 
/*
struct sched {

	struct bstree_node *ready;
	struct bstree_node *defer;
	struct bstree_node *sleep;
	struct bstree_node *wait;

};

struct sched {

	BSTREE_ENTRY(,bstree_node) ready;
	BSTREE_ENTRY(,bstree_node) defer;
	BSTREE_ENTRY(,bstree_node) sleep;
	BSTREE_ENTRY(,bstree_node) wait;

};

*/


//创建一个结点 内部函数
struct bstree_node *_bstree_create_node(KEY_VALUE key)
{
	//堆上创建
	struct bstree_node *node = (struct bstree_node*)malloc(sizeof(struct bstree_node));
	if (node == NULL){
		//assert(0);
		return NULL;
	}

	node->data = key;
	node->bst.left = node->bst.right = NULL;

	return node;

}


/////////////////////////////////api////////////////////
//查找 search
//search()
struct bstree_node * bstree_search(struct bstree *T, KEY_VALUE key){

	//空树	
	if (T == NULL) return NULL;
	//根结点也是空的
	if (T->root == NULL) return NULL;

	struct bstree_node *node = T->root;
	struct bstree_node *tmp = T->root;

	while(node != NULL){
		tmp = node;
		if (key == node->data){
			return node;	
		}
	}

	return NULL;
}

//插入  插入后就是在叶子结点 insert
int bstree_insert(struct bstree *T, KEY_VALUE key){
	//1 异常判断	
	if (T == NULL){
	 	printf("bstree_insert T is NULL!!! \n");      
		return -1; //树为空
	}

	//2 只是根结点
	if (T->root == NULL) {
	 	printf("bstree_insert T->root is NULL!!! key:%d\n", key);      
		T->root = _bstree_create_node(key);
		return 0;
	}

	//3 不只e根结点  二叉树无法回缩
	struct bstree_node *node = T->root;
	struct bstree_node *tmp = T->root;

	while(node != NULL){
		
		tmp = node;
		if (key <node->data){
			node = node->bst.left;
		}else if (key > node->data){
			node = node->bst.right;
		}else{
			//相同的结点不插入  尽量不插入重复结点，不方便查找
			return -2;
		}
	}	
	
	if (key < tmp->data){ //分配空间
		tmp->bst.left = _bstree_create_node(key);
	}else{
		tmp->bst.right = _bstree_create_node(key);
	}

	return 0;
}

//删除 delete
//delete()
int bstree_delete(struct bstree *T, KEY_VALUE key){
	//删除当前结点和左右子树	

	return 0;
}

//更改 update
//update() 先删除一个结点，然后再添加这个结点

//遍历 traversal
//前中后层次遍历  递归和非递归(需要接入一个队列实现)
int bstree_traversal(struct bstree_node *node)
{
	if (node == NULL) return 0;
	
	bstree_traversal(node->bst.left);
	printf("%4d", node->data);
	bstree_traversal(node->bst.right);

	return 0;
}



int main()
{
	//测试代码

	int keyArray[ARRAY_LENGTH] = {24,25,13,35,23, 26,67,47,38,98, 20,13,17,49,12, 21,9,18,14,15};

	struct bstree T = {0};
	int i = 0;
	for (i = 0;i < ARRAY_LENGTH;i ++) {
		bstree_insert(&T, keyArray[i]);
	}

	bstree_traversal(T.root);

	printf("\n");

	return 0;
}


