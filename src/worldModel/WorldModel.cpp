#include "WorldModel.h"
#include "../geometry/Geometry.h"
//======================================
WorldModel* WorldModel::uniqueInstance;
//======================================
WorldModel* WorldModel::getUniqueInstance(){
  if (uniqueInstance == NULL)
    uniqueInstance = new WorldModel();

  return uniqueInstance;
}
//======================================
WorldModel::WorldModel(){
  logWorlModel.open("WMLog.txt");
  logWorlModel.close();

  reciveMsg = new char [1024];
  fallen = false;
}
//======================================
WorldModel::~WorldModel(){
  delete reciveMsg;
}
//======================================
void WorldModel::setTime(float ft){
  time = ft;
}
//======================================
float WorldModel::getTime(){
  return time;
}
//======================================
void WorldModel::setGSTime(float ft){
  gameStateTime = ft;
}
//======================================
float WorldModel::getGSTime(){
  return gameStateTime;
}
///=====================================
void WorldModel::setAHingeJoint(HingeJoint hj , int index){
  hingeJointsArray[index] = hj;
}
///=====================================
HingeJoint WorldModel::getAHingeJoint(int index){
  return *(hingeJointsArray + index);
}
///=====================================
void WorldModel::setBall(Ball b){
  ball = b;
}
///=====================================
Ball WorldModel::getBall(){
  return ball;
}
///=====================================
void WorldModel::setGyro(Gyro g){
  gyro = g;
}
///=====================================
Gyro WorldModel::getGyro(){
  return gyro;
}
///=====================================
void WorldModel::printJoints(){

  logWorlModel.open("WMLog.txt" , ios::app);

  logWorlModel << "Time :" << this->getTime();
  logWorlModel << " ->\n\t";

  // log the Ball
  logWorlModel	<< "\n\n\tBall :" << ball.getPolarPos().getRo()<< " "
      << ball.getPolarPos().getYaw() << " " << ball.getPolarPos().getPhi() << endl;
  logWorlModel	<< "Direction of head from flag :" << getDOF(DOF_HEAD_PAN) << endl;

  logWorlModel << "\nJoints degree :\n\t" ;

  // log the Joint
  for(int i = 0; i < 22; i++)
  {
    logWorlModel << hingeJointsArray[i].getName() << " "<< hingeJointsArray[i].getAxis() << ",";
  }


  logWorlModel << endl << endl;
  logWorlModel.close();
}
///=====================================
PlayMode WorldModel::getPlayMode(){
  return pm;
}
///=====================================
void WorldModel::setPlayMode(string playMode){

  if ( playMode == "BeforeKickOff")
    pm = PM_BEFORE_KICK_OFF;
  else if (playMode == "PlayOn")
      pm = PM_PLAY_ON;
  else if (playMode == "KickOff_Left")
      pm = PM_KICKOFF_LEFT;
  else if (playMode == "KickOff_Right")
      pm = PM_KICKOFF_RIGHT;
  else if (playMode == "KickIn_Left")
      pm = PM_KICKIN_LEFT;
  else if (playMode == "KickIn_Right")
      pm = PM_KICKIN_RIGHT;
  else if (playMode == "FREE_KICK_LEFT")
      pm = PM_FREE_KICK_LEFT;
  else if (playMode == "FREE_KICK_RIGHT")
      pm = PM_FREE_KICK_RIGHT;
  else if (playMode == "Goal_Left")
      pm = PM_GOAL_LEFT;
  else if (playMode == "Goal_Right")
      pm = PM_GOAL_RIGHT;
  else if (playMode == "CORNER_KICK_LEFT")
      pm = PM_CORNER_KICK_LEFT;
  else if (playMode == "CORNER_KICK_RIGHT")
      pm =  PM_CORNER_KICK_RIGHT;
  else if (playMode == "GameOver")
      pm = PM_GAME_OVER;
  else
      pm = PM_UNKNOWN;
}
///=====================================
Point WorldModel::getFRPCenterL(){
  return FRP[0];
}
///=====================================
Point WorldModel::getFRPForceL(){
  return FRP[1];
}
///=====================================
Point WorldModel::getFRPCenterR(){
  return FRP[2];
}
///=====================================
Point WorldModel::getFRPForceR(){
  return FRP[3];
}
///=====================================
void WorldModel::setFRPCenterL(Point center){
  FRP[0] = center;
}
///=====================================
void WorldModel::setFRPForceL(Point force){
  FRP[1] = force;
}
///=====================================
void WorldModel::setFRPCenterR(Point center){
  FRP[2] = center;
}
///=====================================
void WorldModel::setFRPForceR(Point force){
  FRP[3] = force;
}
///=====================================
void WorldModel::printFRPs(){
  cout<< "Left Center: "<< getFRPCenterL()<< endl;
  cout<< "Left Force: "<< getFRPForceL()<< endl;
  cout<< "Right Center: "<< getFRPCenterR()<< endl;
  cout<< "Right Force: "<< getFRPForceR()<< endl;
}
///=====================================
int WorldModel::getMyNum(){
  return myNum;
}
///=====================================
void WorldModel::setMyNum(int unum){
  myNum = unum;
}
//======================================
Side WorldModel::getOurSide(){
  return ourSide;
}
//======================================
void WorldModel::setOurSide(Side side){
  ourSide = side;
}
///=====================================
string WorldModel::getTeamName(){
  return teamName;
}
///=====================================
void WorldModel::setTeamName(string str){
  teamName = str;
}
///=====================================
void WorldModel::resetForUpdate(){
  Point zero( Point(0.0, 0.0, 0.0) );
  setFRPCenterL(zero);
  setFRPForceL(zero);
  setFRPCenterR(zero);
  setFRPForceR(zero);
  setLastTime();
  setLastPosOfBall();
  setLastGlobalPosOfBall();
  setLastVelOfBall();
}
///=====================================
double  WorldModel::getLastTime() {
  return lastTime;
}
///=====================================
Point WorldModel::getLastPosOfBall() {
  return lastPosOfBall;
}
///=====================================
void WorldModel::setLastTime () {

  lastTime = getTime();
}
///====================================
void WorldModel::setLastPosOfBall() {

  lastPosOfBall = getBall().getPolarPos();
}
///====================================
bool WorldModel::isPlayOn(){
  if(pm == PM_PLAY_ON)
    return true;

  return false;
}
///====================================
bool WorldModel::isGameOver(){
  if (pm == PM_GAME_OVER)
    return true;

  return false;
}
///====================================
bool WorldModel::isBeforeKickOff(){
  if(pm == PM_BEFORE_KICK_OFF)
    return true;

  return false;
}
///====================================
bool WorldModel::isKickOffUs(){
  if( (pm == PM_KICKOFF_LEFT) && (ourSide == SIDE_LEFT) )
    return true;

  if( (pm == PM_KICKOFF_RIGHT) && (ourSide == SIDE_RIGHT) )
    return true;


  return false;
}
///====================================
bool WorldModel::isKickOffThem(){

  if( (pm == PM_KICKOFF_LEFT) && (ourSide == SIDE_RIGHT) )
    return true;

  if( (pm == PM_KICKOFF_RIGHT) && (ourSide == SIDE_LEFT) )
    return true;

  return false;
}
///====================================
bool WorldModel::isKickInUs(){
  if( (pm == PM_KICKIN_LEFT) && (ourSide == SIDE_LEFT) )
    return true;

  if( (pm == PM_KICKIN_RIGHT) && (ourSide == SIDE_RIGHT) )
    return true;

  return false;
}
///====================================
bool WorldModel::isKickInThem(){
  if( (pm == PM_KICKIN_LEFT) && (ourSide == SIDE_RIGHT) )
    return true;

  if( (pm == PM_KICKIN_RIGHT) && (ourSide == SIDE_LEFT) )
    return true;

  return false;

}
///====================================
bool WorldModel::isCornerUs(){
  if( (pm == PM_CORNER_KICK_LEFT) && (ourSide == SIDE_LEFT) )
    return true;

  if( (pm == PM_CORNER_KICK_RIGHT) && (ourSide == SIDE_RIGHT) )
    return true;

  return false;
}
///====================================
bool WorldModel::isCornerThem(){
  if( (pm == PM_CORNER_KICK_LEFT) && (ourSide == SIDE_RIGHT) )
    return true;

  if( (pm == PM_CORNER_KICK_RIGHT) && (ourSide == SIDE_LEFT) )
    return true;

  return false;

}
///====================================
bool WorldModel::isGoalKickUS(){
  if( (pm == PM_GOAL_KICK_LEFT) && (ourSide == SIDE_LEFT) )
    return true;

  if( (pm == PM_GOAL_KICK_RIGHT) && (ourSide == SIDE_RIGHT) )
    return true;

  return false;
}
///====================================
bool WorldModel::isGoalKickThem(){
  if( (pm == PM_GOAL_KICK_LEFT) && (ourSide == SIDE_RIGHT) )
    return true;

  if( (pm == PM_GOAL_KICK_RIGHT) && (ourSide == SIDE_LEFT) )
    return true;

  return false;

}
///====================================
bool WorldModel::isGoalUs(){
  if( (pm == PM_GOAL_LEFT) && (ourSide == SIDE_LEFT) )
    return true;

  if( (pm == PM_GOAL_RIGHT) && (ourSide == SIDE_RIGHT) )
    return true;

  return false;
}
///====================================
bool WorldModel::isGoalThem(){
  if( (pm == PM_GOAL_LEFT) && (ourSide == SIDE_RIGHT) )
    return true;

  if( (pm == PM_GOAL_RIGHT) && (ourSide == SIDE_LEFT) )
    return true;

  return false;

}
///====================================
void WorldModel::setLastGlobalPosOfBall(){
  lastGlobalPosOfBall = getGlobalPosOfBall();
}
///====================================
Point WorldModel::getLastGlobalPosOfBall(){
  return lastGlobalPosOfBall;
}
///====================================
void WorldModel::setGlobalPosOfBall(Point ballPos){
  glbPosOfBall = ballPos;
}
///=====================================
Point WorldModel::getGlobalPosOfBall(){
  return glbPosOfBall;
}
///====================================
Point WorldModel::getVelOfBall(){
  return velOfBall;
}
///====================================
void WorldModel::setVelOfBall(){
  if (getDeltaTime()!= 0)
    velOfBall = ( ( getGlobalPosOfBall() - getLastGlobalPosOfBall() ) / getDeltaTime() );
  else
    return;
}
///====================================
void WorldModel::setAccerationOfBall(){
  if (getDeltaTime() != 0)
    accOfBall= ((getVelOfBall() - getLastVelOfBall()) / getDeltaTime());
  else
    return;
}
///====================================
Point WorldModel::getAccerationOfBall() {
  return accOfBall;
}
///====================================
void WorldModel::setDeltaTime(){
  deltaTime = getTime() - getLastTime();
}
///====================================
double WorldModel::getDeltaTime () {
  return deltaTime;
}
///====================================
void WorldModel::setLastVelOfBall(){
  lastVelOfBall = getVelOfBall();
}
///====================================
Point WorldModel::getLastVelOfBall(){
  return lastVelOfBall;
}

