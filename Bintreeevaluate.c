#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Defining the structure of a tree node
typedef struct Node 
{char value;
struct Node *left, *right, *parent;
}Node;

//Function to create a new tree node
Node* createNode(char value) 
{Node* newNode=(Node*)malloc(sizeof(Node));
newNode->value=value;
newNode->left=newNode->right=newNode->parent=NULL;
return newNode;
}

//Function to push a node onto the stack
void push(int* top,Node* stack[],Node* node) 
{stack[++(*top)]=node;
}

//Function to pop a node from the stack
Node* pop(Node* stack[],int* top) 
{if(*top==-1)
return NULL;
else
return stack[(*top)--];
}

//Checking if a character is an operator
int isOperator(char c) 
{return(c=='+' || c=='-' || c=='*' || c=='/');
}

//Function to build a binary expression tree from postfix expression
Node* buildExpressionTree(char* postfix,int n) 
{Node* stack[n];
int top=-1;
for (int i=0;i<n;i++) 
{char c=postfix[i];
Node* newNode=createNode(c);
if(isOperator(c)) 
{//Popping two nodes for operator
newNode->right=pop(stack,&top);
newNode->left=pop(stack,&top);
//Setting the parent pointers
if(newNode->left) 
newNode->left->parent=newNode;
if(newNode->right) 
newNode->right->parent=newNode;
}
//Pushing the new node onto the stack
push(&top,stack,newNode);
}
return pop(stack,&top);//The root of the tree
}

//Traversal functions
void preorder(Node* root) 
{if(root)
{printf("%c ",root->value);
preorder(root->left);
preorder(root->right);
}
}

void inorder(Node* root) 
{if(root)
{inorder(root->left);
printf("%c ",root->value);
inorder(root->right);
}
}

void postorder(Node* root) 
{if(root) 
{postorder(root->left);
postorder(root->right);
printf("%c ",root->value);
}
}

//Function to evaluate the expression tree
int evaluate(Node* root) 
{if(!root)
return 0;
if(!isOperator(root->value)) 
{return root->value-'0';//Converting char digit to int
}
int leftValue=evaluate(root->left);
int rightValue=evaluate(root->right);
switch(root->value) 
{case '+': return leftValue+rightValue;
case '-': return leftValue-rightValue;
case '*': return leftValue*rightValue;
case '/': return leftValue/rightValue;
}
return 0;
}

void display(Node* root,int count)
{if(root)
{display(root->right,count+1);
for(int i=1;i<=count;i++)
{printf("\t");
}
printf("%c\n",root->value);
display(root->left,count+1);
}
}

void freetree(Node* root)
{if(root)
{freetree(root->left);
freetree(root->right);
free(root);
}
}
// Main function
void main() 
{int n;
printf("Enter the number of characters in the expression: ");
scanf("%d",&n);
char postfix[n+1];
printf("Enter the postfix expression: ");
scanf("\n%[^\n]s",postfix);
// Build the binary expression tree
Node* root=buildExpressionTree(postfix, n);
printf("\n");
//Display the binary expression tree
printf("The Binary expression tree:\n\n");
display(root,0);
// Print traversals
printf("\nPreorder traversal: ");
preorder(root);
printf("\n");

printf("\nInorder traversal: ");
inorder(root);
printf("\n");

printf("\nPostorder traversal: ");
postorder(root);
printf("\n");

// Evaluate and print the result
int result = evaluate(root);
printf("\nResult of the expression: %d\n", result);
freetree(root);
}