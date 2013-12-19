#include <iostream>
#include <csignal>
#include <cstdlib>
#include "Gpio.hpp"

bool interceptedInteruption = false;

void sigHandler(int sig) {
	interceptedInteruption = true;
}

int main(int argc, char *argv[]) {
	Gpio gpio;
	string buffer;
	int ret;

	struct sigaction sigactionStruct;
	sigactionStruct.sa_handler = sigHandler;
	sigactionStruct.sa_flags = 0;
	sigemptyset(&sigactionStruct.sa_mask);

	if(sigaction(SIGINT, &sigactionStruct, NULL) == -1) {
		cerr << "SIGACTION FAILED : " << string(strerror(errno)) << endl;
		return(EXIT_FAILURE);
	}

	// NUMBER OF PINS
	cout << "NUMBER OF PINS : " << gpio.getNumberOfPins() << endl;

	// ADD
	for(int i = 0; i < 5 ; i++) {
		if(i % 2 == 0) {
			ret = gpio.addPin(i, "in");
		} else {
			ret = gpio.addPin(i, "out");
		}
		cout << "RETURN : " << ret << endl;
		if(ret == -3) {
			cout << "WORK : -3 " << i << endl;
			break;
		} 
	}
	gpio.removePin(4);
	if(gpio.addPin(2, "out") == -2) {
		cout << "WORK AGAIN" << endl;
	}
	if(gpio.addPin(4, "out") == 0) {
		cout << "WORK AGAIN AND AGAIN" << endl;
	}
	// VALUES
	if(gpio.getValueOf(1, buffer)) {
		cout << "PIN 1 : " << buffer << endl;
	}
	if(gpio.getValueOf(2, buffer)) {
		cout << "PIN 2 : " << buffer << endl;
	}
	if(gpio.getValueOf(3, buffer)) {
		cout << "PIN 3 : " << buffer << endl;
	}
	if(gpio.getValueOf(4, buffer)) {
		cout << "PIN 4 : " << buffer << endl;
	}
	gpio.setValueOf(1, 78);
	if(gpio.getValueOf(1, buffer)) {
		cout << "PIN 1 : " << buffer << endl;
	}
	gpio.setValueOf(2, -12);
	if(gpio.getValueOf(2, buffer)) {
		cout << "PIN 2 : " << buffer << endl;
	}
	gpio.setValueOf(3, 1);
	if(gpio.getValueOf(3, buffer)) {
		cout << "PIN 3 : " << buffer << endl;
	}
	gpio.setValueOf(4, 0);
	if(gpio.getValueOf(4, buffer)) {
		cout << "PIN 4 : " << buffer << endl;
	}

	// DIRECTIONS
	if(gpio.getDirectionOf(1, buffer)) {
		cout << "PIN 1 : " << buffer << endl;
	}
	if(gpio.getDirectionOf(2, buffer)) {
		cout << "PIN 2 : " << buffer << endl;
	}
	if(gpio.getDirectionOf(3, buffer)) {
		cout << "PIN 3 : " << buffer << endl;
	}
	if(gpio.getDirectionOf(4, buffer)) {
		cout << "PIN 4 : " << buffer << endl;
	}
	gpio.setDirectionOf(1, "in");
	if(gpio.getDirectionOf(1, buffer)) {
		cout << "PIN 1 : " << buffer << endl;
	}
	gpio.setDirectionOf(2, "out");
	if(gpio.getDirectionOf(2, buffer)) {
		cout << "PIN 2 : " << buffer << endl;
	}
	gpio.setDirectionOf(3, "in");
	if(gpio.getDirectionOf(3, buffer)) {
		cout << "PIN 3 : " << buffer << endl;
	}
	gpio.setDirectionOf(4, "out");
	if(gpio.getDirectionOf(4, buffer)) {
		cout << "PIN 4 : " << buffer << endl;
	}

	// NUMBER OF PINS 2
	cout << "NUMBER OF PINS : " << gpio.getNumberOfPins() << endl;
	gpio.removePin(4);
	cout << "NUMBER OF PINS : " << gpio.getNumberOfPins() << endl;
	if(!gpio.getValueOf(4, buffer)) {
		cout << "PIN 4 REMOVED !!" << endl;
	}

	while(true) {
		if(interceptedInteruption) {
			cout << "\nInteruption : the GPIO is going to be deleted" << endl;
			gpio.~Gpio();
			break;
		}
	}
	return(0);
}