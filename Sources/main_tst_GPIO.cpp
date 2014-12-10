#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include "Gpio.hpp"

bool interceptedInteruption = false;

void sigHandler(int sig) {
	interceptedInteruption = true;
}

// Exemple : Blink diode pin 4
int main(int argc, char *argv[]) {
	Gpio gpio;	// The GPIO
	struct sigaction sigactionStruct;
	sigactionStruct.sa_handler = sigHandler;
	sigactionStruct.sa_flags = 0;
	sigemptyset(&sigactionStruct.sa_mask);

	if(sigaction(SIGINT, &sigactionStruct, NULL) == -1) {
		cerr << "SIGACTION FAILED : " << string(strerror(errno)) << endl;
		return(EXIT_FAILURE);
	}
	gpio.addPin(4, OUT);	// ADD PIN 4 (OUT)
	while(true) {
		gpio.setValueOf(4, HIGH);	// WRITE 1 IN PIN 4
		sleep(1);
		gpio.setValueOf(4, LOW);	// WRITE 0 IN PIN 4
		sleep(1);
		if(interceptedInteruption) {
			cout << "\nInteruption : the GPIO is going to be deleted" << endl;
			gpio.~Gpio();	//Delete the GPIO
			break;
		}
	}
	return(EXIT_SUCCESS);
}
