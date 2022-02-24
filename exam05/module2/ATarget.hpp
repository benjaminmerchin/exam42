#pragma once

#include <iostream>

class ASpell;

class ATarget{
protected:
	std::string _type;
public:
	std::string const &getType() const {return _type;}
	ATarget() {}
	ATarget(ATarget const &src) {*this = src;}
	ATarget(std::string const &type): _type(type) {}
	virtual ~ATarget() {}
	ATarget &operator=(ATarget const &src) {_type = src._type; return *this;}
	virtual ATarget *clone() const = 0;
	void getHitBySpell(ASpell const &src) const;
};

#include "ASpell.hpp"
