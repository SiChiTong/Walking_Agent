/*
 * Copyright (C) 2016 nima@ua.pt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef SERVER_COMMUNICATION_MANAGER
#define SERVER_COMMUNICATION_MANAGER

#include "Connection.h"
#include <cstdio>
#include <cstring>
using namespace std;
#define BUF_SIZE 4096

class ServerCommunicationManager {

public:

  static ServerCommunicationManager* getUniqueInstance();

  ~ServerCommunicationManager();

  bool connect(unsigned int port = 3100, string hostName = "127.0.0.1");

  void disconnect();

  char *readMsg();

  char *getMsg();

  bool sendMsg(string msg);

private:

  static ServerCommunicationManager *uniqueInstance;

  char *buf;

  unsigned int bufSize;

  string hostName;

  unsigned int port;

  bool connected;

  TRoboCupConnection *con;

  ServerCommunicationManager();

};

#endif
