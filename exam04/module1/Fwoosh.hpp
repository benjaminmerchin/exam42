#pragma once

#include <iostream>
#include "ASpell.hpp"

class Fwoosh : public ASpell {
public:
	Fwoosh() : ASpell("Fwoosh", "fwooshed") {}
	~Fwoosh() {}
	virtual ASpell *clone() const {return new Fwoosh();}
};
