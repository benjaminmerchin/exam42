#pragma once

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell {
protected:
	std::string _name;
	std::string _effects;
public:
	std::string const &getName() const {return _name;}
	std::string const &getEffects() const {return _effects;}
	ASpell() {}
	ASpell(ASpell const &src) {*this = src;}
	ASpell(std::string const &name, std::string const &effects): _name(name), _effects(effects) {}
	virtual ~ASpell() {}
	ASpell &operator=(ASpell const &src) {_name = src._name; _effects = src._effects; return *this;}
	virtual ASpell *clone() const = 0;
	void launch(ATarget const &src) const;
};
