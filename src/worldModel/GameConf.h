#ifndef GAMECONF_H
#define GAMECONF_H
///=====================================
#include "WorldModel.h"
#include "../geometry/Point.h"
#include "../geometry/Geometry.h"
#include "../objects/Ball.h"
///=====================================

class GameConf{

private:

  static	GameConf    *uniqueInstance;

  GameConf  ();
  ~GameConf ();

  WorldModel *WM;
  static 	string rsgPath;

public:
  static GameConf* getUniqueInstance (		     );
  void  	 init		   (		     );
  static 	string 	 getRSGPath	   (		     );
  static 	void 	 setRSGPath	   ( string filePath );

};
///=====================================
#endif
///=====================================
