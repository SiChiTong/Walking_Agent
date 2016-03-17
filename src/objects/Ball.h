#ifndef BALL_H
#define BALL_H
//======================================
#include "../geometry/Point.h"
//======================================

class Ball
{
private:

	Point	polarPos;

public:
			Ball						( );
	void 	setPolarPos						( Point );
	Point 	getPolarPos						( void );
};

//======================================
#endif
///=====================================


