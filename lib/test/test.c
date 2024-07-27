
// gcc -o test.exe test.c ..\src\lib.c test_stuff.c -Wall -Wextra

#include "test_stuff.h"

sUartApi uart1;
sUartApi uart2;

eErrorCode callback (uint8_t *receiveByte){
    static uint32_t rcvCnt = 0;
    static uint8_t rcvBuffer[20]; 
    printf("callback from uart 1 receive callback(), byte received: 0x%x\n", *receiveByte);
    rcvBuffer[rcvCnt] = *receiveByte;
    rcvCnt++;
    if (rcvCnt == 5){ // may be 128
        rcvCnt = 0;
        if (uartGetTxStatus(&uart2) != STATE_TX_BUSY){
            uartSend(&uart2, rcvBuffer, 5);
        }
    }
    
    return E_NOERR;
}

int main(void){

    printf("start\n");

    if (uartInit(&uart1, init_1) != E_NOERR){
        printf("uart 1 init error");
        return 1;
    }

    if (uartInit(&uart2, init_2) != E_NOERR){
        printf("uart 2 init error");
        return 1;
    }

    uart1.functions->setBaudrate = setBaudrate_1;
    uart1.functions->setParity = setParity_1;
    uart1.functions->setStopBits = setStopBits_1;
    uart1.functions->uartEnable = enable_1;
    uart1.functions->uartGetByte = getByte_1;

    uart2.functions->setBaudrate = setBaudrate_2;
    uart2.functions->uartEnable = enable_2;
    uart2.functions->uartPutByte = putByte_2;

    { // tests
    uartSetBaudrate(&uart1, 9600);
    uartSetBaudrate(&uart2, 115200);
    uartSetParity(&uart1, PARITY_NONE);
    uartSetStopBits(&uart1, STOP_BITS_1);
    printf("uart1 new config baudrate= %d\n", uartGetBaudrate(&uart1));
    printf("uart2 new config baudrate= %d\n", uartGetBaudrate(&uart2));
    printf("uart1 new config parity= %d\n", uartGetParity(&uart1));
    printf("uart1 new config stopBits= %d\n", uartGetStopBits(&uart1));
    printf("uart1 rx state= %d\n", uartGetRxStatus(&uart1));
    printf("uart1 tx state= %d\n", uartGetTxStatus(&uart1));
    }

    uartSetReceiveCB(&uart1, callback); // setup user-defined receive callback function

    uartEnable(&uart1, STATE_RX_ENABLE, STATE_TX_DISABLE);
    uartEnable(&uart2, STATE_RX_DISABLE, STATE_TX_ENABLE);

    uint32_t testRcvCnt = 11;

    for(uint32_t i = testRcvCnt; i != 0 ; i--){
        uart1IRQ_Handler(); // uart1 touch to receive
    }

    uartDeinit(&uart1);
    uartDeinit(&uart2);
    
    printf("done");

    return 0;
}

void uart1IRQ_Handler(){
    if (1) { // rx interrupt flag check
        if (uartGetRxStatus(&uart1) != STATE_RX_BUSY){
            CBByteReceivedIT(&uart1);
        }
        // clear rx interrupt flag
    }
}

void uart2IRQ_Handler(){
    if (1) { // tx interrupt flag check
        CBTransmitterEmptyIT(&uart2);
        // clear tx interrupt flag
    }
}

