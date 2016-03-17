#include "ServerCommunicationManager.h"

ServerCommunicationManager* ServerCommunicationManager::uniqueInstance = NULL;
//======================================
ServerCommunicationManager* ServerCommunicationManager::getUniqueInstance(){
  if(uniqueInstance == NULL)
    uniqueInstance = new ServerCommunicationManager();

  return uniqueInstance;
}
//======================================
ServerCommunicationManager::ServerCommunicationManager(){
  connected = false;
  bufSize = BUF_SIZE;
  buf = new char[bufSize];
  con=0;
  port=3100;
}
//======================================
ServerCommunicationManager::~ServerCommunicationManager(){
  delete buf;
}
//======================================
bool ServerCommunicationManager::connect2(unsigned int port, string hostName){
  if(connected)
    cerr<< "ServerCommunicationManager::connect2(): Already Connected To Server!"<< endl;

  con = new TRoboCupConnection(hostName.c_str(), port);
  connected = con->connected();
  return connected;
}
//======================================
void ServerCommunicationManager::disconnect(){
  con->closeConnection();
  connected = false;
}
//======================================
char *ServerCommunicationManager::readMsg(){
  memset(buf, 0, bufSize);
  con->getMessage(buf, bufSize);
  return buf;
}
//======================================
bool ServerCommunicationManager::sendMsg(string msg){
  return con->sendCommand( msg.c_str() );
}
//======================================
//======================================
//======================================
//======================================
//======================================

