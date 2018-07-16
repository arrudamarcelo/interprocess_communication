#include <iostream>
#include <string>

class DummyObject {

public:
	DummyObject(std::string message, int num) : _message(message), _num(num) {}

	void printMessage() {
		std::cout << _message << std::endl;
		std::cout << "test" << std::endl;
	}

private:
	std::string _message;
	int _num;

};

