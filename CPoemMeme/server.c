#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


typedef struct node_t{
    char line[MAX];
    struct node_t* next;
    struct node_t* prev;
}node;

void printList(node* head){
    node* temp = head;
    while(temp!=NULL){
        fprintf(stderr,"%s",temp->line);
        temp = temp->next;
    }
}

void printListReverse(node* head){
    node* temp = head;
    while(temp!=NULL){
        fprintf(stderr,"%s",temp->line);
        temp = temp->prev;
    }
}

void writeListReverse(node* head, int connfd){
    node* temp = head;
    while(temp!=NULL){
        //fprintf(stderr,"%s",temp->line);
		write(connfd, temp->line, MAX); 
        temp = temp->prev;
    }
}

void freeLinks(node* Node){
    while(Node->prev!=NULL){
        Node=Node->prev;
        free(Node->next);
        Node->next=NULL;
    }
    free(Node);
}

// Function designed for chat between client and server.
void func(int connfd)
{
    node* head=NULL;
    node* ptr;
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));

        if(strncmp("Judsen",buff,6)==0){
            //fprintf(stderr,"here, %s",buff);
            break;
        }
		// print buffer which contains the client contents
		//printf("%s", buff);
        if(head==NULL){
            node* temp = malloc(sizeof(node));
            temp->prev=NULL;
            strcpy(temp->line,buff);
            head = temp;
            ptr = head;
        }else{
            node* temp = malloc(sizeof(node));
            strcpy(temp->line,buff);
            temp->prev=ptr;
            ptr->next=temp;
            ptr = ptr->next;
        }
	}
    writeListReverse(ptr,connfd);
    write(connfd,"Judsen",6);
    freeLinks(ptr);
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
