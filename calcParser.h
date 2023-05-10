#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include <list>
#include <stack>
#include "calcScanner.h"

class CalcParser {
	CalcScanner scanner;
	std::stack<double> number_stack;

	std::map<const CalcTokens::Symbols, int> p = {
		{CalcTokens::Symbols::PLUS, 1},
		{CalcTokens::Symbols::MINUS, 1},
		{CalcTokens::Symbols::ASTERISK, 2},
		{CalcTokens::Symbols::SOLIDUS, 2},
		{CalcTokens::Symbols::L_PARAM, 255},
		{CalcTokens::Symbols::R_PARAM, 255}
	};


	void reset(){number_stack=std::stack<double>();scanner.reset("");}
	bool computerStatement(const CalcTokens::Symbols&);

	int getP(const CalcTokens::Symbols);
public:
	CalcParser(){}

	std::list<CalcTokens> deInfix(const std::list<CalcTokens>&);
	double compute(const std::list<CalcTokens>&);

	double computeString(const std::string&);
};

#endif