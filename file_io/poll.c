#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/poll.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
	int fd,sy,i=0;
	struct pollfd fds[1];
	int poll_ret;
	ssize_t nr;
	char buf[28] ={"hello rc how are you doing"};
	int len=0;
	len = (sizeof(buf)-1);
	fd=open("/home/user/RCL/samples/file_io/write_text2.txt", O_WRONLY|O_APPEND);

	if(fd == -1){
		printf("Error opening the file\n");
	}else{
		/* In every application the below logic of checking for the complete write operation is necessary because simply issuing write with the write system call may result in partial writes */
		fds[0].fd = fd;
		fds[0].events = POLLOUT;
		poll_ret = poll(fds,1,5000);

		if (poll_ret == -1) {
			perror ("poll");
			return 1;
		}
		if (!poll_ret) {
			printf (" seconds elapsed.\n");
			return 0;
		}	

		if (fds[0].revents & POLLOUT){
			printf ("Given fd is available for writing\n");
			printf ("writing the given string into the file\n");

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

			sy =fsync(fd);
			if(sy== 0){
				printf("Successfully wrote to disk\n");
			}else{
				perror("fsync");
			}
		}else{
			printf("The given fd is not available for POLLOUT i.e reading\n");
		}
		/* fsync or fdatasync to make sure that the data is written to the disk. Else data is lost incase of crash as the data written using a write call first writes in cache and the write back process is done by the kernel later. The write function returns after writing into
		   cache which makes the operation faster */
	}
	close(fd);
}
