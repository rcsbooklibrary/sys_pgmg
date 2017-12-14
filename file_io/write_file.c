#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
	int fd,sy,i=0;
	ssize_t nr;
	char buf[28] ={"hello rc how are you doing"};
	int len=0;
	len = (sizeof(buf)-1);
	fd=open("/home/user/RCL/samples/file_io/write_text.txt", O_WRONLY|O_APPEND);
	if(fd == -1){
		printf("Error opening the file\n");
	}else{
	/* In every application the below logic of checking for the complete write operation is necessary because simply issuing write with the write system call may result in partial writes */
		while(len != 0 && (nr = write(fd,&buf[i],len)) != 0){
			if(nr == -1){
				printf("yes a write failure case\n");	
				if(errno == EINTR){
					continue;
				}else{
					perror("write");
					break;
				}	
				len = nr-1;
				i = nr+1;		
				printf("wrote %zu bytes pending %d bytes\n",nr,len);
			}	
			printf("wrote %zu bytes : %s\n",nr,buf);
			if(nr == len)
				break;	
		}
/* fsync or fdatasync to make sure that the data is written to the disk. Else data is lost incase of crash as the data written using
a write call first writes in cache and the write back process is done by the kernel later. The write function returns after writing into
cache which makes the operation faster */
		sy =fsync(fd);
		if(sy== 0){
			printf("Successfully wrote to disk\n");
		}else{
			perror("fsync");
		}
	}
	close(fd);
}
