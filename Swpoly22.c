#include<stdio.h>
#include<stdlib.h>

typedef struct Node 
{int coeff;
int exp;
struct Node *next;
}Node;

Node *avail=NULL;//Available node list

// Function to get a new node from the avail list or create a new one
Node* getNode(int coeff,int exp) 
{Node *temp;
if(avail!=NULL)
{temp=avail;
avail=avail->next;
} 
else 
{temp=(Node *)malloc(sizeof(Node));
}
temp->coeff=coeff;
temp->exp=exp;
temp->next=temp;//Point to itself for circularity
return temp;
}

//Function to return a node to the avail list
void freeNode(Node *node) 
{node->next=avail;
avail=node;
}

//Function to insert a term in decreasing order of exponent
Node* insertTerm(Node *head, int coeff, int exp) 
{if(coeff==0)
return head;
Node *newNode = getNode(coeff, exp), *curr = head, *prev = NULL;
//Create a new list if head is NULL
if(!head) 
{newNode->next=newNode;
return newNode;
}
//If new term has a higher exponent than head, place it at start
if(exp>head->exp) 
{while (curr->next != head) 
curr=curr->next;
newNode->next=head;
curr->next=newNode;
return newNode;
}
//Insert at the correct position based on exponent
do 
{if(exp>curr->exp) 
break;
prev=curr;
curr=curr->next;
}while(curr != head);
if(prev->exp==exp)
{prev->coeff+=coeff;
if(prev->coeff==0)
{prev->next=curr->next;
freeNode(curr);
}
}
else
{// Insert the node in the list
prev->next = newNode;
newNode->next = curr;
}
return head;
}

//Function to create a polynomial
Node* createPolynomial() 
{Node *poly=NULL;
int n,coeff,exp;
printf("Enter the number of terms:");
scanf("%d",&n);
for(int i = 0; i < n; i++) 
{printf("Enter coefficient and exponent for term %d:", i+1);
scanf("%d %d",&coeff,&exp);
poly=insertTerm(poly,coeff,exp);
}
return poly;
}

//Function to display a polynomial
void displayPolynomial(Node *poly) 
{if (!poly) 
{printf("Polynomial is empty.\n");
return;
}
Node *curr = poly;
do 
{printf("%dx^%d",curr->coeff,curr->exp);
curr=curr->next;
if(curr!=poly) 
{if(curr->coeff>=0)
printf("+");
}
}while(curr!=poly);
printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node *A, Node *B) 
{Node *result=NULL;Node *pA=A,*pB = B;
//If either polynomial is NULL, return the other
if(!A && !B)
return result;
if(!A) 
{do
{
result=insertTerm(result,pB->coeff,pB->exp);
pB=pB->next;
} while(pB!=B);
return result;
}
if(!B) 
{do
{
result=insertTerm(result,pA->coeff,pA->exp);
pA=pA->next;
} while(pA!=A);
return result;
}
int completedA=0,completedB=0;  
//Flags to indicate completion of each list
// Process until we complete both polynomials
while(!completedA && !completedB) 
{if (pA->exp > pB->exp) 
{result = insertTerm(result, pA->coeff, pA->exp);
pA = pA->next;
if (pA == A) 
completedA = 1;  // We completed one cycle in A
} 
else if(pA->exp < pB->exp) 
{result = insertTerm(result, pB->coeff, pB->exp);
pB = pB->next;
if (pB == B) 
completedB = 1;  // We completed one cycle in B
} 
else 
{ // Same exponent, add coefficients
result = insertTerm(result, pA->coeff + pB->coeff, pA->exp);
pA = pA->next;
pB = pB->next;
if (pA == A) 
completedA = 1;// We completed one cycle in A
if (pB == B) 
completedB = 1;// We completed one cycle in B
}
}
// Append remaining terms from either list if they haven't been fully traversed
while(!completedA) 
{result = insertTerm(result, pA->coeff, pA->exp);
pA = pA->next;
if (pA == A) 
completedA = 1;
}
while (!completedB) 
{result = insertTerm(result, pB->coeff, pB->exp);
pB = pB->next;
if (pB == B) 
completedB = 1;
}
return result;
}

