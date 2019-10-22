#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

int main() {
    //Create a socket
    int listeninigSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeninigSocket < 0) {
        cerr << "Can't create a socket" << endl;
        return 1;
    }

    //Bind the socket to ip and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "192.168.17.32", &hint.sin_addr); // 127.0.0.1

    if (bind(listeninigSocket, (sockaddr*)&hint, sizeof(hint)) == -1) {
        cerr << "Can't bind to IP/port";
        return 2;
    }

    //Mark the socket for listening
    listen(listeninigSocket, SOMAXCONN);

    //Accept the client request
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listeninigSocket, (sockaddr *)&client, &clientSize);

    if (clientSocket == -1) {
        cerr << "Problem wih client connecting" << endl;
        return 3;
    }
    //Close the socket
    close(listeninigSocket);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

//    if(result) {
//        cout << host << " connected on " << service << endl;
//    }

    //While listening echo the message
    char buf[4096];

    while (true) {
        //Clear the buffer
        memset(buf, 0, 4096);
        int bytesRecv = recv(clientSocket, buf, 4096, 0);

        if (bytesRecv == -1) {
            cerr << "There was a connection issue" << endl;
            break;
        }
        if (bytesRecv == 0) {
            cout << "Client disconnected" << endl;
            break;
        }

        cout << "Received: " << string(buf, 0, bytesRecv) << endl;

        send(clientSocket, buf, bytesRecv + 1, 0);
    }
     //Close the socket
     close(clientSocket);
    return 0;
}