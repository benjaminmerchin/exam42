#pragma once

#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;
	std::map<std::string, ASpell *> arr_spell;
public:
	Warlock(std::string const &name, std::string const &title) : _name(name), _title(title) {std::cout << _name << ": This looks like another boring day.\n";}
	~Warlock() {
		for (std::map<std::string, ASpell *>::iterator it = arr_spell.begin(); it != arr_spell.end(); it++)
			delete it->second;
		arr_spell.clear();
		std::cout << _name << ": My job here is done!\n";
	}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void setTitle(std::string const &title) {_title = title;}
	void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!\n";}
	void learnSpell(ASpell* spell_ptr) {
		if (spell_ptr)
			arr_spell.insert(std::pair<std::string, ASpell *>(spell_ptr->getName(), spell_ptr->clone()));
	}
	void forgetSpell(std::string const & spell_name) {
		std::map<std::string, ASpell *>::iterator it = arr_spell.find(spell_name);
		if (it != arr_spell.end())
			delete it->second;
		arr_spell.erase(spell_name);
	}
	void launchSpell(std::string const &spell_name, ATarget const &ref) {
		ASpell* temp = arr_spell[spell_name];
		if (temp)
			temp->launch(ref);
	}
};
