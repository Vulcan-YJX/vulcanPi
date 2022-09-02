#pragma once

//! @file 			vulcanSpi.hpp
//! @author 		Vulcan YJX <vulcanai@163.com> 
//! @created		2022-09-01
//! @last-modified 	2022-09-01
//! @brief			The Spi device class.

#include <time.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/spi/spidev.h>

namespace vulcanPi{

enum class spi_speed {
    S_500K,
    S_10M,
    S_Max,
};

class vulcanSpi{
private:

    int fd = -1;
    uint32_t mode_ = 0;
    uint8_t bits_ = 8;
    char *input_file;
    char *output_file;

    uint16_t delay_;
    int verbose;
    int transfer_size;
    int iterations;
    int interval = 5; /* interval in seconds for showing transfer rate */
    int rw_mode = 3; //1: read, 2: write, 3: write and read
    int rw_len = 4;
    int rw_times = 5;
    char *input_tx;
    uint32_t speed_ = 500000;


private:
    
    void pabort(const char *s);
public:
    int8_t init(const std::string& dev = "/dev/spidev2.0", spi_speed speedCustom_ = spi_speed::S_10M,uint8_t per_word =8,uint8_t log = 0);
    
public:
    void hex_dump(const unsigned char *src, size_t length, size_t line_size,char *prefix);
    int unescape(char *_dst, char *_src, size_t len);
    void transfer(int fd, uint8_t const *tx, uint8_t const *rx, uint32_t len);
    void transfer_escaped_string(char *str);
    void transfer_file(char *filename);
    ~vulcanSpi();
    
    
};

}
