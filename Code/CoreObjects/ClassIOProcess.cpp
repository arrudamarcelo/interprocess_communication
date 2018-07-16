#include "ClassIOProcess.h"
#include <iostream>

ClassIOProcess::ClassIOProcess(std::string name, int s) : Serializible(),
														  _className(name),
														  _sizeKb(s) {
}

bool ClassIOProcess::cacheCleanUp() {
	std::cout << "cleaning cache" << std::endl;
	return true;
}

std::string ClassIOProcess::className() {
	return _className;
}

std::list<std::string> ClassIOProcess::classAttribs() {
	return { "className", "sizeKb" };
}

std::list<std::string> ClassIOProcess::classMethods() {
	return { "cacheCleanUp()", "serialize()",
		"className()", "classAttribs()", "classMethods()" };
}

std::string ClassIOProcess::serialize() {
	return _className + std::string(1, DELIMITER) + std::to_string(_sizeKb);
}

bool ClassIOProcess::updateObj(std::vector<std::string> attributes) {
	if( attributes.size() == 2){
		_className = attributes[0];
		_sizeKb = std::stoi(attributes[1]);

		return true;
	}

	return false;
}

void ClassIOProcess::printAttribValues() {
	std::cout << "Atrributes: " << std::endl;
	std::cout << "\t_className: " << _className << std::endl;
	std::cout << "\t_sizeKb: " << _sizeKb << std::endl;
}
