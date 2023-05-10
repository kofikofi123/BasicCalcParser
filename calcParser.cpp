#include <cmath>
#include <iostream>
#include <algorithm>
#include "calcScanner.h"
#include "calcParser.h"

#define print_out(list) std::for_each(list.begin(), list.end(), [](auto& n){std::cout<<n<<std::endl;})

bool CalcParser::computerStatement(const CalcTokens::Symbols& symbols){
	

	double result = 0.0;

	if (number_stack.size() < 2){
		return false;
	}
	double b = number_stack.top();
	number_stack.pop();
	double a = number_stack.top();
	number_stack.pop();

	switch (symbols){
		case CalcTokens::Symbols::PLUS:
			result = a + b;
			break;
		case CalcTokens::Symbols::MINUS:
			result = a - b;
			break;
		case CalcTokens::Symbols::ASTERISK:
			result = a * b;
			break;
		case CalcTokens::Symbols::SOLIDUS: 
		{
			if (b == 0.0){
				result = std::nan("0");
			}else{
				result = a / b;
			}
			break;
		}
	}

	number_stack.push(result);

	return true;
}

int CalcParser::getP(const CalcTokens::Symbols s){
	int pr = -1;

	auto pair = p.find(s);

	if (pair != p.end()){
		pr = pair->second;
	}

	return pr;
}

std::list<CalcTokens> CalcParser::deInfix(const std::list<CalcTokens>& tokens){
	std::list<CalcTokens> newTokens;
	std::stack<CalcTokens> operatorStack;
	
	auto begin = tokens.begin();
	auto current = begin;
	auto end = tokens.end();

	while (current != end){
		auto token = *current;
		auto type = token.getType();

		if (type == CalcTokens::Type::NUMBER){
			newTokens.push_back(token);
		}else if (type == CalcTokens::Type::SYMBOL){
			auto opr = token.getSymbol();
			
			auto top = opr; //temp;

			if (opr == CalcTokens::Symbols::R_PARAM){
				while (operatorStack.size() > 0 &&
					   (top = operatorStack.top().getSymbol()) != CalcTokens::Symbols::L_PARAM){
					newTokens.push_back(top);
					operatorStack.pop();
				}
				operatorStack.pop();
			}else{
				while (operatorStack.size() > 0 &&
					   getP((top = operatorStack.top().getSymbol())) >= getP(opr) &&
					   top != CalcTokens::Symbols::L_PARAM){
					
					newTokens.push_back(top);
					operatorStack.pop();
				}
				operatorStack.push(opr);
			}
		}
		current++;
	}

	while (operatorStack.size() > 0){
		newTokens.push_back(operatorStack.top());
		operatorStack.pop();
	}

	return newTokens;
}

double CalcParser::compute(const std::list<CalcTokens>& tokens){
	for (auto token : tokens){
		auto type = token.getType();
		if (type == CalcTokens::Type::NUMBER){
			number_stack.push(token.getNumber());
		}else if (type == CalcTokens::Type::SYMBOL){
			if (!computerStatement(token.getSymbol())){
				return std::nan("0");
			}
		}
	}
	double number = std::nan("0");
	if (number_stack.size() == 1){
		number = number_stack.top();
		number_stack.pop();
	}
	return number;
}

double CalcParser::computeString(const std::string& string){
	scanner.reset(string);
	std::list<CalcTokens> tokens;

	while (!scanner.isFinished()){
		if (scanner.nextIsNumber()){
			tokens.push_back(scanner.scanNumber());
		}else if (scanner.nextIsSymbol()){
			tokens.push_back(scanner.scanSymbol());
		}else{
			scanner.advance();
		}
	}

	{
		auto begin = tokens.begin();
		auto current = begin;
		auto end = tokens.end();

		while (current != end){
			auto token = *current;
			if (token.getType() == CalcTokens::Type::SYMBOL && 
				token.getSymbol() == CalcTokens::Symbols::MINUS){
				auto next = std::next(current);
				auto prev = std::prev(current);
				auto next_numb = *current;

				if ((prev == end || 
					(*prev).getType() == CalcTokens::Type::SYMBOL) &&
					(next != end) && 
					((*next).getType() == CalcTokens::Type::NUMBER)){
					auto _new = tokens.insert(current, -((*next).getNumber()));
					tokens.erase(current);
					tokens.erase(next);
					current = _new;
				}
			}
			current++;
		}
	}

	return compute(deInfix(tokens));
}