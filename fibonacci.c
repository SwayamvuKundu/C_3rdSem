#include<stdio.h>
#include<stdlib.h>
int fib(int a,int* arr)
{arr[a]++;
if(a<=1)
{return a;
}
else return fib(a-1,arr)+fib(a-2,arr);
}
void main()
{int n,ch;
printf("Enter a number:");
scanf("%d",&n);
printf("Enter 0 for iteration or 1 for recursion:");
scanf("%d",&ch);
switch(ch)
{case 0:
{int a=0,b=1,c=0,i;
for(i=2;i<=n;i++)
{c=a+b;
a=b;
b=c;
}
if(i<2)
printf("\nfib(%d)=%d",n,n);
else
printf("\nfib(%d)=%d",n,c);
break;
}
case 1:
{int val,i,sum=0;
int *arr=(int*)calloc(n,sizeof(int));
val=fib(n,arr);
printf("\nfib(%d)=%d",n,val);
for(i=0;i<n;i++)
{printf("\nNumber of times fib(%d) is called=%d",i,arr[i]);
sum=sum+arr[i];
}
printf("\nTotal Number of recursive calls:%d",sum);
free(arr);
break;
}
default:
{printf("\nInvalid Input");
break;
}
}
}


