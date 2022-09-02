// fileName: main.cpp

#include "vulcanSpi.hpp"
#include <iostream>

using namespace vulcanPi;

int main() {

	vulcanSpi mySpi;
	mySpi.init("/dev/spidev2.0",spi_speed::S_Max);
	char sendMsg[] = "demo";
	mySpi.transfer_escaped_string(sendMsg);
}
