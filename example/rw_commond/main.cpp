
// fileName: main.cpp

#include "vulcanSerial.hpp"
#include <iostream>

using namespace vulcanPi;

int main() {

	SerialPort serialPort("/dev/ttyS3", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	serialPort.Open(); 

	while(1){
		while(serialPort.Available() > 0){
		    // Write some ASCII data
		    serialPort.Write("Vulcan Serial");

		    std::string readData;
		    serialPort.Read(readData);
		    std::cout << readData << std::endl;
		}

	}
	// Close the serial port
	serialPort.Close();
}