///====================================
double WorldModel::getDOF( DOFID id ){
  /*
	0. (HJ (n hj1) (ax -0.00))
	1. (HJ (n hj2) (ax -0.00))
	2. (HJ (n raj1) (ax -0.00))
	3. (HJ (n raj2) (ax -0.00))
	4. (HJ (n raj3) (ax -0.00))
	5. (HJ (n raj4) (ax -0.00))
	6. (HJ (n laj1) (ax -0.00))
	7. (HJ (n laj2) (ax -0.00))
	8. (HJ (n laj3) (ax -0.00))
	9. (HJ (n laj4) (ax -0.00))
	10. (HJ (n rlj1) (ax -0.00))
	11. (HJ (n rlj2) (ax -0.00))
	12. (HJ (n rlj3) (ax -0.00))
	13. (HJ (n rlj4) (ax -0.00))
	14. (HJ (n rlj5) (ax -0.00))
	15. (HJ (n rlj6) (ax -0.00))
	16. (HJ (n llj1) (ax -0.00))
	17. (HJ (n llj2) (ax -0.00))
	18. (HJ (n llj3) (ax -0.00))
	19. (HJ (n llj4) (ax -0.00))
	20. (HJ (n llj5) (ax -0.00))
	21. (HJ (n llj6) (ax -0.00))
   */
  if( (id == DOF_SHOULDER_LX) || (id == DOF_SHOULDER_RX) )
    return Geometry::normalizeAngle(getAHingeJoint(id).getAxis() + 90.0);

  return getAHingeJoint(id).getAxis();
}
///====================================
void WorldModel::setMessageSay(char* ch){
  reciveMsg = ch;
}
///====================================
char* WorldModel::getMessageSay(){
  return reciveMsg;
}
///====================================
Side WorldModel::getOppSide(){

  if ( getOurSide() == SIDE_LEFT )
    return SIDE_RIGHT;
  else
    return SIDE_LEFT;
}
