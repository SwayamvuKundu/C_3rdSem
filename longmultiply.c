#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* multiply(char* mult,char* n1,char* n2,int l1,int l2)
{int i,c=0,j,p;
if((l1==1 && n1[0]=='0') || (l2==1 && n2[0]=='0'))
return "0";
for(i=0;i<l1+l2;i++)
mult[i]='0';
for(int i=l1-1;i>=0;i--)
{c=0;
for(j=l2-1;j>=0;j--)
{p=(n1[i]-'0')*(n2[j]-'0')+(mult[i+j+1]-'0')+c;
mult[i+j+1]=p%10+'0';
c=p/10;
}
mult[i]=mult[i]+c;
}
for(i=0;i<l1+l2;i++)
{if(mult[i]!='0')
return mult+i;
}
return mult;
}
void main()
{int l1,l2;
printf("\nEnter length of first number:");
scanf("%d",&l1);
char* n1=(char*)calloc((l1+1),sizeof(char));
printf("\nEnter first number of length %d:",l1);
scanf("%s",n1);
printf("\nEnter length of second number:");
scanf("%d",&l2);
char* n2=(char*)calloc((l2+1),sizeof(char));
printf("\nEnter second number of length %d:",l2);
scanf("%s",n2);
char* mult=(char*)calloc(l1+l2+1,sizeof(char));
mult=multiply(mult,n1,n2,l1,l2);
printf("%s x %s=%s\n",n1,n2,mult);
free(n1);
free(n2);
free(mult);
}