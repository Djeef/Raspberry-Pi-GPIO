#include "Pin.hpp"

// Constructor
Pin::Pin(int number, string direction) {
	this->m_number = number;
	this->m_direction = direction;
	this->m_directionPath = string(PATH_OF_GPIO) + "/gpio" + to_string(this->m_number) + "/direction";
	this->m_valuePath = string(PATH_OF_GPIO) + "/gpio" + to_string(this->m_number) + "/value";

	try {
		this->exportPin();
		this->setDirection(direction);
	} catch(string exception) {
		throw(exception);
	}
}

Pin::~Pin() {
	this->unexportPin();
}

// Methodes
void Pin::exportPin() {
	ofstream exportFile(PATH_OF_EXPORT);
	if(!exportFile) {
		throw("EXPORT FAILED : " + string(strerror(errno)));
	}
	exportFile << this->m_number;
	exportFile.close();
}

void Pin::unexportPin() {
	ofstream unexportFile(PATH_OF_UNEXPORT);
	if(!unexportFile) {
		throw("UNEXPORT FAILED : " + string(strerror(errno)));
	}
	unexportFile << this->m_number;
	unexportFile.close();
}


// Accessors
void Pin::setDirection(string direction) {
	ofstream directionFile(this->m_directionPath);
	if(!directionFile) {
		throw("SET DIRECTION FAILED : " + string(strerror(errno)));
	}
	this->m_direction = direction;
	directionFile << direction;
	directionFile.close();
}

string Pin::getDirection() const {
	return(this->m_direction);
}

void Pin::setValue(int value) {
	ofstream valueFile(this->m_valuePath);
	if(!valueFile) {
		throw("SET VALUE FAILED : " + string(strerror(errno)));
	}
	valueFile << value;
	valueFile.close();
}

int Pin::getValue() const {
	string value;
	ifstream valueFile(this->m_valuePath);
	if(!valueFile) {
		throw("GET VALUE FAILED : " + string(strerror(errno)));
	}
	valueFile >> value;
	valueFile.close();
	if(value != "0") {
		return(1);
	} else {
		return(0);
	}
}

int Pin::getNumber() const {
	return(this->m_number);
}
