#include<stdio.h>
#include<stdlib.h>

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
{if(search(root,newnode->data))
{printf("Value already present in BST!!\n");
return root;
}
else
{node* temp1=NULL;
node* temp2=root;
while(temp2!=NULL)
{temp1=temp2;
if(newnode->data<temp2->data)
temp2=temp2->left;
else temp2=temp2->right;
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
printf("Value %d inserted into BST\n",newnode->data);
return root;
}
}

//Function to transplant
void transplant(node** root,node* u,node* v)
{if(u->parent==NULL)
*root=v;
else if(u==u->parent->left)
u->parent->left=v;
else u->parent->right=v;
if(v!=NULL)
v->parent=u->parent;
}

//Function to find the node with minimum value in a BST subtree
node* tree_min(node* root)
{node* temp=root;
while(temp->left!=NULL)
temp=temp->left;
return temp;
}

//Function to delete a node from BST
node* treedelete(node* root,node* z)
{node* y=NULL;
if(z->left==NULL)
transplant(&root,z,z->right);
else if(z->right==NULL)
transplant(&root,z,z->left);
else 
{y=tree_min(z->right);
if(y->parent!=z)
{transplant(&root,y,y->right);
y->right=z->right;
y->right->parent=y;
}
transplant(&root,z,y);
y->left=z->left;
y->left->parent=y;
}
printf("Value %d deleted from BST\n",z->data);
free(z);
return root;
}

//Function to print the inorder traversal of the BST
void inorder(node* root)
{if(root)
{inorder(root->left);
printf("%d ",root->data);
inorder(root->right);
}
}

//Function to find the height of a node
int treeheight(node* newnode)
{if(newnode==NULL)
{return -1;
}
int lefth=treeheight(newnode->left);
int righth=treeheight(newnode->right);
return 1+(lefth>righth?lefth:righth);
}

//Function to free the nodes of the BST
void freetree(node* root)
{if(root)
{freetree(root->left);
freetree(root->right);
free(root);
}
}

//main function to implement the functions
void main()
{node* root;node* tempnode;
root=tempnode=NULL;
int ch,data,height;
do
{printf("\n1.Insert");
printf("\n2.Search");
printf("\n3.Display");
printf("\n4.Delete");
printf("\n5.Height");
printf("\n6.Exit");
printf("\nEnter choice:");
scanf("%d",&ch);
switch(ch)
{case 1:
printf("Enter Data:");
scanf("%d",&data);
tempnode=createNode(data);
root=insert(root,tempnode);
break;

case 2:
printf("Enter data:");
scanf("%d",&data);
if(search(root,data))
printf("Value found in BST\n");
else
printf("Value not found in BST\n");
break;

case 3:
printf("The inorder traversal of the BST is:\n");
inorder(root);
printf("\n");
break;

case 4:
printf("Enter value to be deleted:");
scanf("%d",&data);
tempnode=search(root,data);
if(tempnode)
root=treedelete(root,tempnode);
else
printf("Value not present in BST\n");
break;

case 5:
printf("Enter value:");
scanf("%d",&data);
tempnode=search(root,data);
if(tempnode)
{height=treeheight(tempnode);
printf("Height of the node is:%d\n",height);
}
else
printf("Value not present in BST\n");
break;

case 6:
printf("Exiting...");
freetree(root);
break;

default:
printf("Invalid Input\n");
break;
}
}while(ch!=6);
}