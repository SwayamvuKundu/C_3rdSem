#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//Max Heap Structure
typedef struct MaxHeap 
{int size;// Current number of elements
int cap;// Maximum capacity of the heap
int *data;// Pointer to the heap array
}MaxHeap;

//Initializing the heap with an initial capacity
void initHeap(MaxHeap *heap,int cap) 
{heap->size=0;
heap->cap=cap;
heap->data=(int*)malloc(cap*sizeof(int));
if(!heap->data) 
{printf("Memory allocation failed\n");
exit(1);
}
}

//Resizing the heap's capacity dynamically
void resizeHeap(MaxHeap *heap) 
{heap->cap*=2;
heap->data=(int*)realloc(heap->data,heap->cap*sizeof(int));
if(!heap->data) 
{printf("Memory allocation failed during resizing\n");
exit(1);
}
}

// Heapify up for insertion
void heapifyUp(MaxHeap *heap,int index) 
{if(index<=0) 
return;
int parent=(index-1)/2;
if(heap->data[parent]<heap->data[index]) 
{int temp=heap->data[parent];
heap->data[parent]=heap->data[index];
heap->data[index]=temp;
heapifyUp(heap, parent);
}
}

// Heapify down for deletion
void heapifyDown(MaxHeap *heap, int index) 
{int left=2*index+1;
int right=2*index+2;
int largest=index;
if(left<heap->size && (heap->data[left]>heap->data[largest])) 
{largest=left;
}
if(right<heap->size && (heap->data[right] > heap->data[largest])) 
{largest=right;
}
if(largest!=index) 
{int temp=heap->data[index];
heap->data[index]=heap->data[largest];
heap->data[largest]=temp;
heapifyDown(heap,largest);
}
}

// Insert a new job with priority
void insertJob(MaxHeap *heap,int priority) 
{if(heap->size>=heap->cap) 
{resizeHeap(heap);
}
heap->data[heap->size]=priority;
heapifyUp(heap,heap->size);
heap->size++;
}

// Extract the job with the highest priority
int extractMax(MaxHeap *heap) 
{if(heap->size<=0) 
{printf("Heap Underflow\n");
return -1;
}
int maxVal=heap->data[0];
heap->data[0]=heap->data[heap->size-1];
heap->size--;
heapifyDown(heap,0);
return maxVal;
}

void printspaces(int p)
{for(int i=0;i<p;i++)
printf("   ");
}

// Print the heap like a binary tree
void printHeap(MaxHeap *heap) 
{int p;
if(heap->size==0)
{printf("Heap is Empty.\n");
return;
}
printf("Heap Tree:\n");
int levels=1,count=0;
int h=(int)log2(heap->size);
int spnode=(int)pow(2,h)*3;
for(int i=0;i<heap->size;i++) 
{printspaces(spnode);
printf("%d",heap->data[i]);
count++;
if(count==levels) 
{
printf("\n\n");
levels*=2;
count=0;
spnode/=2;
}
else
printspaces(spnode);
}
printf("\n");
}

//Printing the maximum priority job
void printMax(MaxHeap *heap) 
{if(heap->size<=0) 
{printf("Heap is empty\n");
} 
else 
{printf("Max priority job: %d\n", heap->data[0]);
}
}

// Freeing the memory allocated for the heap
void freeHeap(MaxHeap *heap) 
{free(heap->data);
}

void simulateJobProcessing(char *filename) 
{FILE *file=fopen(filename, "r");
if(!file) 
{printf("Error opening file\n");
return;
}
MaxHeap heap;
initHeap(&heap,10);//Starting with a capacity of 10
int n;
int m, priority=0;
fscanf(file,"%d",&n);//Reading number of time instants
char line[500];//Array used to store a line of the file
fgets(line,sizeof(line),file);
for(int t=1;t<=n;t++) 
{printf("\nTime Instant t%d:\n",t);
fgets(line,sizeof(line), file);
int timeinstant;
sscanf(line,"time instant t%d:%d",&timeinstant,&m);
//Extracting max job and print it
if(t!=1)
{int maxPriority=extractMax(&heap);
if (maxPriority!=-1) 
printf("Processed job with priority: %d\n", maxPriority);
else
printf("No job to process!");
}
if(!strstr(line,"no new job")) 
{//Read new jobs and insert them
char *priorityPtr=strchr(line,':')+3;
printf("Inserting %d new jobs: ", m);
for(int i=0;i<m;i++) 
{sscanf(priorityPtr,"%d",&priority);
printf("%d ",priority);
insertJob(&heap,priority);
priorityPtr=strstr(priorityPtr," ");
if(priorityPtr)
priorityPtr++;
}
printf("\n");
}
printHeap(&heap);//Printing the heap after each instant
}
fclose(file);
freeHeap(&heap);//Freeing the memory at the end
}

void main() 
{char *filename="jobs.txt";
simulateJobProcessing(filename);
}