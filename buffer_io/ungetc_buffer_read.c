#define _GNU_SOURCE
#include<stdio.h>

int main()
{
	FILE *stream;
	int c,i,k;
	
	stream =fopen("/home/user/RCL/samples/file_io/text.txt","r");

	if(stream != NULL){
		for(i=0;i<200;i++){
			c = ungetc(k,stream);
			if(c != EOF){
			printf("%c",(char)c);
			}
		}
	}
}
