#include <iostream>
#include <string>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 1234
#define BACKLOG 5
using namespace std;
int main()
{
  int sockfd, clientfd;
  char buff[1024], ipstr[INET6_ADDRSTRLEN];
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len;
  client_len = sizeof client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = PORT;
  // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_addr.s_addr = INADDR_ANY;
  // Initialize socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Bind socket to local port
  bind(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);
  // Start listening on opened port
  listen(sockfd, BACKLOG);
  cout << "Listening on " << PORT << "..." << endl;
  // Accept connection request from client
  clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
  inet_ntop(AF_INET, &client_addr.sin_addr, ipstr, sizeof ipstr);
  cout << "Accepted connection from " << ipstr << ".\n"
       << endl;
  // Recieve messages from server
  while (1)
  {
    recv(clientfd, buff, sizeof buff, 0);
    cout << "Message recieved: " << buff << "\n"
         << endl;
  }
}