#include "UMachineSPI.h"

UMachineSPI::UMachineSPI(){
	configured = false;
	state = USPIIdle;
	byteIndex = 0;
}

UMessage *UMachineSPI::receive(UMessage *msg){

	/* If Message is loop check the active transfer*/

	if(msg == &loop){
		switch(state){
			case USPIActive:
				if((SPSR & _BV(SPIF))){
					active->buffer[byteIndex] = SPDR;
					byteIndex++;

					if(byteIndex < active->length){
						SPDR = active->buffer[byteIndex];
					}else{
						send(active,active->from);
						state = USPINext;
					}
				}

				if(state != USPINext){
					send(&loop,this);
					return NULL;
				}

			case USPINext:
				active = (USPIMessage *) waiting.shift();
				byteIndex = 0;

				if(!active){
					state = USPIIdle;
					return NULL;
				}

				configure();

				SPDR = active->buffer[byteIndex];
				state = USPIActive;

				send(&loop,this);
				return NULL;
				break;

			default:
				break;
				/* Broken */
		}
	}else{
		waiting.add(msg);
		if(state == USPIIdle){
			state = USPINext;
			send(&loop,this);
			return NULL;
		}
	}
}

void UMachineSPI::configure(){
	/* Check the spi config against the current one */

	if(!configured || active->bitOrder != bitOrder || active->clockDivider != clockDivider || active->dataMode != dataMode){
		/*Reconfigure spi*/
		SPI.setBitOrder(active->bitOrder);
		bitOrder = active->bitOrder;

		SPI.setDataMode(active->dataMode);
		dataMode = active->dataMode;

		SPI.setClockDivider(active->clockDivider);
		clockDivider = active->clockDivider;

		configured = true;
	}
}


void UMachineSPI::begin(){
	SPI.begin();
}

void UMachineSPI::end(){
	SPI.end();
}
