#pragma once

#include <iostream>

class Warlock {
private:
	std::string _name;
	std::string _title;
	Warlock() {}
	Warlock(Warlock const &src) {*this = src;}
	Warlock &operator=(Warlock const &src) {_name = src._name; _title = src._title; return *this;}
public:
	Warlock(std::string const &name, std::string const &title) : _name(name), _title(title) {std::cout << _name << ": This looks like another boring day.\n";}
	~Warlock() {std::cout << _name << ": My job here is done!\n";}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void setTitle(std::string const &title) {_title = title;}
	void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!\n";}
};
