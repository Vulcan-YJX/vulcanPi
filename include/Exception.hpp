#ifndef VULCAN_PI_LINUX_SERIAL_EXCEPTION_H_
#define VULCAN_PI_LINUX_SERIAL_EXCEPTION_H_

// System includes
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <stdlib.h>

namespace vulcanPi {

        class Exception : public std::runtime_error {

        public:
            Exception(const char *file, int line, const std::string &arg) :
                    std::runtime_error(arg) {
                msg_ = std::string(file) + ":" + std::to_string(line) + ": " + arg;
            }

            ~Exception() throw() {}

            const char *what() const throw() override {
                return msg_.c_str();
            }

        private:
            std::string msg_;
        };
        
        

} // namespace vulcanPi


#define THROW_EXCEPT(arg) throw Exception(__FILE__, __LINE__, arg);


#endif // VULCAN_PI_LINUX_SERIAL_EXCEPTION_H_
