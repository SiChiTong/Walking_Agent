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
#include "ServerCommunicationManager.h"

ServerCommunicationManager* ServerCommunicationManager::uniqueInstance = NULL;
//======================================
ServerCommunicationManager* ServerCommunicationManager::getUniqueInstance() {
  if (uniqueInstance == NULL)
    uniqueInstance = new ServerCommunicationManager();

  return uniqueInstance;
}
//======================================
ServerCommunicationManager::ServerCommunicationManager() {
  connected = false;
  bufSize = BUF_SIZE;
  buf = new char[bufSize];
  con = 0;
  port = 3100;
}
//======================================
ServerCommunicationManager::~ServerCommunicationManager() {
  delete buf;
}
//======================================
bool ServerCommunicationManager::connect2(unsigned int port, string hostName) {
  if (connected)
    cerr
        << "ServerCommunicationManager::connect2(): Already Connected To Server!"
        << endl;

  con = new TRoboCupConnection(hostName.c_str(), port);
  connected = con->connected();
  return connected;
}
//======================================
void ServerCommunicationManager::disconnect() {
  con->closeConnection();
  connected = false;
}
//======================================
char *ServerCommunicationManager::readMsg() {
  memset(buf, 0, bufSize);
  con->getMessage(buf, bufSize);
  return buf;
}
//======================================
bool ServerCommunicationManager::sendMsg(string msg) {
  return con->sendCommand(msg.c_str());
}
//======================================
//======================================
//======================================
//======================================
//======================================

