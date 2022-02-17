#pragma once

#include <iostream>
#include <string>

class Warlock {
private:
	std::string _name;
	std::string _title;
	Warlock() {}
	Warlock(Warlock const &rhs) {(void)rhs;}
	Warlock &operator=(Warlock const &rhs) {(void)rhs; return *this;}
public:
	Warlock(std::string name, std::string title) : _name(name), _title(title) {std::cout << _name << ": This looks like another boring day." << std::endl;}
	~Warlock() {std::cout << _name << ": My job here is done!" << std::endl;}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void setTitle(std::string const &title) {_title = title;}
	void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << " !"<< std::endl;}
};
