#pragma once

#include "ClassSerialize.h"

/*
* Example of a class exchanged by server and client.
* Handles string and int datatypes
*/
class ClassIOProcess : public Serializible
{
	public:
		ClassIOProcess() = default;
		ClassIOProcess(std::string name, int s);

		/*
		* Example of a method.
		* @return bool value.
		*/
		bool cacheCleanUp();

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
		int _sizeKb;
};

