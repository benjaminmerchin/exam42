#include "ASpell.hpp"

void ASpell::launch(ATarget const &src) const {src.getHitBySpell(*this);}