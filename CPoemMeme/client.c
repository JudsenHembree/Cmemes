#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    FILE* poem;
    char* poemName;
    char buff[MAX];
    int n;
    printf("Enter poem file as .txt: ");
    fscanf(stdin,"%s", poemName);
    poem = fopen(poemName,"r");
    assert(poem!=NULL);
    bzero(buff, MAX);
    n = 0;

    while ((fscanf(poem,"%c",&buff[n])!=EOF)){
        if(buff[n]=='\n'){
            write(sockfd, buff, MAX);
            bzero(buff, MAX);
            n=0;
            continue;
        }
        n++;
        /*
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        */
        /*
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        */
    }
    //fprintf(stderr,"sending Jud");
    write(sockfd, "Judsen", MAX);
    //fprintf(stderr,"reading");
    int i=0;
    for(;;){
        bzero(buff,MAX);
        //fprintf(stderr,"%d\n",i);
        read(sockfd,buff,MAX);
        //i++;
        if(strncmp(buff,"Judsen",6)==0){
            break;
        }
        fprintf(stderr,"%s",buff);
    }
}
   
int main()
{
    int sockfd, connfd;
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}