#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static long int count=0;
int* insert(int* arr,int n)
{int i,j,key,f,v;
srand(time(NULL));
while(f<n)
{v=rand();
arr[f]=v;
f++;
}
printf("\nThe unsorted array is:\n");
for(i=0;i<n;i++)
printf("%d ",arr[i]);
for(i=1;i<n;i++)
{key=arr[i];
j=i-1;
while(j>=0 && arr[j]>key)
{count++;
arr[j+1]=arr[j];
j--;
}
arr[j+1]=key;
}
return arr;
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
{int n,v,i;
printf("\nEnter Number of Random Numbers to be generated:");
scanf("%d",&n);
int arr[n];
insert(arr,n);
printf("\n");
if(issort(arr,n))
{printf("\nThe array is sorted");
printf("\nThe sorted array is:\n");
for(i=0;i<n;i++)
printf("%d ",arr[i]);
printf("\n");
printf("\nNumber of Comparisons:%ld\n",count);
}
else
printf("\nThe array is not sorted");
}