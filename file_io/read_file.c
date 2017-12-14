/**/
#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
	int fd,i=0;
	ssize_t nr;
	char buf[28];
	int len=0;
	len = (sizeof(buf)-1);
	fd=open("/home/user/RCL/samples/file_io/text.txt", O_RDONLY);
	if(fd == -1){
		printf("Error opening the file\n");
	}else{
		while(len != 0 && (nr = read(fd,&buf[i],len)) != 0){
			if(nr == -1){
				printf("yes a read failure case\n");	
				if(errno == EINTR){
					continue;
				}else{
					perror("read");
					break;
				}	
				len = nr-1;
				i = nr+1;		
			printf("read %zu bytes pending %d bytes\n",nr,len);
			}	
			printf("read %zu bytes : %s\n",nr,buf);
		}
	}
	if(close(fd) == -1){
	perror("close");
	}else{
	printf("closed the file\n");
	}
}
