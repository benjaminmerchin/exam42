#pragma once

#include <iostream>
#include <map>
#include "ATarget.hpp"

class TargetGenerator {
private:
	std::map<std::string, ATarget *> _array;
	TargetGenerator(TargetGenerator const &src) {*this = src;}
	TargetGenerator &operator=(TargetGenerator const &src) {(void)src; return *this;}
public:
	TargetGenerator() {}
	~TargetGenerator() {
		std::map<std::string, ATarget *>::iterator it = _array.begin();
		while (it != _array.end())
		{
			delete it->second;
			it++;
		}
		_array.clear();
	}
	void learnTargetType(ATarget* target_ptr) {
		if (target_ptr)
			_array.insert(std::pair<std::string, ATarget *>(target_ptr->getType(), target_ptr->clone()));
	}
	void forgetTargetType(std::string const & target_name) {
		std::map<std::string, ATarget *>::iterator it = _array.find(target_name);
		if (it != _array.end())
			delete it->second;
		_array.erase(target_name);
	}
	ATarget* createTarget(std::string const & target_name) {
		std::map<std::string, ATarget *>::iterator it = _array.find(target_name);
		if (it != _array.end())
			return _array[target_name];
		return NULL;
	}
};
