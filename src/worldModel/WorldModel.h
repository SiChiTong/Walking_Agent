#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../objects/HingeJoint.h"
#include "../objects/Ball.h"
#include "../objects/Gyro.h"
#include "../etc/CommonHeaders.h"
#include "../etc/types.h"
#include <vector>
using namespace std;

class WorldModel
{
private:
	ofstream		logWorlModel;
	static			WorldModel* 	uniqueInstance;
	float			time;
	float			gameStateTime;
	bool			fallen;
	HingeJoint		hingeJointsArray[MAX_HING];
	Ball			ball;
	Gyro			gyro;
	Point			FRP[4];
	Point			myCartPos;
	Point			dir;
	PlayMode		pm;
	int				myNum;
	Side			ourSide;
	string		teamName;
	Point			lastPosOfBall;
	Point			lastGlobalPosOfBall;
	Point			glbPosOfBall;
	Point			lastVelOfBall;
	Point			velOfBall;
	Point			accOfBall;
	double		lastTime;
	double		deltaTime;
	char*			reciveMsg;
	int				numOfZero;

public:
					WorldModel						( );
					~WorldModel						( );
	static		WorldModel*	getUniqueInstance	( );
	void			setTime							( float );
	float			getTime							( );
	float			getGSTime						( );
	void			setGSTime						( float );
	void			setAHingeJoint					( HingeJoint , int );
	HingeJoint		getAHingeJoint					( int );
	double			getDOF							( DOFID	id );
	void			setBall							( Ball );
	Ball			getBall							( );
	void			setGyro							( Gyro );
	Gyro			getGyro							( );
	void			printJoints						( );
	void			printFRPs						( );
	PlayMode	getPlayMode						( );
	void			setPlayMode						( string playMode );
	Point			getFRPCenterL					( );
	Point			getFRPForceL					( );
	Point			getFRPCenterR					( );
	Point			getFRPForceR					( );
	void			setFRPCenterL					( Point center );
	void			setFRPForceL					( Point force );
	void			setFRPCenterR					( Point center );
	void			setFRPForceR					( Point force );
	int				getMyNum						( );
	void			setMyNum						( int unum );
	Side			getOurSide						( );
	Side			getOppSide						( );
	void			setOurSide						( Side side );
	string		getTeamName						( );
	void			setTeamName						( string str );
	void			resetForUpdate					( );
	void			setLastTime						( );
	void			setLastPosOfBall				( );
	void			setLastGlobalPosOfBall			( );
	Point			getLastGlobalPosOfBall			( );
	void			setLastGlobalPosOfAgent			( );
	Point			getLastGlobalPosOfAgent			( );
	double		getLastTime						( );
	Point			getLastPosOfBall				( );
	bool			isPlayOn						( );
	bool			isGameOver						( );
	bool			isBeforeKickOff					( );
	bool			isKickOffUs						( );
	bool			isKickOffThem					( );
	bool			isKickInUs						( );
	bool			isKickInThem					( );
	bool			isCornerUs						( );
	bool			isCornerThem					( );
	bool			isGoalKickUS					( );
	bool			isGoalKickThem					( );
	bool			isGoalUs						( );
	bool			isGoalThem						( );
	void			setGlobalPosOfBall				( Point );
	Point			getGlobalPosOfBall				( );
	void			setVelOfBall					( );
	Point			getVelOfBall					( );
	Point			getAccerationOfBall				( );
	void			setLastVelOfBall				( );
	Point			getLastVelOfBall				( );
	double		getDeltaTime					( );
	void			setAccerationOfBall				( );
	void			setDeltaTime					( );
	void			setMessageSay					(char* );
	char*			getMessageSay					( );
};
#endif


