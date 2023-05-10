#ifndef CALC_SCANNER_H
#define CALC_SCANNER_H

#include <cstdint>
#include <string>
#include <map>
#include "calcTokens.h"

class CalcScanner {
	std::map<char, CalcTokens::Symbols> symbolMap = {
		{'+', CalcTokens::Symbols::PLUS},
		{'-', CalcTokens::Symbols::MINUS},
		{'*', CalcTokens::Symbols::ASTERISK},
		{'/', CalcTokens::Symbols::SOLIDUS},
		{'(', CalcTokens::Symbols::L_PARAM},
		{')', CalcTokens::Symbols::R_PARAM}
	};
	std::string currentString;
	std::size_t position = 0;
	//std::size_t savedPosition = 0;
	std::size_t size = 0;

	void _reset();
	char getChar();
	uint8_t getDigit();
public:
	CalcScanner(): CalcScanner(""){}
	CalcScanner(const std::string& str): currentString(str){_reset();}

	bool nextIsNumber();
	bool nextIsSymbol();
	bool isFinished(){return position >= size;}

	void advance(){position++;}
	void reset(std::string);

	std::size_t getPosition(){return position;}


	double scanNumber();
	CalcTokens::Symbols scanSymbol();
};


#endif