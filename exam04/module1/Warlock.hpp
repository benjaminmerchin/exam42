#pragma once

#include <iostream>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;
	std::vector<ASpell *> _array;
public:
	Warlock(std::string const &name, std::string const &title) : _name(name), _title(title) {std::cout << _name << ": This looks like another boring day.\n";}
	~Warlock() {
		for (std::vector<ASpell *>::iterator it = _array.begin(); it != _array.end(); it++)
			delete *it;
		std::cout << _name << ": My job here is done!\n";
	}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void setTitle(std::string const &title) {_title = title;}
	void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!\n";}
	void learnSpell(ASpell *src) {_array.push_back(src);}
	void forgetSpell(std::string const &spell_name) {
		for (std::vector<ASpell *>::iterator it = _array.begin(); it != _array.end(); it++)
			if ((*it)->getName() == spell_name) {
				delete *it; _array.erase(it); return;
			}
	}
	void launchSpell(std::string const &spell_name, ATarget const &ref) {
		for (std::vector<ASpell *>::iterator it = _array.begin(); it != _array.end(); it++)
			if ((*it)->getName() == spell_name) {
				(*it)->launch(ref); return;
			}
	}
};
