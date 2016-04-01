/*
 * Copyright (C) 2016 Nima Shafii
 *
 * nima@ua.pt
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
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>

#include "etc/CommonHeaders.h"
#include "utils/MessageParser.h"
#include "utils/CommandCreator.h"
#include "utils/Connection.h"
#include "utils/ServerCommunicationManager.h"
#include "worldModel/GameConf.h"
#include "skills/RunningZMP.h"

using namespace std;

ofstream logMsg;
ServerCommunicationManager *SCM;

string hostName = "127.0.0.1";
unsigned int port = 3100;

char teamName[64] = "testAgent";
int unum = 0;
Point homePos(-4, 0.0, 0.0);

CommandCreator *CC;
WorldModel *WM;
RunningZMP *runSkill;

bool replayMode = false;
bool enableLog = false;
string logPath;

const int MAX = 12000;
char *msg = new char[MAX];

///=====================================
void readOptions(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--teamname") == 0) {
      strcpy(teamName, argv[++i]);
    } else if (strcmp(argv[i], "--unum") == 0) {
      unum = atoi(argv[++i]);
    } else if (strncmp(argv[i], "--host", 6) == 0) {
      string tmp = argv[++i];
      hostName = tmp;
    }
  }
}
///=====================================
char* readMsg() {
  memset(msg, 0, MAX);
  strcpy(msg, SCM->readMsg());
  return msg;
}
///=====================================
char* getMsg() {
  return msg;
}
///=====================================
void sendMsg(string cmd) {
  SCM->sendMsg(cmd);
}
///=====================================
bool init() {

  logMsg.open("Msg.txt");
  logMsg.close();

  cerr << teamName << ": connecting to " << hostName << ":" << port << "... ";
  SCM = ServerCommunicationManager::getUniqueInstance();
  if (!SCM->connect2(port, hostName.c_str())) {
    delete SCM;
    return false;
  }
  cout << "Done." << endl;

  CC = CommandCreator::getUniqueInstance();
  WM = WorldModel::getUniqueInstance();
  sendMsg(GameConf::getRSGPath());

  //initialize worldModel
  WM->setMyNum(unum);
  WM->setTeamName(teamName);
  char *strMessage = new char[4096];
  char *firstChar = strMessage;
  strcpy(strMessage, readMsg());
  MessageParser parser;
  parser.parseMessage(std::string(strMessage));
  GameConf::getUniqueInstance()->init();
  CC->init(unum, teamName);
  sendMsg(CC->getPreparedCommand());

  CC->reset();
  strMessage = firstChar;
  strcpy(strMessage, readMsg());
  parser.parseMessage(std::string(strMessage));

  CC->beam(-8, 0, 0);
  sendMsg(CC->getPreparedCommand());

  delete firstChar;

  return true;
}
///=====================================
void behaveWalking() {

  if (WM->getGSTime() == 0) {
    CC->stopAllJoints();
  } else {
    static bool initialized = false;

    if (!initialized) {
      initialized = true;
      runSkill = new RunningZMP;
      runSkill->init();
      runSkill->stepSizeX = 0.04;
      runSkill->stepTime = 0.4;
      runSkill->amplitude = 0;
      runSkill->amplitude2 = 0;
      runSkill->offset = 0.24;
      runSkill->swingHeight = 0.06;
      runSkill->constantInclination = 1;
      runSkill->stop = true;
      runSkill->initPos = false;
    }

    runSkill->offset = 0.23;

    double getReady = 5;
    if (WM->getGSTime() < getReady) {
      runSkill->offset = (((0.21 - 0.24) / getReady) * (WM->getGSTime()))
          + 0.24;
    } else {
      runSkill->offset = 0.21;
    }
    if (WM->getGSTime() > 6) {
      runSkill->stop = false;
    }

    runSkill->execute();

  }

}
///=====================================
void run() {
  char *strMessage = new char[4000];
  char *firstChar = strMessage;
  string msg;
  string cmd;

  while (readMsg()) {
    CC->reset();
    strMessage = firstChar;
    strcpy(strMessage, getMsg());
    logMsg.open("Msg.txt", ios::app);
    logMsg << strMessage << endl << endl;
    logMsg.close();
    MessageParser parser;
    parser.parseMessage(std::string(strMessage));
    behaveWalking();
    sendMsg(CC->getPreparedCommand());
    WM->resetForUpdate();
  }
  delete firstChar;
}

///=====================================
int main(int argc, char* argv[]) {
  cout << "\t\t* * * * < < < < <   TEST agent     > > > > > * * * *\n";

  readOptions(argc, argv);

  if (!init()) {
    return 1;
  }
  run();
  cout << "\nTest Agent exited successfully!" << endl;
  return 0;
}
