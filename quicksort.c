#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static long int count=0;
void inarray(int* arr,int n)
{int v,f=0;
srand(time(NULL));
while(f<n)
{v=rand();
arr[f]=v;
f++;
}
}
int partition(int* arr,int p,int r)
{int x=arr[r];
int i=p-1;
int temp;
for(int j=p;j<=r-1;j++)
{if(arr[j]<=x)
{count++;
i=i+1;
temp=arr[i];
arr[i]=arr[j];
arr[j]=temp;
}
}
temp=arr[i+1];
arr[i+1]=arr[r];
arr[r]=temp;
return(i+1);
}
void quicksort(int* arr,int p,int r)
{if(p<r)
{int q=partition(arr,p,r);;
quicksort(arr,p,q-1);
quicksort(arr,q+1,r);
}
}
int issort(int* arr,int n)
{int i;
for(i=0;i<n-1;i++)
{if(arr[i]>arr[i+1])
return 0;
}
return 1;
}
void main() 
{ int n;
    printf("Enter the size of the array:");
    scanf("%d", &n);
    int* arr;
    arr=(int*)malloc(n*sizeof(int));
    inarray(arr,n);
    printf("The unsorted array is:\n");
    for (int i = 0; i < n; i++) 
    printf("%d ", arr[i]);
    quicksort(arr, 0, n - 1);
    if(issort(arr,n))
    {printf("\n\nArray is sorted using quick sort");
    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) 
    printf("%d ", arr[i]);
    printf("\n");
    printf("Total Number of Comparisons:%ld",count);
    }
    else
    printf("\nThe array is not sorted");
    printf("\n");
    free(arr);
}