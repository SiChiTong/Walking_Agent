#ifndef SERVER_COMMUNICATION_MANAGER
#define SERVER_COMMUNICATION_MANAGER

#include "Connection.h"
#include <cstdio>
#include <cstring>
using namespace std;
#define BUF_SIZE 4096

class ServerCommunicationManager {

  static ServerCommunicationManager *uniqueInstance;
  char *buf;
  unsigned int bufSize;
  string hostName;
  unsigned int port;
  bool	connected;

  TRoboCupConnection *con;
  ServerCommunicationManager();

public:

  static ServerCommunicationManager* getUniqueInstance();
  //===================
  ~ServerCommunicationManager();
  //===================
  bool connect2(unsigned int port = 3100, string hostName = "127.0.0.1");
  //===================
  void disconnect();
  //===================
  char *readMsg();
  //===================
  char *getMsg(){
    return buf;
  }
  //===================
  bool sendMsg(string msg);

};

#endif
