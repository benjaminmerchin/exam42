#include "ATarget.hpp"

void ATarget::getHitBySpell(ASpell const &src) const {std::cout << _type << " has been " << src.getEffects() << "!\n";}