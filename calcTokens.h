#ifndef CALCTOKENS_H
#define CALCTOKENS_H

#include <variant>
#include <ostream>

class CalcTokens {
public://asterisk
	enum class Type {
		NONE = 0,
		NUMBER,
		SYMBOL
	};
	enum class Symbols {
		PLUS = 0,
		MINUS,
		ASTERISK,
		SOLIDUS,
		L_PARAM,
		R_PARAM
	};

	CalcTokens(double _number): type(Type::NUMBER), number(_number){}
	CalcTokens(Symbols _symbol): type(Type::SYMBOL), symbol(_symbol){}


	Type getType() const;
	double getNumber() const;
	Symbols getSymbol() const;


	friend std::ostream& operator<<(std::ostream&, const CalcTokens&);
private:
	const Type type;
	std::variant<double, Symbols> number, symbol;
};


#endif