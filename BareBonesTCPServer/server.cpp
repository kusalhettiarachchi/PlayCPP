#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>

using namespace std;

const int DPORT = 54000;
char *DIP = "192.168.17.32";

void SendMessage(string msg, int clientSocket);

int main(int argc, char *argv[]) {
    int PORT;
    char *IP;

    //We need 2 things: ip address and port number, in that order
    if(argc == 3)
    {
        PORT    = atoi(argv[2]);
        IP      = argv[1];
    } else if (argc == 2) {
        PORT    = atoi(argv[1]);
        IP      = DIP;
    } else if(argc == 1) {
        PORT    = DPORT;
        IP      = DIP;
    }
    cout << "Using " << "IP: " << IP << ", Port: " << PORT << endl;

    //Create a socket
    int listeninigSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeninigSocket < 0) {
        cerr << "Can't create a socket" << endl;
        return 1;
    }

    //Bind the socket to ip and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &hint.sin_addr);

    if (bind(listeninigSocket, (sockaddr*)&hint, sizeof(hint)) == -1) {
        cerr << "Can't bind to IP/port";
        return 2;
    }

    //Mark the socket for listening
    listen(listeninigSocket, SOMAXCONN);
    cout << "Listening on port: " << PORT << endl;

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

//    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << svc << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }

    //Send greeting
    SendMessage("Hello! Welcome.", clientSocket);

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
        string message = string(buf, 0, bytesRecv);

        if(message == "exit\r\n") {
            SendMessage("GoodBye!", clientSocket);
//            close(clientSocket);
//            close(listeninigSocket);
//            main();
            break;
        }
        else if (message == "shutdown\r\n") {
            cout << "Shut down message received" << endl;
            break;
        }
        else {
            cout << "Received: " << buf << endl;
            cout << "> ";

            //Send reply
            string reply;
            getline(cin, reply);
            SendMessage(reply, clientSocket);
        }
//        SendMessage("You said: " + buf, clientSocket);
    }
     //Close the sockets
    close(clientSocket);
    close(listeninigSocket);
    cout << "Sockets closed. Bye!" << endl;
    return 0;
}

void SendMessage(string msg, int clientSocket) {
    string replyMessage = msg + "\r\n> ";
    unsigned char reply[replyMessage.length()];
    copy(replyMessage.begin(), replyMessage.end(), reply);
    send(clientSocket, reply, sizeof(reply), 0);
}