#include "GameConf.h"

///=====================================
GameConf *GameConf::uniqueInstance = NULL;
string	GameConf::rsgPath = "(scene /usr/local/share/rcssserver3d/rsg/agent/nao.rsg)";

///=====================================
GameConf::GameConf(){
  WM = WorldModel::getUniqueInstance();
}
///=====================================
void GameConf::init(){
  setRSGPath(rsgPath);
}
///=====================================
GameConf::~GameConf(){
  delete WM;
}
///=====================================
GameConf *GameConf::getUniqueInstance(){
  if( !uniqueInstance )
    uniqueInstance = new GameConf;
  return uniqueInstance;
}
///=====================================
string GameConf::getRSGPath(){
  return rsgPath;
}
///=====================================
void GameConf::setRSGPath(string filePath){
  rsgPath = filePath;
}
