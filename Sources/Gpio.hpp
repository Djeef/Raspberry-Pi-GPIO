#ifndef GPIO_H
#define GPIO_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstring>
#include "Pin.hpp"

#define MAX_PINS 26

using namespace std;

class Gpio {
	private:
		map<int, Pin*> m_pins;
		int m_numberOfPins;

	public:
		// Constructor/Destructor
		Gpio();
		~Gpio();

		// Methodes
		int addPin(int number, string direction);
		bool removePin(int number);
		bool setDirectionOf(int number, string direction);
		bool getDirectionOf(int number, string &direction);
		bool setValueOf(int number, int value);
		bool getValueOf(int number, string &value);

		// Accessors
		int getNumberOfPins();
};

#endif /*GPIO_H*/