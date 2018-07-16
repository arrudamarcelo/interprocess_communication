#include "ClassSerialize.h"
#include <sstream>
#include <iostream>

void Serializible::deserialize(std::string attribMessage) {
	std::string att;
	std::vector<std::string> attsVec;
	std::istringstream split(attribMessage);
	while (std::getline(split, att, DELIMITER))
	{
		attsVec.emplace_back(att);
	}

	updateObj(attsVec);
}

std::string Serializible::classDescription() {
	std::string desc = "Class: " + className() + "\n";
	auto addInfo = [&desc](std::string item, std::list<std::string> subItems) {
		desc += "\t" + item + ":\n";
		for (auto si : subItems) {
			desc += "\t\t" + si + "\n";
		}
	};

	addInfo("Attributes", classAttribs());
	addInfo("Methods", classMethods());

	//add an empty line at the end
	desc += "\n";

	return desc;
}
