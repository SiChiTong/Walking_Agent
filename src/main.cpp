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
/// \define Reading the input arguments to the binary
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
/// \define Read the message that is sent by the simulator to the agent's socket
char* readMsg() {
  memset(msg, 0, MAX);
  strcpy(msg, SCM->readMsg());
  return msg;
}

///=====================================
/// \define getter of the message
char* getMsg() {
  return msg;
}

///=====================================
/// \define Send the effector message of the agent to the simulator socket
void sendMsg(string cmd) {
  SCM->sendMsg(cmd);
}

///=====================================
/// \define Initial the agent functionalities
bool init() {

  logMsg.open("Msg.txt");
  logMsg.close();

  // initial the agents connection
  cerr << teamName << ": connecting to " << hostName << ":" << port << "... ";
  SCM = ServerCommunicationManager::getUniqueInstance();

  if (!SCM->connect(port, hostName.c_str())) {
    delete SCM;
    return false;
  }

  cout << "Done." << endl;

  // Initial the commands creator
  CC = CommandCreator::getUniqueInstance();

  // Initial the world model
  WM = WorldModel::getUniqueInstance();
  sendMsg(GameConf::getRSGPath());
  WM->setMyNum(unum);
  WM->setTeamName(teamName);

  // Receive the first messages from the simulator and extract the the primary information
  // to update the world model
  char *strMessage = new char[4096];
  char *firstChar = strMessage;
  strcpy(strMessage, readMsg());
  MessageParser parser;
  parser.parseMessage(std::string(strMessage));
  GameConf::getUniqueInstance()->init();

  // Send the first messages to the simulator to spawn the agent in simulator
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
/// \define An interface and to execute walking. This is rather slow walking how ever it can
/// perform walking in both Gazebo and Simspark simulator.
/// The parameters of the walk is set in this function. To understand the parameters for
/// tuning them, check RunningZMP.h.
void behaveWalking() {

  // start the behavior only in play_on mode
  if (WM->getGSTime() == 0) {
    CC->stopAllJoints();
  }
  else {
    static bool initialized = false;

    if (!initialized) {
      initialized = true;
      runSkill = new RunningZMP;
      runSkill->init();

      // The walk engine parameters
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

    // Prepare to be in walking posture in the first 6 seconds
    double getReady = 5;
    if (WM->getGSTime() < getReady) {
      runSkill->offset = (((0.21 - 0.24) / getReady) * (WM->getGSTime()))
          + 0.24;
    } else {
      runSkill->offset = 0.21;
    }
    if (WM->getGSTime() > 6) {

      // start walking
      runSkill->stop = false;
    }

    runSkill->execute();

  }

}

///=====================================
/// \define The main loop of the agent, including sense, think, act.
/// First, the agent receives the sense messages, and extracts the information from it.
/// Second, the agent decides to execute the walking behavior.
/// Finally, the agent sends to the simulator its effector messages, and wait to receive
/// the next cycle of the sense messages.
void run() {

  char *strMessage = new char[4000];
  char *firstChar = strMessage;
  string msg;
  string cmd;

  while (readMsg()) {
    CC->reset();
    strMessage = firstChar;

    // Receive the sense message
    strcpy(strMessage, getMsg());
    logMsg.open("Msg.txt", ios::app);
    logMsg << strMessage << endl << endl;
    logMsg.close();

    // Extract the information from the s-expression sense messages
    MessageParser parser;
    parser.parseMessage(std::string(strMessage));

    // Execute the decision making system and walking behavior
    behaveWalking();

    // send effector messages to the simulator
    sendMsg(CC->getPreparedCommand());
    WM->resetForUpdate();
  }

  delete firstChar;
}

///=====================================
/// \define The main of the test agent binary
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
