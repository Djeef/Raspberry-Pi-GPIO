#include <iostream>
#include <csignal>
#include <cstdlib>
#include "Gpio.hpp"

bool interceptedInteruption = false;

void sigHandler(int sig) {
	interceptedInteruption = true;
}

// Exemple : Blink diode pin 4
int main(int argc, char *argv[]) {
	Gpio gpio;
	struct sigaction sigactionStruct;
	sigactionStruct.sa_handler = sigHandler;
	sigactionStruct.sa_flags = 0;
	sigemptyset(&sigactionStruct.sa_mask);

	if(sigaction(SIGINT, &sigactionStruct, NULL) == -1) {
		cerr << "SIGACTION FAILED : " << string(strerror(errno)) << endl;
		return(EXIT_FAILURE);
	}
	gpio.addPin(4, "out");
	while(true) {
		gpio.setValueOf(4, 1);
		sleep(1);
		gpio.setValueOf(4, 0);
		sleep(1);
		if(interceptedInteruption) {
			cout << "\nInteruption : the GPIO is going to be deleted" << endl;
			gpio.~Gpio();
			break;
		}
	}
	return(EXIT_SUCCESS);
}