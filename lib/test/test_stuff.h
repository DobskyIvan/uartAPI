

#include "..\inc\lib.h"
#include <stdint.h>
#include <stdio.h>

void uart1IRQ_Handler(); // async function
void uart2IRQ_Handler(); // async function

eErrorCode init_1 (void);
eErrorCode init_2 (void);
eErrorCode deinit_1 (void);
eErrorCode deinit_2 (void);
eErrorCode setBaudrate_1 (uint32_t baudrate);
eErrorCode setBaudrate_2 (uint32_t baudrate);
eErrorCode setParity_1 (eParity eParity);
eErrorCode setStopBits_1 (eStopBits eStopBits);
eErrorCode enable_1 (eRxSwitch rxSwitch, eTxSwitch txSwitch);
eErrorCode enable_2 (eRxSwitch rxSwitch, eTxSwitch txSwitch);
eErrorCode putByte_2 (uint8_t byteToSend);
eErrorCode getByte_1 (uint8_t *receiveByte);


