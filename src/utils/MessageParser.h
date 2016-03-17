#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <string>
#include <cstring>
#include "../sexpLibrary/sexp.h"
#include "../sexpLibrary/sexp_ops.h"
#include "../geometry/Point.h"
#include "../worldModel/WorldModel.h"

class MessageParser
{
	public:
		MessageParser();
		~MessageParser();
		void parseMessage(const std::string& msg);

	private:	
	  WorldModel  *WM;
		void parseSexp(sexp_t* exp);
		Point* parsePoint(sexp_t* ptr);
		Point* parsePolarCoords(sexp_t* exp_p);
		void parseTime(sexp_t* exp);
		void parseGameState(sexp_t* exp);
		void parseGyro(sexp_t* exp);
		void parseFRP(sexp_t* exp);
		void parseHingeJoint(sexp_t *exp);
		void parseVision(sexp_t *exp);
		void parseBall(sexp_t* exp);
		void parseFlag(sexp_t* exp);
		void parseGoal(sexp_t* exp);
};

#endif // MESSAGEPARSER_H
