#include<stdio.h>
void push(char* arr,int cap,int* top,char x)
{if(*top==cap-1)
  printf("\nStack is Full");
else
arr[++(*top)]=x;
}
char pop(char* arr,int* top)
{if(*top==-1)
printf("Stack is Empty");
else
return arr[(*top)--];
}
int check(char ptr1,char ptr2)
{if((ptr1=='+' || ptr1=='-')&&(ptr2=='*' || ptr2=='/'))
return 1;
else
return 0;
}
void main()
{int n;
printf("\nEnter the number of characters in the expression:");
scanf("%d",&n);
char exp[n+1];
printf("\nEnter the expression:");
scanf("\n%[^\n]s",exp);
char arr[n];
int top=-1;
char* ptr=exp;
printf("\nThe postfix expression is:");
printf("\n");
while(*ptr!='\0')
{if(*ptr=='+' || *ptr=='-' || *ptr=='*' || *ptr=='/')
{if(top==-1)
{
push(arr,n,&top,*ptr);
}
else if(check(arr[top],*ptr))
push(arr,n,&top,*ptr);
else
{while(!check(arr[top],*ptr))
{printf("%c",pop(arr,&top));
if(top==-1)
break;
}
push(arr,n,&top,*ptr);
}
}
else
printf("%c",*ptr);
ptr++;
}
while(top!=-1)
printf("%c",pop(arr,&top));
}