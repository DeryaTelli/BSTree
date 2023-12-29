#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

typedef Node *BTREE;
BTREE newnode(int x){
	BTREE p;
	p=(BTREE)malloc(sizeof(struct node));
	p->data=x;
	p->left=p->right=NULL;
	return p;
}
BTREE insert(BTREE root , int x){
	if(root==NULL){
		root=newnode(x);
	}else{
		if(x<root->data){
			root->left=insert(root->left,x);
		}else{
			root->right=insert(root->right,x);
		}
	}
	return root; // yerinden emin degilim 
}
int height(BTREE root){
		int lheight;
		int rheight;
	if(root==NULL){
		return -1;
	}else{
	
		lheight=height(root->left);
		rheight=height(root->right);
	}
	if(rheight > lheight){
		return rheight+1;
	}else{
		return lheight+1;
	}
}
void mirror(BTREE root){
	if(root==NULL){
		return;
	}else{
		struct node* temp;
		temp=root->left;
		root->left=root->right;
		root->right=temp;
		mirror(root->left);
		mirror(root->right);
	}
}
void inorder(BTREE root){
	if(root!=NULL){
		inorder(root->left);
		printf("%d, ",root->data);
		inorder(root->right);
	}
}
BTREE delete(BTREE root , int x){
	BTREE p,q;
	if(root==NULL){
		return NULL;
	}
	if(root->data==x){
		if(root->left==root->right){
			free(root);
			return NULL;
		}
		else{
			if(root->left==NULL){
				p=root->right;
				free(root);
				return p;
			}else if(root->right==NULL){
				p=root->right;
				free(root);
				return p;
			}else{
				p=q=root->right;
				while(p->left!=NULL){
					p=p->left;
					p->left=root->left;
					free(root);
					return q;
				}
			}
		}
	}
	if(root->data<x){
		root->right=delete(root->right,x);	
	}else{
		root->left=delete(root->left,x);
	}
	return root;
}

int size (BTREE root){
	if(root==NULL){
		return 0;
	}else{
		return 1+size(root->left)+size(root->right);
	}
}
int sum(BTREE root){
	if(root==NULL){
		return 0;
	}else{
		return(root->data)+sum(root->left)+sum(root->right);
	}
}
int depth(BTREE root, int d){
	if(root==NULL){
		return 0;
	}if(d==0){
		return 1;
	}else{
		return depth(root->left,d-1)+depth(root->right,d-1);
	}
}
int main(int argc, char *argv[]) {
    BTREE myroot = NULL;
    int i;
    printf("Enter value:\n");
    scanf("%d", &i);
    while (i != -1) {
        myroot = insert(myroot, i);
        scanf("%d,", &i);
    }
    printf("Inorder tree: ");
    inorder(myroot);
    
    printf("\nHeight: %d\n", height(myroot));
    printf("\nDepth: %d\n",depth(myroot,3));
    printf("\nSize: %d\n", size(myroot));
    printf("\nSummarize: %d\n", sum(myroot));
    mirror(myroot);
    printf("After the mirror:\n");
    inorder(myroot);
    int key;
    printf("\nEnter a key: ");
    scanf("%d", &key);
    myroot = delete(myroot, key);
    printf("\nDeletion done.\n");
    inorder(myroot);
    printf("\n");
    return 0;
}
