#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static long int count=0;

//Defining the structure of a node of the BST
typedef struct node
{int data;
struct node* left;
struct node* right;
struct node* parent;
}node;

//Function to create a new node
node* createNode(int newdata)
{node* newnode=(node*)malloc(sizeof(node));
newnode->data=newdata;
newnode->left=NULL;
newnode->right=NULL;
newnode->parent=NULL;
return newnode;
}

//Function to search a value in the BST
node* search(node* root,int k)
{if(!root || k==root->data)
return root;
if(k<root->data)
return search(root->left,k);
else return search(root->right,k);
}

//Function to insert a value into the BST
node* insert(node* root ,node* newnode)
{node* temp1=NULL;
node* temp2=root;
while(temp2!=NULL)
{temp1=temp2;
if(newnode->data<temp2->data)
temp2=temp2->left;
else temp2=temp2->right;
count++;
}
newnode->parent=temp1;
if(temp1==NULL)
root=newnode;
else if(newnode->data<temp1->data)
{temp1->left=newnode;
newnode->parent=temp1;
}
else 
{temp1->right=newnode;
newnode->parent=temp1;
}
count++;
return root;
}

void freetree(node* root)
{if(root)
{freetree(root->left);
freetree(root->right);
free(root);
}
}

void main()
{int n;
node* root=NULL;
node* newnode=NULL;
printf("\nEnter Number of values to be inserted in BST:");
scanf("%d",&n);
int f=0,v;
srand(time(NULL));
while(f<n)
{v=rand()+rand()+rand()+rand()+rand();
if(!search(root,v))
{newnode=createNode(v);
root=insert(root,newnode);
f++;
}
}
printf("%d values successfully inserted into BST",n);
printf("\nNumber of comparisons:%ld",count);
freetree(root);
}
