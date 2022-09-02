
//! @file 			vulcanSpi.cpp
//! @author 		Vulcan YJX <vulcanai@163.com> 
//! @created		2022-09-01
//! @last-modified 	2022-09-01
//! @brief			The Spi device class.


#include <iostream>
#include "vulcanSpi.hpp"


namespace vulcanPi{

int8_t vulcanSpi::init(const std::string& dev, spi_speed speedCustom_,uint8_t per_word,uint8_t log){
    int8_t ret;
    std::string device_ = dev;
    fd = open(device_.c_str(), O_RDWR);
    if (fd < 0){
        pabort("can't open device");    
    }
    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode_);
    if (ret == -1){
        pabort("can't set spi mode");
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode_);
    if (ret == -1){
        pabort("can't get spi mode");
    }
    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &per_word);
    if (ret == -1){
        pabort("can't set bits per word");
    }
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &per_word);
    if (ret == -1){
        pabort("can't get bits per word");
    }
    
    /*
     * max speed hz
     */
    switch(speedCustom_) {
        case spi_speed::S_500K:
            speed_ = 500000;
            break;
        case spi_speed::S_10M:
            speed_ = 10000000;
            break;
        case spi_speed::S_Max:
            speed_ = 12000000;
            break;
        default:
            printf("value not supported!");
    }
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed_);
    if (ret == -1)
        pabort("can't set max speed hz");

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed_);
    if (ret == -1)
        pabort("can't get max speed hz");


    if(log){
        printf("spi mode: 0x%x\n", mode_);
        printf("bits per word: %d\n", per_word);
        printf("max speed: %d Hz (%d KHz)\n", speed_, speed_/1000);
    }
    return ret;
}

void vulcanSpi::hex_dump(const unsigned char *src, size_t length, size_t line_size,
        char *prefix)
{
    int i = 0;
    const unsigned char *address = src;
    const unsigned char *line = address;
    unsigned char c;

    printf("%s | ", prefix);
    while (length-- > 0) {
        printf("%02X ", *address++);
        if (!(++i % line_size) || (length == 0 && i % line_size)) {
            if (length == 0) {
                while (i++ % line_size)
                    printf("__ ");
            }
            printf(" | ");  /* right close */
            while (line < address) {
                c = *line++;
                printf("%c", (c < 33 || c == 255) ? 0x2E : c);
            }
            printf("\n");
            if (length > 0)
                printf("%s | ", prefix);
        }
    }
}

int vulcanSpi::unescape(char *_dst, char *_src, size_t len)
{
    int ret = 0;
    int match;
    char *src = _src;
    char *dst = _dst;
    unsigned int ch;

    while (*src) {
        if (*src == '\\' && *(src+1) == 'x') {
            match = sscanf(src + 2, "%2x", &ch);
            if (!match)
                pabort("malformed input string");

            src += 4;
            *dst++ = (unsigned char)ch;
        } else {
            *dst++ = *src++;
        }
        ret++;
    }
    return ret;
}

void vulcanSpi::transfer(int fd, uint8_t const *tx, uint8_t const *rx, uint32_t len_)
{
    int ret;
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = len_,
        .speed_hz = speed_,
        .delay_usecs = delay_,
        .bits_per_word = bits_,
    };

    if (mode_ & SPI_TX_QUAD)
        tr.tx_nbits = 4;
    else if (mode_ & SPI_TX_DUAL)
        tr.tx_nbits = 2;
    if (mode_ & SPI_RX_QUAD)
        tr.rx_nbits = 4;
    else if (mode_ & SPI_RX_DUAL)
        tr.rx_nbits = 2;
    if (!(mode_ & SPI_LOOP)) {
        if (mode_ & (SPI_TX_QUAD | SPI_TX_DUAL))
            tr.rx_buf = 0;
        else if (mode_ & (SPI_RX_QUAD | SPI_RX_DUAL))
            tr.tx_buf = 0;
    }

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
        pabort("can't send spi message");

    char c_buf[] = "TX";
    if (verbose)
        hex_dump(tx, len_, 32, c_buf);
    strcpy(c_buf,"RX");
    if (verbose)
        hex_dump(rx, len_, 32,c_buf);
}

void vulcanSpi::transfer_escaped_string(char *str)
{
    size_t size = strlen(str);
    uint8_t *tx;
    uint8_t *rx;

    tx = (uint8_t *)malloc(size);
    if (!tx)
        pabort("can't allocate tx buffer");

    rx = (uint8_t *)malloc(size);
    if (!rx)
        pabort("can't allocate rx buffer");

    size = unescape((char *)tx, str, size);
    printf("size: %ld\n", size);
    transfer(fd, tx, rx, size);
    free(rx);
    free(tx);
}

void vulcanSpi::transfer_file(char *filename)
{
    ssize_t bytes;
    struct stat sb;
    int tx_fd;
    uint8_t *tx;
    uint8_t *rx;

    if (stat(filename, &sb) == -1)
        pabort("can't stat input file");

    tx_fd = open(filename, O_RDONLY);
    if (tx_fd < 0)
        pabort("can't open input file");

    tx = (uint8_t *)malloc(sb.st_size);
    if (!tx)
        pabort("can't allocate tx buffer");

    rx = (uint8_t *)malloc(sb.st_size);
    if (!rx)
        pabort("can't allocate rx buffer");

    bytes = read(tx_fd, tx, sb.st_size);
    if (bytes != sb.st_size)
        pabort("failed to read input file");

    transfer(fd, tx, rx, sb.st_size);
    free(rx);
    free(tx);
    close(tx_fd);
}


void vulcanSpi::pabort(const char *s)
{
    perror(s);
    abort();
}

vulcanSpi::~vulcanSpi()
{
  try {
      close(fd);
  }catch(const std::system_error& e) {
      std::cout << "Caught system_error with code " << e.code() 
      << " meaning " << e.what() << '\n';
  }
}

}
