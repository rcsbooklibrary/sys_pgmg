#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	FILE *stream;
	int i,k;
	char str[5000];
	struct stat fileStat;	
	size_t c;
	/*Open a file stream and get the information about the file using stat api.The stat api contains the complete metadat information 
          of the file like block size , file size, file type, UID,GID etc*/
	stream =fopen("/home/user/RCL/samples/file_io/text.txt","r");
	k = stat("/home/user/RCL/samples/file_io/text.txt",&fileStat);
	if(stream != NULL){
	//	c = fread(str,4096,fileStat.st_size-4,stream);
		c = fread(str,4096,1,stream);
		printf("File Size : %d\n Block size :%d\n %s\n",(int)fileStat.st_size,(int)fileStat.st_blksize,str);
	}
}
