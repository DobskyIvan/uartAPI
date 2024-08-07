
#include "test_stuff.h"
#include <stdlib.h>

eErrorCode init_1 (void){
    // do some platform-specific stuff
    printf("callback from uart 1 init()\n");
    srand(1792); // seed to rand()
    return E_NOERR;
}

eErrorCode init_2 (void){
    // do some platform-specific stuff
    printf("callback from uart 2 init()\n");
    return E_NOERR;
}

eErrorCode deinit_1 (void){
        // do some platform-specific stuff
    printf("callback from uart 1 denit()\n");
    return E_NOERR;
}

eErrorCode deinit_2 (void){
        // do some platform-specific stuff
    printf("callback from uart 2 denit()\n");
    return E_NOERR;
}

eErrorCode setBaudrate_1 (uint32_t baudrate){
    // do some platform-specific stuff
    (void) baudrate;
    printf("callback from uart 1 setBaudrate(%d)\n", baudrate);
    return E_NOERR;
}

eErrorCode setBaudrate_2 (uint32_t baudrate){
    // do some platform-specific stuff
    (void) baudrate;
    printf("callback from uart 2 setBaudrate(%d)\n", baudrate);
    return E_NOERR;
}

eErrorCode setParity_1 (eParity eParity){
    // do some platform-specific stuff
    (void) eParity;
    printf("callback from uart 1 setParity(%d)\n", eParity);
    return E_NOERR;
}

eErrorCode setStopBits_1 (eStopBits eStopBits){
    // do some platform-specific stuff
    (void) eStopBits;
    printf("callback from uart 1 setStopBits(%d)\n", eStopBits);
    return E_NOERR;
}

eErrorCode enable_1 (eRxSwitch rxSwitch, eTxSwitch txSwitch){
    // do some platform-specific stuff
    printf("callback from uart 1 Enable(%d, %d)\n", rxSwitch, txSwitch);
    switch (rxSwitch){
    case STATE_RX_ENABLE:
        // platform-specific enable rx interrupt
        printf("uart 1 rx- enable\n");
        break;
    case STATE_RX_DISABLE:
        // platform-specific enable rx interrupt
        printf("uart 1 rx- disable\n");
        break;
    
    default:
        return E_COMMERR;
        break;
    }

    switch (txSwitch){
    case STATE_TX_ENABLE:
        // platform-specific enable tx interrupt
        printf("uart 1 tx- enable\n");
        break;
    case STATE_TX_DISABLE:
        // platform-specifi disable tx interrupt
        printf("uart 1 tx- disable\n");
        break;
    
    default:
        return E_COMMERR;
        break;
    }
    return E_NOERR;
}

eErrorCode enable_2 (eRxSwitch rxSwitch, eTxSwitch txSwitch){
    // do some platform-specific stuff
    printf("callback from uart 2 Enable(%d, %d)\n", rxSwitch, txSwitch);
    switch (rxSwitch){
    case STATE_RX_ENABLE:
        // platform-specific enable rx interrupt
        printf("uart 2 rx- enable\n");
        break;
    case STATE_RX_DISABLE:
        // platform-specific enable rx interrupt
        printf("uart 2 rx- disable\n");
        break;
    
    default:
        return E_COMMERR;
        break;
    }

    switch (txSwitch){
    case STATE_TX_ENABLE:
        // platform-specific enable tx interrupt
        printf("uart 2 tx- enable\n");
        break;
    case STATE_TX_DISABLE:
        // platform-specifi disable tx interrupt
        printf("uart 2 tx- disable\n");
        break;
    
    default:
        return E_COMMERR;
        break;
    }
    return E_NOERR;
}

eErrorCode putByte_2 (uint8_t byteToSend){
    // do some platform-specific stuff
    printf("callback from uart 2, byte send: 0x%x\n", byteToSend);
    uart2IRQ_Handler(); // recursion
    return E_NOERR;
}

eErrorCode getByte_1 (uint8_t *receiveByte){
    // do some platform-specific stuff
    *receiveByte = (uint8_t)rand();
    return E_NOERR;
}
