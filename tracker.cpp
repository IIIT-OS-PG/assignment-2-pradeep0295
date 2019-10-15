#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
using namespace std;
void *checkfile(void *arg){
    int *newsockfd=(int*)arg,n;
    cout<<*newsockfd<<endl;
    if (*newsockfd < 0) 
        perror("ERROR on accept");
    char buffer[256];
    bzero(buffer,256);
    n = read(*newsockfd,buffer,256);
    if (n < 0)
        perror("ERROR reading from socket");
    cout<<"file requested: "<<buffer<<endl;
    //find file
    FILE *fp = fopen("track", "rb");
    if(fp==NULL){
	 	cout<<"file not found"<<endl;
	 	//exit(1); 
	}
    else{
        
    }
	// else{//  cal size
    // fseek ( fp , 0 , SEEK_END);
	// int size = ftell ( fp );
	// rewind ( fp );
    // //ack
    // n = write(*newsockfd,"file is being sent",18);
	// send(*newsockfd ,&size,sizeof(size),0);
    // //send
	// char Buffer [ BUFF_SIZE];
	// while ((n = fread(Buffer, sizeof(char), BUFF_SIZE, fp)) > 0  && size > 0 ){
	// 	send(*newsockfd, Buffer, n, 0);
   	//  	memset(Buffer, '\0', BUFF_SIZE);
	// 	size = size - n;
	// 	}
    // if (n < 0) 
    //     perror("ERROR writing to socket");
    // fclose(fp);
    // }
    close(*newsockfd);
}
void *servercode(void *arg){
	char *s=(char*)arg;    
	char *ip=strtok(s,":");
    int portno=atoi(strtok(NULL,":"));
	cout<<ip<<portno<<endl;
    int sockfd,newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr,cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        perror("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
            perror("ERROR on binding");
    listen(sockfd,5);
    while(1){
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    pthread_t dl;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&dl,NULL,checkfile,&newsockfd);
    //pthread_join(dl,NULL);
    }
}
int main(int argc,char *argv[]){
    if(argc < 3){
        fprintf(stderr,"ERROR, mandatory arguments ip port tracker file");
        exit(1);
    }
    pthread_t server;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&server,&attr,servercode,argv[1]);
    pthread_detach(server);

    /////////quit//////////
    char buffer[6];
    cin>>buffer;
    if(strcmp(buffer,"quit")==0){
        exit(1);
    }
}        