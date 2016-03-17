#include "CommandCreator.h"
///===================================
CommandCreator *CommandCreator::uniqueInstance;
///===================================
#define EACH_COMMAND_SIZE   25
#define COMMAND_STRING_SIZE 2048

///===================================
CommandCreator::CommandCreator(){
	commandString = new char [COMMAND_STRING_SIZE];
	command = new char [EACH_COMMAND_SIZE];
	strcpy (commandString,"");
	WM = WorldModel::getUniqueInstance();
}
///===================================
CommandCreator::~CommandCreator (){
	delete commandString;
	delete command;
}
///===================================
CommandCreator* CommandCreator::getUniqueInstance(){
	if (uniqueInstance == NULL)
		uniqueInstance = new CommandCreator();
	return uniqueInstance;
}
///==================  Nao Commands =================

//commands for moving head
///===================================
void CommandCreator::moveHeadAx1(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(he1 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveHeadAx2(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(he2 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================

//commands for Hands
void CommandCreator::moveLShoulderAx1 (float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lae1 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRShoulderAx1 (float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rae1 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLShoulderAx2 (float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lae2 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRShoulderAx2 (float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rae2 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::rotateLShoulder(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lae3 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::rotateRShoulder(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rae3 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLElbow(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lae4 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRElbow (float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rae4 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================

//commands for legs
///===================================
void CommandCreator::rotateLLeg(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle1 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::rotateRLeg(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle1 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLLegAx1(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle2 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRLegAx1(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle2 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLLegAx2(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle3 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRLegAx2(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle3 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLKnee(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle4 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRKnee(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle4 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLAnkleAx1(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle5 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveRAnkleAx1(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle5 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}
///===================================
void CommandCreator::moveLAnkleAx2(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(lle6 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}

///===================================

void CommandCreator::moveRAnkleAx2(float angle)
{
	sprintf (command,"%f",angle);
	strcat  (commandString,"(rle6 ");
	strcat  (commandString,command);
	strcat  (commandString,")");
}


///===================================
void CommandCreator::moveHingJoint(int index,float angle){
    if      (index == 0)
   		moveHeadAx1(angle);
   	else if (index == 1)
   		moveHeadAx2(angle);
    else if (index == 2)
   		moveRShoulderAx1(angle);
    else if (index == 3)
   		moveRShoulderAx2(angle);
    else if (index == 4)
   		rotateRShoulder(angle);
    else if (index == 5)
   		moveRElbow(angle);
    else if (index == 6)
   		moveLShoulderAx1(angle);
    else if (index == 7)
   		moveLShoulderAx2(angle);
    else if (index == 8)
   		rotateLShoulder(angle);
    else if (index == 9)
   		moveLElbow(angle);
    else if (index == 10)
   		rotateRLeg(angle);
    else if (index == 11)
   		moveRLegAx1(angle);
    else if (index == 12)
   		moveRLegAx2(angle);
    else if (index == 13)
   		moveRKnee(angle);
    else if (index == 14)
   		moveRAnkleAx1(angle);
    else if (index == 15)
   		moveRAnkleAx2(angle);
    else if (index == 16)
   		rotateLLeg(angle);
    else if (index == 17)
   		moveLLegAx1(angle);
    else if (index == 18)
   		moveLLegAx2(angle);
    else if (index == 19)
   		moveLKnee(angle);
    else if (index == 20)
   		moveLAnkleAx1(angle);
    else if (index == 21)
   		moveLAnkleAx2(angle);
    else
   		cerr <<"!!!this index is not available in hingjoint number!!!\n you should select number between (0 -> 7)"<<endl;
}

///===================================
void CommandCreator::stopAllJoints(){
	strcpy (commandString,"(he1 0.0)(he2 0.0)(rae1 0.0)(rae2 0.0)(rae3 0.0)(rae4 0.0)(lae1 0.0)(lae2 0.0)(lae3 0.0)(lae4 0.0)(rle1 0.0)(rle2 0.0)(rle3 0.0)(rle4 0.0)(rle5 0.0)(rle6 0.0)(lle1 0.0)(lle2 0.0)(lle3 0.0)(lle4 0.0)(lle5 0.0)(lle6 0.0)");
}
///===================================
char* CommandCreator::getPreparedCommand(){
	return commandString;
}
///===================================
void  CommandCreator::reset(){
    	memset (commandString, 0, COMMAND_STRING_SIZE);
}
///===================================
void CommandCreator::beam(float x,float y,float z){
	sprintf (commandString,"(beam %f %f %f)",x, y, z);
}
///===================================
void CommandCreator::beam(Point point){
    sprintf (commandString,"(beam %f %f %f)",point.getX(), point.getY(), point.getZ());
}
///===================================
void CommandCreator::init (int i,char* ch){
	sprintf (commandString, "(init (unum %d)(teamname %s))", i, ch);
}
///===================================
void CommandCreator::pushCmd(const char *cmd){
    strcat(commandString, cmd);
}
///===================================
