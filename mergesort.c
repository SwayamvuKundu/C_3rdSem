#include <stdio.h>
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
void merge(int* arr, int left, int mid, int right) 
{  int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L;
    int* R;
    L=(int*)malloc(n1*sizeof(int));
    R=(int*)malloc(n2*sizeof(int));
    for (int i = 0; i < n1; i++) 
    L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) 
    R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {  if (L[i] <= R[j]) 
        arr[k++] = L[i++];
        else 
        arr[k++] = R[j++];
        count++;
    }
    while (i < n1) 
    arr[k++] = L[i++];
    while (j < n2) 
    arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int* arr, int left, int right)
 { if (left < right) 
 {  int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    mergeSort(arr, 0, n - 1);
    if(issort(arr,n))
    {printf("\n\nArray is sorted using merge sort");
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