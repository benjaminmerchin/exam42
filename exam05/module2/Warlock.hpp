#pragma once

#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;
	SpellBook _book;
public:
	Warlock(std::string const &name, std::string const &title) : _name(name), _title(title) {
		std::cout << _name << ": This looks like another boring day.\n";
	}
	~Warlock() {
		std::cout << _name << ": My job here is done!\n";
	}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void setTitle(std::string const &title) {_title = title;}
	void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!\n";}
	void learnSpell(ASpell *aspell_ptr) {
		_book.learnSpell(aspell_ptr);
	}
	void forgetSpell(std::string const &spell_name) {
		_book.forgetSpell(spell_name);
	}
	void launchSpell(std::string const &spell_name, ATarget const &ref) {
		ASpell *temp = _book.createSpell(spell_name);
		if (temp)
			temp->launch(ref);
	}
};
