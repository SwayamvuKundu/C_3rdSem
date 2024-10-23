#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int fib(int a)
{
if(a<=1)
{return a;
}
else
return fib(a-1)+fib(a-2);
}
void main()
{int l,h,n,i,v,f=0,val;
printf("\nEnter Lower Limit:");
scanf("%d",&l);
printf("\nEnter Upper Limit:");
scanf("%d",&h);
printf("\nEnter Number of Random numbers to be generated:");
scanf("%d",&n);
srand(time(NULL));
while(f<n)
{printf("\n");
v=rand() % (h-l+1)+l;
printf("\nRandom Number:%d",v);
val=fib(v);
printf("\nfib(%d)=%d",v,val);
f++;
}
}
