#include "calcTokens.h"


CalcTokens::Type CalcTokens::getType() const {
	return this->type;
}


double CalcTokens::getNumber() const {
	return std::get<double>(this->number);
}

CalcTokens::Symbols CalcTokens::getSymbol() const {
	return std::get<CalcTokens::Symbols>(this->symbol);
}


std::ostream& operator<<(std::ostream& stream, const CalcTokens::Type& type){
	switch (type){
		case CalcTokens::Type::NUMBER:
			stream << "[NUMBER]";
			break;
		case CalcTokens::Type::SYMBOL:
			stream << "[SYMBOL]";
			break;
		default:
			stream << "[????]";
			break;
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const CalcTokens::Symbols symbol){
	switch (symbol){
		case CalcTokens::Symbols::PLUS:
			stream << "+";
			break;
		case CalcTokens::Symbols::MINUS:
			stream << "-";
			break;
		case CalcTokens::Symbols::ASTERISK:
			stream << "*";
			break;
		case CalcTokens::Symbols::SOLIDUS:
			stream << "/";
			break;
		case CalcTokens::Symbols::L_PARAM:
			stream << "(";
			break;
		case CalcTokens::Symbols::R_PARAM:
			stream << ")";
			break;
		default:
			stream << "?";
			break;
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const CalcTokens& token){
	CalcTokens::Type type = token.getType();

	stream << "{\n\t" << "Type: ";
	stream << type;
	stream << "\n\tValue: ";

	switch (type){
		case CalcTokens::Type::NUMBER:
			stream << token.getNumber();
			break;
		case CalcTokens::Type::SYMBOL:
			stream << token.getSymbol();
			break;
		default:
			stream << "[UNKNOWN DATA]";
			break;
	}

	stream << "\n}";

	return stream;
}