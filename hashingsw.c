#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TABLE_SIZE 50021//closest prime number greater than 50000
#define NUM_KEYS 50000

//Node structure for chaining
typedef struct Node 
{int key;
struct Node* next;
struct Node* prev;
}Node;

//Hash function
int hash(int key) 
{return key%TABLE_SIZE;
}

Node* createnode(int key)
{Node* newnode=(Node*)malloc(sizeof(Node));
newnode->key=key;
newnode->prev=NULL;
newnode->next=NULL;
}

//Function to insert in chaining
void insertChaining(Node* table[],int key,int* chain_lengths) 
{int index=hash(key);
Node* newNode=createnode(key);
if(table[index]==NULL)
table[index]=newNode;
else
{newNode->next=table[index];
table[index]->prev=newNode;
table[index]=newNode;
}
chain_lengths[index]++;
}

//Function to calculate chaining stats
void chainingStats(Node* table[],int* chain_lengths) 
{int min_length=TABLE_SIZE,max_length=0,total_length=0,non_empty=0;
for(int i=0;i<TABLE_SIZE;i++) 
{if(chain_lengths[i]>0) 
{non_empty++;
total_length+=chain_lengths[i];
if(chain_lengths[i]>max_length) 
max_length=chain_lengths[i];
if (chain_lengths[i]<min_length) 
min_length=chain_lengths[i];
}
}
double avg_length=(double)total_length/non_empty;
printf("Chaining:\nMin Chain Length=%d\nMax Chain Length=%d\nAvg Chain Length=%.2f", min_length, max_length, avg_length);
}

//Function to insert in linear probing
int insertLinearProbing(int table[],int key) 
{int index=hash(key);
int i=0;
int probes=0;
while(table[(index+i)%TABLE_SIZE]!=-1) 
{i++;
probes++;
if(probes==TABLE_SIZE)
return probes;
}
table[(index+i)%TABLE_SIZE]=key;
return probes+1;//Include the first probe
}

//Function to insert in quadratic probing
int insertQuadraticProbing(int table[],int key) 
{int index=hash(key),i=0,probes=0;
while(table[(index+i*i)%TABLE_SIZE]!=-1) 
{i++;
probes++;
if(probes==TABLE_SIZE)
return probes;
}
table[(index+i*i)%TABLE_SIZE]=key;
return probes+1;
}

//Function to insert in double hashing
int insertDoubleHashing(int table[],int key) 
{int index=hash(key),h2=1+(key%(TABLE_SIZE-1)),i=0,probes=0;
while(table[(index+i*h2)%TABLE_SIZE]!=-1) 
{i++;
probes++;
if(probes==TABLE_SIZE)
return probes;
}
table[(index+i*h2)%TABLE_SIZE]=key;
return probes+1;
}

void main() 
{int keys[NUM_KEYS];
Node* chainingTable[TABLE_SIZE]={NULL};
int chain_lengths[TABLE_SIZE]={0};
int linearTable[TABLE_SIZE],quadraticTable[TABLE_SIZE],doubleHashTable[TABLE_SIZE];
int totalLinearProbes=0,totalQuadraticProbes=0,totalDoubleProbes=0;
//Initialize hash tables
for(int i=0;i<TABLE_SIZE;i++) 
{linearTable[i]=-1;
quadraticTable[i]=-1;
doubleHashTable[i]=-1;
}
//Generate random keys
srand(time(NULL));
for(int i=0;i<NUM_KEYS;i++) 
{keys[i]=rand();
}
//Insert keys into the tables
for(int i=0;i<NUM_KEYS;i++) 
{insertChaining(chainingTable,keys[i], chain_lengths);
totalLinearProbes+=insertLinearProbing(linearTable,keys[i]);
totalQuadraticProbes+=insertQuadraticProbing(quadraticTable,keys[i]);
totalDoubleProbes+=insertDoubleHashing(doubleHashTable,keys[i]);
}
//Report results
chainingStats(chainingTable,chain_lengths);
printf("\n\nLinear Probing:\nAvg Probes=%.2f",(double)totalLinearProbes/NUM_KEYS);
printf("\n\nQuadratic Probing:\nAvg Probes=%.2f",(double)totalQuadraticProbes/NUM_KEYS);
printf("\n\nDouble Hashing:\nAvg Probes=%.2f",(double)totalDoubleProbes/NUM_KEYS);
}