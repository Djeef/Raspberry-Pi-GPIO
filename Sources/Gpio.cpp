#include "Gpio.hpp"

Gpio::Gpio() {
	this->m_numberOfPins = 0;
}

Gpio::~Gpio() {
	map<int, Pin*>::iterator it;
	for(it = this->m_pins.begin(); it != m_pins.end(); it++) {
		delete(it->second);
		this->m_pins.erase(it);
	}
}

//Methodes
int Gpio::addPin(int number, string direction) {
	if(this->m_numberOfPins >= MAX_PINS) {
		return(-3);
	}
	try {
		Pin *newPin = new Pin(number, direction);
		if(!this->m_pins.insert(pair<int, Pin*>(number, newPin)).second) {
			return(-2);
		}
	} catch(string exception) {
		cerr << "PIN " << number << " " << exception << endl;
		return(-1);
	}
	this->m_numberOfPins++;
	return(0);
}

bool Gpio::removePin(int number) {
	map<int, Pin*>::iterator it = this->m_pins.find(number);
	if(it != this->m_pins.end()) {
		delete(it->second);
		this->m_pins.erase(it);
		this->m_numberOfPins--;
		return(true);
	}
	return(false);
}

bool Gpio::setDirectionOf(int number, string direction) {
	map<int, Pin*>::iterator it = this->m_pins.find(number);
	if(it != this->m_pins.end()) {
		try {
			it->second->setDirection(direction);
			return(true);
		} catch(string exception) {
			cerr << "PIN " << number << " " << exception << endl;
		}
	}
	return(false);
}

bool Gpio::getDirectionOf(int number, string &direction) {
	map<int, Pin*>::iterator it = this->m_pins.find(number);
	if(it != this->m_pins.end()) {
		direction = it->second->getDirection();
		return(true);
	}
	return(false);
}

bool Gpio::setValueOf(int number, int value) {
	map<int, Pin*>::iterator it = this->m_pins.find(number);
	if(it != this->m_pins.end()) {
		try {
			it->second->setValue(value);
			return(true);
		} catch(string exception) {
			cerr << "PIN " << number << " " << exception << endl;
		}
	}
	return(false);
}

bool Gpio::getValueOf(int number, string &value) {
	map<int, Pin*>::iterator it = this->m_pins.find(number);
	if(it != this->m_pins.end()) {
		value = to_string(it->second->getValue());
		return(true);
	}
	return(false);
}

//Accessors
int Gpio::getNumberOfPins() {
	return(this->m_numberOfPins);
}