// Function to subtract two polynomials (A - B)
Node* subtractPolynomials(Node *A, Node *B) 
{Node *result = NULL;Node *pA = A, *pB = B;
// If A is NULL, return the negation of B
if(!A && !B)
return result;
if(!A) 
{
do 
{result = insertTerm(result, -pB->coeff, pB->exp);
pB = pB->next;
} 
while(pB != B);
return result;
}
//If B is NULL, return A
if(!B) 
{do
{
result=insertTerm(result,pA->coeff,pA->exp);
pA=pA->next;
} while(pA!=A);
return result;
}

int completedA = 0, completedB = 0;// Flags to indicate completion of each list
// Process terms until we complete both polynomials
while(!completedA && !completedB) 
{if (pA->exp > pB->exp) 
{result = insertTerm(result, pA->coeff, pA->exp);
pA = pA->next;
if (pA == A) 
completedA = 1;  // Completed one cycle in A
} 
else if(pA->exp < pB->exp) 
{result=insertTerm(result, -pB->coeff, pB->exp); // Subtract B's term
pB=pB->next;
if (pB==B) 
completedB = 1; // Completed one cycle in B
} 
else 
{//Same exponent, subtract coefficients
result = insertTerm(result, pA->coeff - pB->coeff, pA->exp);
pA=pA->next;
pB=pB->next;
if (pA==A) 
completedA = 1;//Completed one cycle in A
if (pB==B) 
completedB = 1;//Completed one cycle in B
}
}
//Append remaining terms from A if it hasn't been fully traversed
while(!completedA) 
{result=insertTerm(result, pA->coeff, pA->exp);
pA=pA->next;
if(pA==A) 
completedA=1;
}
//Append remaining terms from B as negative if it hasn't been fully traversed
while(!completedB) 
{result=insertTerm(result, -pB->coeff, pB->exp);
pB=pB->next;
if(pB==B) 
completedB = 1;
}
return result;
}

// Function to multiply two polynomials
Node* multiplyPolynomials(Node *A,Node *B) 
{Node *result=NULL, *pA = A, *pB;
if(!A || !B)
return result;
do 
{pB=B;
do 
{result=insertTerm(result, pA->coeff * pB->coeff, pA->exp + pB->exp);
pB=pB->next;
} while(pB!=B);
pA = pA->next;
} while(pA!=A);
return result;
}

// Function to erase a polynomial
void erasePolynomial(Node **poly) 
{Node* temp;
if(*poly!=NULL)
{temp=(**poly).next;
(**poly).next=avail;
avail=temp;
*poly=NULL;
}
}

//Function to erase the avail list
void eraseavail()
{while(avail!=NULL)
{Node* temp=avail->next;
free(avail);
avail=temp;
}
avail=NULL;
}

// Main menu-driven function
int main() 
{Node *A = NULL, *B = NULL, *result = NULL;
int choice,polyChoice;
while(1)
{printf("\nMenu:\n");
printf("1. Create polynomial (A or B)\n");
printf("2. Add polynomial (A + B)\n");
printf("3. Subtract polynomial (A - B)\n");
printf("4. Multiply polynomial (A * B)\n");
printf("5. Display polynomial (A or B)\n");
printf("6. Erase polynomial (A or B)\n");
printf("7. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice) 
{case 1:
printf("Choose polynomial to create (1 for A, 2 for B): ");
scanf("%d", &polyChoice);
if(polyChoice==1) 
{A=createPolynomial();
} 
else if(polyChoice==2) 
{B=createPolynomial();
} 
else 
{printf("Invalid polynomial choice.\n");
}
break;
case 2:
result = addPolynomials(A, B);
printf("Result of addition (A + B): ");
displayPolynomial(result);
erasePolynomial(&result);
break;
case 3:
result = subtractPolynomials(A, B);
printf("Result of subtraction (A - B): ");
displayPolynomial(result);
erasePolynomial(&result);
break;
case 4:
result = multiplyPolynomials(A, B);
printf("Result of multiplication (A * B): ");
displayPolynomial(result);
erasePolynomial(&result);
break;
case 5:
printf("Choose polynomial to display (1 for A, 2 for B): ");
scanf("%d",&polyChoice);
if(polyChoice==1) 
{
printf("Polynomial A:");
displayPolynomial(A);
} 
else if(polyChoice==2) 
{printf("Polynomial B:");
displayPolynomial(B);
} 
else 
{printf("Invalid polynomial choice.\n");
}
break;
case 6:
printf("Choose polynomial to erase (1 for A, 2 for B): ");
scanf("%d",&polyChoice);
if(polyChoice==1) 
{erasePolynomial(&A);
printf("Polynomial A erased.\n");
} 
else if(polyChoice==2)
{erasePolynomial(&B);
printf("Polynomial B erased.\n");
} 
else 
{printf("Invalid polynomial choice.\n");
}
break;
case 7:
erasePolynomial(&A);
erasePolynomial(&B);
eraseavail();
printf("Exiting...\n");
return 0;
default:
printf("Invalid choice. Please try again.\n");
}
}
return 0;
}