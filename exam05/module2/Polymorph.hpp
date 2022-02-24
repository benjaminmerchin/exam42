#pragma once

#include <iostream>
#include "ASpell.hpp"

class Polymorph : public ASpell {
public:
	Polymorph() : ASpell("Polymorph", "turned into a critter") {}
	~Polymorph() {}
	virtual ASpell *clone() const {return new Polymorph();}
};
