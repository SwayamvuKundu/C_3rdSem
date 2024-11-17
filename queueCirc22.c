#include <stdio.h>
#include <stdlib.h>
//Define the node structure for the circular singly linked list
struct Node
{int data;
struct Node* next;
};

//Define the queue structure with a pointer to the head (rear node)
struct Queue 
{struct Node* head;
};

//Function to create a new node
struct Node* createNode(int value)
{struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
newNode->data=value;
newNode->next=newNode;//Point to itself to make it circular
return newNode;
}

//Function to create an empty queue
struct Queue* createQueue() 
{struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
q->head=NULL;
return q;
}

//Function to enqueue (add) an element to the queue
void enqueue(struct Queue* q,int value) 
{struct Node* newNode=createNode(value);
if(q->head==NULL) 
{//If the queue is empty, initialize head to new node
q->head=newNode;
newNode->next=newNode;//Make it circular
} 
else 
{//Insert newNode after head and move head to newNode to keep it at the rear
newNode->next=q->head->next;//newNode points to front node
q->head->next=newNode;// Rear node points to new node
q->head=newNode;// Update rear to new node
}
printf("Enqueued %d\n", value);
}

//Function to dequeue(remove) an element from the queue
void dequeue(struct Queue* q) 
{if(q->head==NULL) 
{printf("Queue is empty\n");
return;
}
struct Node* frontNode=q->head->next;//Get the front node(head->next)
//If there is only one element in the queue
if(q->head==frontNode) 
{printf("Dequeued %d\n", frontNode->data);
free(frontNode);
q->head=NULL;//Queue is now empty
} 
else 
{//Remove the front node by updating the rear's next pointer
printf("Dequeued %d\n", frontNode->data);
q->head->next=frontNode->next;//Rear node points to the next front
free(frontNode);//Free the old front node
}
}

//Function to count the number of elements in the queue
int countElements(struct Queue* q)
{if(q->head==NULL) 
{return 0;
}
int count=1;//Start counting from the front node
struct Node* temp=q->head->next;//Start from front

while(temp!=q->head)//Traverse until we reach rear(head) again
{count++;
temp=temp->next;
}
return count;
}

//Function to print the queue
void printQueue(struct Queue* q) 
{if(q->head==NULL) 
{printf("Queue is empty\n");
return;
}
struct Node* temp=q->head->next;//Start from the front
printf("Queue elements:");
do 
{printf("%d ",temp->data);
temp=temp->next;
}while (temp!=q->head->next);//Stop when we return to front
printf("\n");
//Print front and rear elements
printf("Front element:%d\n",q->head->next->data);//Front is next to head
printf("Rear element:%d\n",q->head->data);//Rear is the head itself
}

//Function to free all nodes in the queue and the queue structure itself
void freeQueue(struct Queue* q) 
{if(q->head==NULL)
{free(q);//If the queue is empty, just free the Queue structure
return;
}
struct Node* current=q->head->next;//Start from the front
struct Node* nextNode;
//Traverse and free each node until we come back to head
while(current!=q->head) 
{nextNode=current->next;
free(current);
current=nextNode;
}
//Free the head node
free(q->head);
//Finally, free the queue structure itself
free(q);
printf("Queue memory freed\n");
}

//Main function to test the queue operations
void main()
{struct Queue* q=createQueue();
int choice,value;
while(1) 
{printf("\n1)Enqueue\n2)Dequeue\n3)Count Elements\n4)Print Queue\n5)Exit\n");
printf("Enter your choice:");
scanf("%d",&choice);
switch(choice)
{
case 1:
printf("Enter the value to enqueue:");
scanf("%d",&value);
enqueue(q,value);
break;

case 2:
dequeue(q);
break;

case 3:
printf("Number of elements in the queue:%d\n",countElements(q));
break;

case 4:
printQueue(q);
break;

case 5:
freeQueue(q);
printf("Exiting...\n");
exit(0);
break;

default:
printf("Invalid choice, please try again.\n");
}
}
}