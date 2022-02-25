#pragma once

#include <iostream>
#include <map>
#include "ASpell.hpp"

class SpellBook {
private:
	std::map<std::string, ASpell *> _array;
	SpellBook(SpellBook const &src) {*this = src;}
	SpellBook &operator=(SpellBook const &src) {(void)src;return *this;}
public:
	SpellBook() {}
	~SpellBook() {
		std::map<std::string, ASpell *>::iterator it = _array.begin();
		while (it != _array.end())
		{
			delete it->second;
			it++;
		}
		_array.clear();
	}
	void learnSpell(ASpell* spell_ptr) {
		if (spell_ptr)
			_array.insert(std::pair<std::string, ASpell *>(spell_ptr->getName(), spell_ptr->clone()));
	}
	void forgetSpell(std::string const & spell_name) {
		std::map<std::string, ASpell *>::iterator it = _array.find(spell_name);
		if (it != _array.end())
			delete it->second;
		_array.erase(spell_name);
	}
	ASpell* createSpell(std::string const & spell_name) {
		std::map<std::string, ASpell *>::iterator it = _array.find(spell_name);
		if (it != _array.end())
			return _array[spell_name];
		return NULL;
	}
};
