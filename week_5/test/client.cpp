#include <iostream>
#include <string>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 1234
using namespace std;
int main()
{
  int sockfd;
  char buff[1024];
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = PORT;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  // Initialize socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Connect to server
  connect(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);
  // Send message
  while (1)
  {
    cout << "\nEnter message: ";
    fgets(buff, 1024, stdin);
    send(sockfd, buff, sizeof buff + 1, 0);
    cout << "Data sent successfully."
         << endl;
  }
}