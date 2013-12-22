tst-gpio: Pin.o main_tst_GPIO.o Gpio.o 
	g++ -Wall -g -o tst-gpio Pin.o main_tst_GPIO.o Gpio.o

Pin.o: Sources/Pin.cpp Sources/Pin.hpp
	g++ -std=c++0x -c Sources/Pin.cpp

Gpio.o: Sources/Gpio.cpp Sources/Gpio.hpp
	g++ -std=c++0x -c Sources/Gpio.cpp

main_tst_GPIO.o: Sources/main_tst_GPIO.cpp
	g++ -c Sources/main_tst_GPIO.cpp

clean: 
	rm *.o