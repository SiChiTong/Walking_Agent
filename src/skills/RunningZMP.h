#ifndef RUNNINGZMP_H_
#define RUNNINGZMP_H_

#include <time.h>
#include "../geometry/Point.h"
#include "../geometry/Geometry.h"
#include "../geometry/Bezier.h"
#include "../utils/CommandCreator.h"
#include "../worldModel/WorldModel.h"
#include "InverseKinematics.h"

#define 	RIGHTFOOT 	0
#define 	LEFTFOOT 	1

struct Foot2{
	Point Position;
	bool support;
	bool Right;
	double time;
	double theta;
};

struct ZMP2{
	Point Position;
	double time;
};

struct CoM2{
	Point PositionX;
	Point PositionY;
	double time;
};

struct HeightTrajectory{
	double z;
	double ddz;
};

class RunningZMP{
	double dp;
	double dpY;

	std::vector<HeightTrajectory> comZTrajecotry;


	int oneStepSize;
	double legSeperation;
	Foot2 planedLeftFoot[25];
	Foot2 planedRightFoot[25];
	CoM2* planedCoM;
	bool activeBalace;
	int maxPrevIter;

	double cl;
	double initTime;
	double deltaT;
	Foot2 inicialLeftLeg;
	Foot2 inicialRightLeg;

	float pose[22];
	float	lastAngle[22];
	float	lastError[22];

	CommandCreator *CC;
  WorldModel *WM;
	Bezier bzqdRotateSwing;
	Bezier bzqdRotateSupport;
	Bezier bzqdSwing;
	InverseKinematics ik;

public:
	// walk Paramateres..
  bool initPos;
	bool initWalk;
	double swingHeight;
	double stepSizeX;
	double stepSizeY;
	double stepTime;
	double legExtention;
	double thetaStep;
	//--------------- optimizing Parameters
	double constantInclination;
	double kpXActiveBalance;
	double kpYActiveBalance;
	double increasingDX;
	//--------------- last Walk Parameters
	double lastStepTime;
	double lastDX;
	double lastDY;
	double lastTheta;

	//---------------- height Parameters------------
	double offset;
	double amplitude;
	double amplitude2;
	//----------------share the walk state
	CoM2 initCom;
	Point transitionError;
	CoM2 transitionCom;
	Foot2 transitionLeftFoot;
	Foot2 transitionRightFoot;

	Foot2 previousLeftFoot;
	Foot2 previousRightFoot;
	bool isStepFinished;
	bool stop;

	RunningZMP();

	void thomasAlgorithm(double com0,double com1,double com0y,double com1y, int legth);
	CoM2* fastDynamicSolverWithSlideWindow(Point zmpInit,ZMP2* zmpTrajector,int length,
	          double dt,std::vector<HeightTrajectory> comZ);
	void createHeightTrajectory(double size);
	void setWalkParameter(double period, double dX,double dY,double theta, 	bool presure=true);

	Point getCoM(double time);

	Foot2 setFoot(Point Position, bool isSupport,bool isRight, double time,double theta);
	void footGenerator2(double stepX,double stepY, double stepTheta,int stepNumber,
			double timeStep,Foot2 inicialLeftLeg,Foot2 inicialRightLeg);
	vector<float> legInvKin(const int foot, const Point targetPos, const Point targetOri);
	void computePose(const Point lFootPos, const Point rFootPos, Point orientationRithFoot, Point orientationLeftFoot);
	void updatePose();
	void initialPos();
	double predictEffector(int joint, double current, double setpoint);
	void	execute();
	bool    finished();
	void	init();
	ZMP2* zmpGenerator2(int stepNumber, double dt, double doubleSupportPercent, int &size);
	virtual ~RunningZMP();

};

#endif /* RUNNING_H_ */
