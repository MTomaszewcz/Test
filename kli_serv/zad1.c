#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <pthread.h>


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t vkoniec = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mkoniec = PTHREAD_MUTEX_INITIALIZER;

//pthread_mutex_t m[2] = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t brak[2] = PTHREAD_COND_INITIALIZER;

int koniec = 0;
int koniec_zajete = 0;

#define MAX 80
#define PORT 8080 
#define SA struct sockaddr
#define MAXCONN 5

int sockfd, connfd[MAXCONN], len[MAXCONN];
struct sockaddr_in servaddr, cli[MAXCONN]; 

int prepare_socket()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1 )
	{ 
		printf("socket creation failed...\n"); 
		return -1; 
	} 
	else
	{
		printf("Socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
	{ 
		printf("socket bind failed...\n");
		return -2;
	} 
	else
	{	
		printf("Socket successfully binded..\n");
	}

	return 0;
}
 

int tcp_send(int fd)
{
	char buff[MAX]; 
	int n;
	printf(">> ");
	while((buff[n++] = getchar()) != '\n'){}

	write(fd, buff, sizeof(buff));

	return 0;
}

char * tcp_read(int fd)
{
	char buff[MAX]; 
	int n;
	while((buff[n++] = getchar()) != '\n'){}

	read(fd, buff, sizeof(buff));

	return buff;
}

void * czytanie(void * arg)
{
	int fd = (int)arg;

	char buf[80];
	while(1)
	{
		bzero(buf, 80);
		//printf("HEJ %d\n", fd);
		//char* a = tcp_read(fd);
		read(fd, buf, sizeof(buf));
		//printf("HOO %d\n", fd);
		pthread_mutex_lock(&m);
		printf("<< %s\n", buf);
		pthread_mutex_unlock(&m);
		if(strcmp(buf, "quit") == 0)
		{
			pthread_mutex_lock(&mkoniec);
			while(koniec_zajete == 1)
			{
				pthread_cond_wait(&vkoniec, &mkoniec );
			}
			koniec_zajete = 1;
			pthread_mutex_unlock(&mkoniec);

			koniec = 1;

			pthread_mutex_lock(&mkoniec);
			koniec_zajete = 0;
			pthread_cond_signal(&vkoniec);
			pthread_mutex_unlock(&mkoniec);

			pthread_mutex_lock(&m);
			printf("konczymy");
			pthread_mutex_unlock(&m);
			break;
		}
	}
}

void func(int ping, int pong) 
{ 
	char buff[MAX]; 
	int n;
 
	while(1)
	{ 
		bzero(buff, MAX);		
		read(ping, buff, sizeof(buff));		

		if(strncmp("quit", buff, 4) == 0)
		{
			printf("From client: %s\n", buff);
            write(pong, buff, sizeof(buff));
			printf("Server quit...\n");
			shutdown(ping, 2);
			close(ping);
            shutdown(pong, 2);
			close(pong);
			break;
		}
		else
		{
			printf("From client: %s\n", buff);
			write(pong, buff, sizeof(buff)); 
		}

        bzero(buff, MAX);		
		read(pong, buff, sizeof(buff));		

		if(strncmp("quit", buff, 4) == 0)
		{
			printf("From client: %s\n", buff);
            write(ping, buff, sizeof(buff));
			printf("Server quit...\n");
			shutdown(ping, 2);
			close(ping);
            shutdown(pong, 2);
			close(pong);
			break;
		}
		else
		{
			printf("From client: %s\n", buff);
			write(ping, buff, sizeof(buff)); 
		}
	} 
} 

int main() 
{
	prepare_socket();

	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		return 0; 
	} 
	else
	{
		printf("Server listening..\n");
	}

    for(int i=0; i<MAXCONN; i++)
	{
		//printf("Hoo %d\n", i);
		if(fork()==0)
		{
			//printf("Haa %d\n", i);
			len[i] = sizeof(cli[i]);
			connfd[i] = accept(sockfd, (SA*)&cli[i], &len[i]); 
			if (connfd[i] < 0)
			{ 
				printf("server acccept failed...\n");
				return 0;
			}
			else
			{
				printf("server acccept the client %d...\n", i);
			}
			pthread_t thrid;
			pthread_create(&thrid, NULL, czytanie, (void*)connfd[i]);	
			
			int k;
			while(1)
			{
				pthread_mutex_lock(&mkoniec);
				while(koniec_zajete == 1)
				{
					pthread_cond_wait(&vkoniec, &mkoniec );
				}
				koniec_zajete = 1;
				pthread_mutex_unlock(&mkoniec);

				k = koniec;

				pthread_mutex_lock(&mkoniec);
				koniec_zajete = 0;
				pthread_cond_signal(&vkoniec);
				pthread_mutex_unlock(&mkoniec);

				if(k==1){
					break;
				}

				tcp_send(connfd[i]);

			}

			pthread_join(thrid, NULL); 
			shutdown(connfd[i], 2);
 

		}
	}
	int status;
	for(int i=0; i<MAXCONN; i++)
	{
		wait(&status);
	}
	shutdown(sockfd, 2);
	//func(connfd[0], connfd[1]);
 
	return 0; 
} 

