#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void main()
{int l,h,n,i,v,f=0,a=0,b=1,c=0;
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
a=0,b=1,c=0;
for(i=2;i<=v;i++)
{c=a+b;
a=b;
b=c;
}
if(i<2)
printf("\nfib(%d)=%d",v,v);
else
printf("\nfib(%d)=%d",v,c);
f++;
}
}