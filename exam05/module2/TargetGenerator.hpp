#pragma once

#include <iostream>
#include <map>
#include "ATarget.hpp"

class TargetGenerator {
private:
	std::map<std::string, ATarget *> arr_target;
	TargetGenerator(TargetGenerator const &src) {*this = src;}
	TargetGenerator &operator=(TargetGenerator const &src) {(void)src; return *this;}
public:
	TargetGenerator() {}
	~TargetGenerator() {
		std::map<std::string, ATarget *>::iterator it_begin = arr_target.begin();
		std::map<std::string, ATarget *>::iterator it_end = arr_target.end();
		while (it_begin != it_end)
		{
			delete it_begin->second;
			it_begin++;
		}
		arr_target.clear();
	}
	void learnTargetType(ATarget* target_ptr) {
		if (target_ptr)
			arr_target.insert(std::pair<std::string, ATarget *>(target_ptr->getType(), target_ptr->clone()));
	}
	void forgetTargetType(std::string const & target_name) {
		std::map<std::string, ATarget *>::iterator it = arr_target.find(target_name);
		if (it != arr_target.end())
			delete it->second;
		arr_target.erase(target_name);
	}
	ATarget* createTarget(std::string const & target_name) {
		std::map<std::string, ATarget *>::iterator it = arr_target.find(target_name);
		if (it != arr_target.end())
			return arr_target[target_name];
		return NULL;
	}
};
