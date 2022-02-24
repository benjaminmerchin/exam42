#pragma once

#include <iostream>
#include "ASpell.hpp"

class Fireball : public ASpell {
public:
	Fireball() : ASpell("Fireball", "burnt to a crisp") {}
	~Fireball() {}
	virtual ASpell *clone() const {return new Fireball();}
};
