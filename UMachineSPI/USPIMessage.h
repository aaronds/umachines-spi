/**
 * USPIMessage.h
 *
 * A message to represent each spi action.
 */

#ifndef __U_SPI_MESSAGE
#define __U_SPI_MESSAGE

#include <UMessage.h>

extern "C" {
	#include <inttypes.h>
	#include <string.h>
}

class USPIMessage : public UMessage {

	public:
		USPIMessage();

		uint8_t *buffer;
		uint8_t length;

		/*
		 * TODO: condense these into one field
		 */

		uint8_t bitOrder;
		uint8_t clockDivider;
		uint8_t dataMode;
		uint8_t clockEnablePin;

};

#endif
