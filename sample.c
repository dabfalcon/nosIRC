/*
  Sample solution for NOS 2014 assignment: implement a simple multi-threaded 
  IRC-like chat service.

  (C) Paul Gardner-Stephen 2014.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

//weig0018

#include <stdio.h>//standard input output
#include <stdlib.h>//standard library
#include <unistd.h>//miscelanious symbols and types
#include <sys/socket.h>//used for socklen_t
#include <sys/ioctl.h>//function ioctl
#include <fcntl.h>//used for file control options
#include <netinet/in.h>//used for incoming ports and addresses
#include <string.h>//used for strings
#include <strings.h>//used for strings
#include <signal.h>//used for symbolic constants
#include <netdb.h>//used for hostent
#include <time.h>//used for time or timing
#include <errno.h>//used for reporting and retrieving error codes
#include <pthread.h>//used for threads
#include <ctype.h>//transforms characters
#include <sys/time.h>//used for setitimer
#include <unistd.h>//used to pause
#include <signal.h>//used for signal

struct client_thread {
  pthread_t thread;
  int thread_id;
  int fd;

  char nickname[32];

  int state;
  int user_command_seen;
  int user_has_registered;
  time_t timeout;

  char line[1024];
  int line_len;

  int next_message;
};

pthread_rwlock_t message_log_lock;

int create_listen_socket(int port)
{
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if (sock==-1) return -1;

  int on=1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1) {
    close(sock); return -1;
  }
  if (ioctl(sock, FIONBIO, (char *)&on) == -1) {
    close(sock); return -1;
  }
  
  /* Bind it to the next port we want to try. */
  struct sockaddr_in address;
  bzero((char *) &address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == -1) {
    close(sock); return -1;
  } 

  if (listen(sock, 20) != -1) return sock;

  close(sock);
  return -1;
}

int accept_incoming(int sock)
{
  struct sockaddr addr;
  unsigned int addr_len = sizeof addr;
  int asock;
  if ((asock = accept(sock, &addr, &addr_len)) != -1) {
    return asock;
  }

  return -1;
}

int main(int argc,char **argv)
{
  signal(SIGPIPE, SIG_IGN);

  int r;
  char buffer[100];
  buffer[100] = '\0';

  if (argc!=2) {
  fprintf(stderr,"usage: sample <tcp port>\n");
  exit(-1);
  }
  
  int master_socket = create_listen_socket(atoi(argv[1]));
  
  fcntl(master_socket,F_SETFL,fcntl(master_socket, F_GETFL, NULL)&(~O_NONBLOCK));  
  
  time_t start, end;
  time(&start);
  double elapsed;
  int i;
  int n;
  int quits = 0;
  char output[100];
  char nickname[32];
  char cmd[32];
  int registered = 0;
  
  while(1) {
	int client_sock = accept_incoming(master_socket);
    
    if (client_sock!=-1) {
		bzero(buffer,99);
		time(&start);
		write(client_sock,":ice 020 * : initial connection\n",32);
		while(1)
        {
			n = read(client_sock,buffer,99);
			//printf("buffer: %s\n",buffer);
			
			if (strstr(buffer,"QUIT")!=NULL) {	
				printf("Recieved Quit\n");
				//printf("%d", quits);
				//printf("\n");
				//quits+=1;
				sprintf(output,"ERROR :Closing Link: QUIT command closes connection\n");
				write(client_sock,output,strlen(output));
				close(client_sock);
				break;
			}
			
			
			else if (strstr(buffer,"JOIN")!=NULL) {
				printf("Recieved Join\n");
				sprintf(output,":ice 241 * : JOIN command sent before registration\n");
				write(client_sock,output,strlen(output));
				time(&start); //message recieved so reset timeout
			}
			
			else if (strstr(buffer,"PRIVMSG")!=NULL) {
				printf("Recieved PM: %s\n",buffer);
				if (registered) {
				sprintf(output,":ice PRIVMSG %s : PRIVMSG to self\n",nickname);
				write(client_sock,output,strlen(output));
				}
				else {
				sprintf(output,":ice 241 * : PRIVMSG command send before registration\n");
				write(client_sock,output,strlen(output));
				}
				time(&start);  //message recieved so reset timeout
			}
			
			else if (strstr(buffer,"NICK")!=NULL) {
				sscanf(buffer,"%s %s",cmd,nickname);
				printf("Recieved NICK: %s\n",nickname);
				time(&start); //message recieved so reset timeout
			}
			
			else if (strstr(buffer,"USER")!=NULL) {
				//printf("Recieved USER\n");
				registered = 1;
				sprintf(output,":ice 001 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 002 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 003 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 004 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 253 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 254 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				sprintf(output,":ice 255 %s : CREATED USER\n",nickname);
				write(client_sock,output,strlen(output));
				time(&start);  //message recieved so reset timeout
			}
			
			
			else if (elapsed>=5.0) {
				printf("Time Out\n");
				sprintf(output,"ERROR :Closing Link: waiting 5 seconds\n");
				write(client_sock,output,strlen(output));
				close(client_sock);
				break;
			}
			
			time(&end);
			elapsed = difftime(end, start);
			
		}
    }
  }
}
