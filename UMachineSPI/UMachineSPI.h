/**
 * UMachineSPI
 *
 * A simple SPI machine.
 */

#ifndef __U_MACHINE_SPI
#define __U_MACHINE_SPI

#include <SPI.h>
#include <UMachine.h>
#include <UMessageList.h>
#include <USPIMessage.h>

enum UMachineSPIState {USPIIdle,USPIActive,USPINext};

class UMachineSPI : public UMachine {
	public:
		UMachineSPI();
		UMessage *receive(UMessage *msg);
		void begin();
		void end();

		void configure();

		/* Machine State */
		UMessageList waiting;
		USPIMessage *active;
		uint8_t byteIndex;
		UMessage loop;
		UMachineSPIState state;

		/**
		 * The current SPI state
		 */

		/*TODO: One field*/
		
		uint8_t bitOrder;
		uint8_t clockDivider;
		uint8_t dataMode;
		bool configured;

};

#endif
