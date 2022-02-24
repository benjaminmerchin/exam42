#pragma once

#include <iostream>
#include "ATarget.hpp"

class Dummy : public ATarget {
public:
	Dummy() : ATarget("Target Practice Dummy") {}
	~Dummy() {}
	virtual ATarget *clone() const {return new Dummy();}
};
