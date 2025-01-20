#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//defining node structure
typedef struct node
{int key;
struct node* left;
struct node* right;
struct node* parent;
}node;


//creating a node of the avl tree
node* create( int data)
{node* ptr=(node*)malloc(sizeof(node));
ptr->key=data;
ptr->left=NULL;
ptr->right=NULL;
ptr->parent=NULL;
return ptr;
}

//searching for a node in avl tree
node* search(node* root,int k)
{if(root)
{if(k==root->key)
return root;
else if(k>root->key)
{
return search(root->right,k);
}
else
{
return search(root->left,k);
}
}
else
{printf("The key is not present.\n");
return NULL;
}
}

//function to find height of a node
int height(node* root)
{if(root==NULL)
return 0;
int lefth=height(root->left);
int righth=height(root->right);
if(lefth>=righth)
return lefth+1;
else return righth+1;
}

//Rotation
//Left left  Rotate
void ll(node* z,node* y )
{if(z->parent)
{if(z->parent->left==z)
{z->parent->left=y;
}
else z->parent->right=y;
}
y->parent=z->parent;
z->left=y->right;
if(y->right)
y->right->parent=z;
y->right =z;
z->parent=y;
}

//right right rotate
void rr(node* z,node* y )
{if(z->parent)
{if(z->parent->left==z)
{z->parent->left=y;
}
else z->parent->right =y;
}
y->parent=z->parent;
z->right=y->left;
if(y->left)
y->left->parent=z;
y->left =z;
z->parent=y;
}

//left right rotate
void lr(node* z ,node* y,node* x)
{rr(y,x);
ll(z,x);
}

//right left rotate
void rl(node* z,node* y,node* x)
{ll(y,x);
rr(z,x);
}

//function to check if node is balanced or not
int balance(node* root)
{int a=height(root->left);
int b=height(root->right);
if((a-b)>=-1 && (a-b)<=1) 
return 1;
else return 0;
}

//insertion into avl tree
node* insert(node * root ,int key)
{
node* ptr=root;
node* ptr2 =NULL;
while(ptr)
{if(ptr->key==key)
{printf("\nThe key %d is already present in the AVL tree\n",key);
return root;
}
else if(key>ptr->key)
{ptr2=ptr;
ptr=ptr->right;
}
else
{ptr2=ptr;
ptr=ptr->left;
}
}
printf("Key %d inserted into the AVL tree\n",key);
node* n=create(key);
if(ptr2==NULL)
{return n;
}
if(key>ptr2->key)
{ptr2->right=n;
}
else
{ptr2->left=n;
}
n->parent=ptr2;

node* x=n,*y=ptr2,*z=ptr2->parent;
while(z)
{if(!balance(z))
{if(z->left==y && y->left==x )
{ll(z,y);
if(root==z)
root=y;
}
else if(z->right==y && y->right==x){
rr(z,y);
if(root==z)
root=y;
}
else if(z->left==y && y->right==x)
{lr(z,y,x);
if(root==z)
root=x;
}
else 
{rl(z,y,x);
if(root==z)root=x;
}
break;
}
x=y;
y=z;
z=z->parent;
}
return root;
}

int getMaxDepth(node* root){
if(root==NULL)
return 0;
int leftDepth=getMaxDepth(root->left);
int rightDepth=getMaxDepth(root->right);
return 1+(leftDepth>rightDepth?leftDepth:rightDepth);
}

void printSpaces(int count)
{for(int i=0;i<count;i++)
printf("  ");
}

void printAVL(node* root)
{if(root==NULL)
{printf("Tree is empty\n");
return;
}
int maxDepth=getMaxDepth(root);
int maxWidth=pow(2,maxDepth)-1;
node** queue=(node**)malloc(maxWidth*sizeof(node));

int front=0,rear=0;
queue[rear++]=root;

for(int level=0;level<maxDepth;level++)
{int levelNodeCount=pow(2,level);
int spaceBetweenNodes=pow(2,maxDepth-level)-1;
printSpaces(spaceBetweenNodes/2);
for(int i=0;i<levelNodeCount;i++)
{node* currentNode=queue[front++];
if(currentNode!=NULL)
{printf("%d",currentNode->key);
queue[rear++]=currentNode->left;
queue[rear++]=currentNode->right;
}
else
{
printf("  ");
queue[rear++]=NULL;
queue[rear++]=NULL;
}
printSpaces(spaceBetweenNodes);
}
printf("\n");
}
free(queue);
}

//free memory
void free_memory(node* root)
{if(root)
{free_memory(root->left);
free_memory (root->right);
free(root);
}
}

//minimum
node* minimum(node* root)
{node* ptr=root;
while(ptr->left)
{ptr=ptr->left;
}
return ptr;
}


//transplant
node* transplant(node* root ,node* x,node* y)
{if(x==root)
{if(y) 
y->parent=x->parent;
return y;
}
if(y) 
{y->parent=x->parent;
}
if(x->parent->left==x)
{x->parent->left=y;
}
else
{x->parent->right=y;
}
return root;
}

//delete
node* delete(node* root,int key)
{node* z=search(root,key);
node* w=NULL;
if(z)
{printf("Key %d deleted from the AVL tree\n",key);
if(z->left==NULL)
{root=transplant(root,z,z->right);
w=z->parent;
}
else if(z->right==NULL)
{root=transplant(root,z,z->left);
w=z->parent;
}
else
{node* y=minimum(z->right);
if(y->parent!=z)
{w=y->parent;
root=transplant(root,y,y->right);
y->right=z->right;
y->right->parent=y;
}
else
{w=y;
}
root=transplant(root,z,y);
y->left=z->left;
y->left->parent=y;
}
free(z);
//check for balance
while(w)
{if(!balance(w))
{//give z,y,x correct location
z=w;
node* y,*x;
if(height(z->left)>height(z->right))
{y=z->left;
}
else y=z->right;
if(height(y->left)>height(y->right))
{x=y->left;
}
else x=y->right;
//check which balance
if(z->left==y &&y->left==x )
{ll(z,y);
if(root==z)root=y;
}
else if(z->right==y && y->right==x)
{rr(z,y);
if(root==z)
root=y;
}
else if(z->left==y && y->right==x)
{lr(z,y,x);
if(root==z)root=x;
}
else 
{rl(z,y,x);
if(root==z)
root=x;
}
}
w=w->parent;
}
}
return root;  
}

//main function to implement the functions
void main()
{node* tree=NULL;
int k,choice;
do
{printf("\n1.Insert\n");
printf("2.Delete\n");
printf("3.Search\n"); 
printf("4.Display\n"); 
printf("5.Exit\n");
printf("Enter choice:");
scanf("%d",&choice);
switch (choice)
{
case 1:
{printf("Enter key:");
int n;
scanf("%d",&n);
tree=insert(tree,n);
break;
}

case 2:
{printf("Enter key:");
scanf("%d",&k);
tree=delete(tree,k);
break;
}

case 3:
{printf("Enter key:");
scanf("%d",&k);
int depth=0;
node* temp=search(tree,k);
if(temp)
{printf("The key is present in the AVL tree\n");
}
break;
}

case 4:
{printAVL(tree);
printf("\n");
break;
}

case 5:
{printf("Exiting..\n");
free_memory(tree);
break;
}

default:
{printf("Invalid Input!!\n");
break;
}
}
}while(choice!=5);
}