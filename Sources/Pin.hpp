#ifndef PIN_H
#define PIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstring>

#define OUT "out"
#define IN "in"
#define HIGH 1
#define LOW 0

#define PATH_OF_GPIO "/sys/class/gpio"
#define PATH_OF_EXPORT string(PATH_OF_GPIO) + "/export"
#define PATH_OF_UNEXPORT string(PATH_OF_GPIO) + "/unexport"

using namespace std;

class Pin {
	private:
		int m_number;
		string m_direction;
		string m_directionPath;
		string m_valuePath;

	public:
		// Constructor/Destructor
		Pin(int number, string direction);
		~Pin();

		// Methodes
		void exportPin();
		void unexportPin();

		// Accessors
		void setDirection(string direction);
		string getDirection() const;
		void setValue(int value);
		int getValue() const;
		int getNumber() const;
};

#endif /*PIN_H*/
