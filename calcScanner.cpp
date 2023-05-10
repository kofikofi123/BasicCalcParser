#include "calcScanner.h"


void CalcScanner::_reset(){
	position = 0;
	size = currentString.size();
}

void CalcScanner::reset(std::string otherString){
	currentString = otherString;
	_reset();
}

inline char CalcScanner::getChar(){
	return currentString.at(position);
}

inline uint8_t CalcScanner::getDigit(){
	return getChar() - 0x30;
}

bool CalcScanner::nextIsNumber(){
	char c = getChar();
	return ((c > 0x2F) && (c < 0x3A)) || (c == '.');
}

bool CalcScanner::nextIsSymbol(){
	return symbolMap.count(getChar()) == 1;
}


double CalcScanner::scanNumber(){
	std::size_t savedPosition = position;

	uint8_t decimalCount = 0;
	while (!isFinished() && nextIsNumber() && decimalCount < 2){
		if (getChar() == '.'){
			decimalCount++;
		}
		position++;
	}


	if (decimalCount == 2){
		position--;
	}


	return std::atof(currentString.substr(savedPosition, (position - savedPosition)).c_str());
}

CalcTokens::Symbols CalcScanner::scanSymbol(){
	auto symbol = symbolMap.find(getChar());
	advance();
	return symbol->second;
}