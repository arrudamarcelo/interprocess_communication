#include "ClassKernelProcess.h"
#include <iostream>

ClassKernelProcess::ClassKernelProcess(std::string name, bool isLatestKernel) : 
										Serializible(), 
										_className(name),
										_isLatestKernel() {
}

void ClassKernelProcess::restartProcess() {
	std::cout << "restarting process" << std::endl;
}

std::string ClassKernelProcess::className() {
	return _className;
}

std::list<std::string> ClassKernelProcess::classAttribs() {
	return { "className", "isLatestKernel" };
}

std::list<std::string> ClassKernelProcess::classMethods() {
	return { "restartProcess()", "serialize()",
		"className()", "classAttribs()", "classMethods()", };
}

std::string ClassKernelProcess::serialize() {
	return _className + std::string(1, DELIMITER) + ((_isLatestKernel) ? "true" : "false");
}

bool ClassKernelProcess::updateObj(std::vector<std::string> attributes) {
	if(attributes.size() == 2){
		_className = attributes[0];
		_isLatestKernel = (attributes[1] == "true") ? true : false;
		return true;
	}

	return false;
}

void ClassKernelProcess::printAttribValues() {
	std::cout << "Attributes:" << std::endl;
	std::cout << "\t_className: " << _className << std::endl;
	std::cout << "\t_isLatestKernel: " << ((_isLatestKernel == true) ? "true" : "false") << std::endl;
}
