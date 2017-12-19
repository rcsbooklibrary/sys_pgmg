#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

int main()
{
	FILE *stream;
	int i,k;
	char str[5000]={"hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good hello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that goodhello that great one trying to write an example for every api to be familiar with..that good"};
	struct stat fileStat;	
	size_t c;
	/*Open a file stream and get the information about the file using stat api.The stat api contains the complete metadat information 
          of the file like block size , file size, file type, UID,GID etc*/
	stream =fopen("/home/user/RCL/samples/buffer_io/text_write.txt","a");
//	k = stat("/home/user/RCL/samples/buffer_io/text_write.txt",&fileStat);
	if(stream != NULL){
	//	c = fread(str,4096,fileStat.st_size-4,stream);
		/*just using the file block size to read to perform the operation faster.The clock API returns the
		  number of clock ticks per second. In this example it is proved that the operation is faster when 
                  read in integer multiples of the block size*/
		clock_t begin = clock();
		c = fwrite(str,600,2,stream);
	//	c = fread(str,512,8,stream);
		clock_t end  = clock();
		double time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
		printf("wrote: %s\n Time spent:%f\n",str,time_spent);
	}
	fclose(stream);
}
