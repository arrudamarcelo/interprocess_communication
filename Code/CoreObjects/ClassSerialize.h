#pragma once

#include <list>
#include <string>
#include <vector>

#define DELIMITER '&'

/*
 * Abstract Class resposible for allow the serialization of classes.
 * The classes to be serialized needs to implement the pure virtual methods.
 */
class Serializible {

public:
	virtual std::string serialize() = 0;
	virtual void deserialize(std::string attribMessage);

	virtual std::string className() = 0;
	virtual std::list<std::string> classAttribs() = 0;
	virtual std::list<std::string> classMethods() = 0;
	virtual bool updateObj(std::vector<std::string> attributes) = 0;

	virtual std::string classDescription();
	virtual void printAttribValues() = 0;
};
