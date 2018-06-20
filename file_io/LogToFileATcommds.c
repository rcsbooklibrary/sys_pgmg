#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<pthread.h>
#include<time.h>
#include<math.h>

#define CRASH_LOG_SIZE 1000
#define WRITE_DELAY 10

pthread_t tid;
int fd,sy,i=0;
char crb =0x0D;


int LogTime(void);
int WriteAT(char *buf, int len);
int LogData(void *BufData , int len);

void *ReadFromAT(void *arg)
{
	unsigned long j = 0;
	pthread_t id = pthread_self();
	ssize_t nr;
	char buf[CRASH_LOG_SIZE]= {0};
	int len=0;
	len = (sizeof(buf)-1);
	//fd=open("/dev/ttyAT", O_RDONLY| O_NOCTTY| O_NONBLOCK);
	fd=open("/dev/ttyAT", O_RDONLY| O_NOCTTY);
	if(fd == -1){
		printf("Error opening the file\n");
	}else{
		while(len != 0 && (nr = read(fd,&buf[j],len)) != 0){
			if(nr == -1){
				printf("yes a read failure case\n");
				perror("read");
				if(errno == EINTR){
					continue;
				}else{
					perror("read");
					break;
				}
				len = nr-1;
				j = nr+1;
				printf("read %zu bytes pending %d bytes\n",nr,len);
			}
			LogTime();
			//	LogData(tsb, sizeof(tsb));
			//	puts(buf);
			LogData(buf,sizeof(buf));
			memset(buf,' ', CRASH_LOG_SIZE-1);
		}
	}
	return NULL;
}


void main()
{
	int ret = 0;
	ret = pthread_create(&tid, NULL, &ReadFromAT, NULL);
	char GCbuf[10] ={"AT!GCDUMP"};
	while(1){
		WriteAT(GCbuf,sizeof(GCbuf)-1);
		sleep(WRITE_DELAY);
	}
}

int WriteAT( char *buf ,int len)
{
	//int fd,sy,i=0;
	ssize_t nr;
	fd=open("/dev/ttyAT", O_RDWR);
	if(fd == -1){
		printf("Error opening the file\n");
	}else{
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
			if(nr == len)
				write(fd,&crb,1);
			break;	
		}
	}
	//	close(fd);
}


int LogTime(void)
{
	char *ctme;
	time_t cur_tim;
	time(&cur_tim);
	ctme = ctime(&cur_tim);
	LogData(ctme,30);
}


int LogData(void *BufData, int len )
{
	FILE *Logfd;
	////check returns
	Logfd = fopen ( "CrashDump" ,"a+");
	//fwrite (BufData,1,CRASH_LOG_SIZE-1,Logfd);
	fprintf(Logfd,"%s\n ", BufData);
	fclose(Logfd);

} 
