#include<stdio.h>
void main()
{int n,i,j,c=1,f=0;
printf("\nEnter the number of elements n:");
scanf("%d",&n);
int A[n];
printf("Enter the array elements:");
for(i=0;i<n;i++)
{scanf("%d",&A[i]);
}
if(n==1)
{printf("Majority Element:%d",A[0]);
f=1;
}
for(i=0;i<=(n-1)/2;i++)
{c=1;
for(j=i+1;j<n;j++)
{if(A[i]==A[j])
c++;
if(c>n/2)
{printf("Majority Element:%d",A[i]);
f=1;
break;
}
}
if(f==1)
break;
}
if(f==0)
printf("No Majority Element present");
}
