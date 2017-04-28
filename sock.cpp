#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iomanip>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "init.h"
using namespace std;
#define MYPORT 1234    // the port users will be connecting to


int fd_A[BACKLOG];    // accepted connection fd
int conn_amount;    // current connection amount
int connect_fd;
int visit[BACKLOG] = {0};
Hero him;
Item cur;
string username;
string password;
void showclient()
{
    int i;
    printf("client amount: %d\n", conn_amount);
//    for (i = 0; i < BACKLOG; i++) {
  //      printf("[%d]:%d  ", i, fd_A[i]);
   // }
    printf("\n");
}

int i;
pugi::xml_document docs[BACKLOG];
int main(void)
{
	username = ""; password = "";
srand((unsigned)time(NULL));
    int sock_fd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct sockaddr_in server_addr;    // server address information
    struct sockaddr_in client_addr; // connector's address information
    socklen_t sin_size;
    int yes = 1;
    char buf[BUF_SIZE];
    int ret;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;         // host byte order
    server_addr.sin_port = htons(MYPORT);     // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("listen port %d\n", MYPORT);

    fd_set fdsr;
    int maxsock;
    struct timeval tv;

    conn_amount = 0;
    sin_size = sizeof(client_addr);
    maxsock = sock_fd;
    while (1) {
        // initialize file descriptor set
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);
        // timeout setting
        tv.tv_sec = 30;
        tv.tv_usec = 0;

        // add active connection to fd set
        for (i = 0; i < BACKLOG; i++) {
            if (fd_A[i] != 0) {
                FD_SET(fd_A[i], &fdsr);
            }
	    else visit[i] = 0;
        }

        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv) == 1;

        // check every fd in the set
        for (i = 0; i < conn_amount; i++) {
            connect_fd = fd_A[i];
//            if(visit[i] == 0) {
  //              doc.load_file("game.xml");
//		skout("caonima\n");
  //              visit[i]++;
    //        }
            if (FD_ISSET(fd_A[i], &fdsr)) {
string buff;
skin(buff);
cout << buff;
		if(visit[i] == 0) {
		    docs[i].load_file("game.xml");
		    doc = docs[i];
		    init();
			string scur = him.getAttr("cur");
			string query = "//scene/name[text()=\"" + scur + "\"]/..";
			cur.self = doc.select_node(query.c_str()).node();
		    visit[i]++;
		}
		else {
		    int cmdl = processStr(buff);
		    switch(cmdl){
			case 449: shows(); break; //show
			case 425: mines(); break; //mine
			case 528: craft(); break; //craft
			case 632: if(!atack()){
				close(fd_A[i]);
				visit[i] = 0;
				fd_A[i] = 0;
				} break; //attack
			case 431: saves(); break; //save
			case 416: loads(); break; //load
			case 210: me(); break; //me
			case 298: bag(); break; //bag
			case 316: help(); break; // man
			case 333: use();  break; //use
			case 441: gotos(); break; //goto
			case 314: eat(); break; //eat			
			case 317: see(); break; //make
			case 537: login(); break; //login
			case 330: news(); break; //new
			case 628: create(); break; //create
			default: skout("The rest is silence. \n", CYAN); break;
            }}}
}
        // check whether a new connection comes
        if (FD_ISSET(sock_fd, &fdsr)) {
            new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
            showclient();
//            if (new_fd <= 0) {
  //              perror("accept");
    //            continue;
      //      }

            // add to fd queue
            if (conn_amount < BACKLOG) {
		for(int j = 0; j < BACKLOG; ++j) {
		    if(fd_A[j] == 0) {
			fd_A[j] = new_fd;
			if(j == conn_amount){ conn_amount++; printf("%d", j);}
			break;
		    }
		}
                printf("new connection client[%d] %s:%d\n", conn_amount,
                        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if (new_fd > maxsock)
                    maxsock = new_fd;
            }
            else {
                printf("max connections arrive, exit\n");
                send(new_fd, "bye", 4, 0);
                close(new_fd);
                break;
            }
        }
    }

    // close other connections
    for (i = 0; i < BACKLOG; i++) {
        if (fd_A[i] != 0) {
            close(fd_A[i]);
        }
    }

    exit(0);
}

bool skout(string s, string color){
    if(s.size() == 0) return true;
    s = color + s + RESET;
    if(send(connect_fd, s.c_str(), s.size(), 0) == -1) return false;
    else return true;
}

void skin(string & buff){
    unsigned char str[256];
    int n = recv(connect_fd, str, MAXLINE, 0);
    str[n] = '\0';
    if(n <= 0 && errno != EINTR){
	close(fd_A[i]);
	visit[i] = 0;
	fd_A[i] = 0;
    }
    buff = (char *)str;
    if(buff[buff.size() - 1] == '\n' && buff[buff.size() - 2] == '\r'){
    buff.erase(buff.end() - 2, buff.end());
    }
    cout << buff.size();
    for(int m = 0; m < buff.size();++m) printf(" %x", buff[m]);
    cout << endl;
}
