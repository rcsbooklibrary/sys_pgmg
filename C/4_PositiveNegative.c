#include<stdio.h>
void main()
{
	signed int x=0;
	printf("Enter a number\n");
	scanf("%d",&x);
	printf("You entered %d\n",x);
	if(x < 0){
		printf("Negative number\n");
	}else if(x > 0){
		printf("Positive number\n");
	}else{
		printf("Zero\n");
	}
}
