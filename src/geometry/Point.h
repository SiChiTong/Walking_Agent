#include "../etc/CommonHeaders.h"
#include "Geometry.h"

#ifndef POINT_H
#define POINT_H

class Point{

  public:
    double     x_Ro;
    double     y_Phi;
    double     z_Teta;
			    	   Point (){}
		    	     Point ( double x , double y , double z=0 );

		void       setX             ( double  );
		void       setY             ( double  );
		void       setZ             ( double  );
		void       setRo            ( double  );
		void       setPhi	    ( double  );
		void   	   setTeta	    ( double  );

		double     getX             (         );
		double     getY             (         );
		double     getZ        	    (         );
		double     getRo	    (  	      );
		double     getPhi	    (	      );
		double     getTeta	    (	      );
		float      getDirection (       );

		double     getDistanceTo    ( Point   );
		double     getDistanceTo2   ( Point   );
		double     getMagnitude     (         );
		Point      rotate( float angle );


		Point      operator +=      ( Point   );
		Point      operator -=      ( Point   );
		Point      operator +       ( Point   );
		Point      operator -       ( Point   );
		Point      operator /       ( double  );
		Point      operator /=      ( double  );
		Point      operator *       ( double  );
		Point      operator *=      ( double  );
		bool       operator ==      ( Point   );
		bool       operator !=      ( Point   );
		Point      getNorm	    ();
		void       printOnScreen();
		friend ostream &operator <<(ostream&,const Point &);

};

///=====================================
#endif
///=====================================
