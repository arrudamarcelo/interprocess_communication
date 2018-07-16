#pragma once

#include "ClassSerialize.h"

/*
* Example of a class exchanged by server and client.
* Handles string and boolean datatypes
*/
class ClassKernelProcess : public Serializible
{
	public:
		ClassKernelProcess() = default;
		ClassKernelProcess(std::string name, bool isLatestKernel);

		/*
		* Example of a method.
		*/
		void restartProcess();

		/*
		* Method responsible for print values.
		*/
		void printAttribValues();

		/*
		* Methods responsible for serialize / deserialize the class.
		*/
		std::string serialize();
		std::string className();
		std::list<std::string> classAttribs();
		std::list<std::string> classMethods();
		bool updateObj(std::vector<std::string> attributes);

	private:
		std::string _className;
		bool _isLatestKernel;
};
