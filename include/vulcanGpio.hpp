
//! @file 			vulcanGpio.hpp
//! @author 		Vulcan YJX <vulcanai@163.com> 
//! @created		2022-09-02
//! @last-modified 	2022-09-02
//! @brief			The horizon x3 pi Gpio class.


#ifndef __VULCAN_GPIO__H
#define __VULCAN_GPIO__H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Exception.hpp"

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF	64
#define RET_OK 0

namespace vulcanPi{

class vulcanGpio{
public:
    
    /// \brief		Sends a binary message over the com port.
    /// \param		gpio		Gpio pin number.
    /// \throws		vulcanPi::Exception gpio/export.
    int gpio_export(unsigned int gpio);
    
    /// \brief		Sends a binary message over the com port.
    /// \param		gpio		Gpio pin number.
    /// \throws		vulcanPi::Exception gpio/export.
    int gpio_unexport(unsigned int gpio);
    
    /// \brief		Sends a binary message over the com port.
    /// \param		gpio		Gpio pin number.
    /// \param		out_flag	1/0 set Gpio pin out/in.
    /// \throws		vulcanPi::Exception gpio/direction.
    int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
    
    /// \brief		Set the level of Gpio.
    /// \param		gpio		Gpio pin number.
    /// \param		value		1/0 set Gpio value High/low.
    /// \throws		vulcanPi::Exception gpio/set-value.
    int gpio_set_value(unsigned int gpio, unsigned int value);
    
    /// \brief		Get the level of Gpio.
    /// \param		gpio		Gpio pin number.
    /// \param		value		Gpio input Io value.
    /// \throws		vulcanPi::Exception gpio/get-value.
    int gpio_get_value(unsigned int gpio, unsigned int *value);
    
    /// \brief		Configure GPIO interrupt mode.
    /// \param		gpio		Gpio pin number.
    /// \param		edge		none: GPIO is not an interrupt pin.
    ///                         rising: Rising edge triggered interrupt.
    ///                         falling: Falling edge triggered interrupt.
    ///                         both: Indicates that the pin is an edge triggered interrupt.
    /// \throws		vulcanPi::Exception gpio/set-edge.
    int gpio_set_edge(unsigned int gpio, char *edge);


};

}

#endif /*__VULCAN_GPIO__H*/
