#include<stdio.h>
void push(int* arr,int cap,int* top,int x)
{if(*top==cap-1)
  printf("\nStack is Full");
else
arr[++(*top)]=x;
}
int pop(int* arr,int* top)
{if(*top==-1)
printf("Stack is Empty");
else
return arr[(*top)--];
}
void main()
{int n;
printf("\nEnter the number of characters in the expression:");
scanf("%d",&n);
char exp[n+1];
printf("\nEnter the expression:");
scanf("\n%[^\n]s",exp);
int arr[n];
int top=-1,v,k,r;
char* ptr=exp;
while(*ptr!='\0')
{if((*ptr)=='+')
{ v=pop(arr,&top);
 k=pop(arr,&top);
r=k+v;
push(arr,n,&top,r);
}
else if((*ptr)=='-')
{ v=pop(arr,&top);
 k=pop(arr,&top);
r=k-v;
push(arr,n,&top,r);
}
else if((*ptr)=='*')
{ v=pop(arr,&top);
 k=pop(arr,&top);
r=k*v;
push(arr,n,&top,r);
}
else if((*ptr)=='/')
{ v=pop(arr,&top);
 k=pop(arr,&top);
r=k/v;
push(arr,n,&top,r);
}
else
push(arr,n,&top,*ptr-'0');
ptr++;
}
printf("The result is:%d",pop(arr,&top));
}






