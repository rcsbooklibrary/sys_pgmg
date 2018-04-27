#include<stdio.h>
void main()
{
	int x=0;
	printf("Enter a number\n");
	scanf("%d",&x);
	printf("You entered %d\n",x);
	if((x%2)==0){
		printf("It is an Even number\n");
	}else{
		printf("It is an Odd number\n");
	}
}
