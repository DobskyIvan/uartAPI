/*! \file
* \details Source file for lib.h
*/

#include <stdlib.h>
#include "..\inc\lib.h"

/*! \ingroup uart_api
* \brief Приватная структура конфигурации периферийного модуля*/
struct sUartApiConfig_{
    uint32_t baudrate; /*!< Текущее значение бодовой скорости */
    eParity parity; /*!< Текущее значение бита четности */
    eStopBits stopBits; /*!< Текущее значение количества стоп-битов */
    eErrorCode (*ReceiveCB) (uint8_t *receiveByte); /*!< Указатель функции обратного вызова (callback) для приема данных */
};

/*! \ingroup uart_api
* \brief Приватная структура состояний приемника и передатчика*/
struct sUartApiState_{
    eRxState rxState; /*!< Текущее состояние приемника */
    eTxState txState; /*!< Текущее состояние передатчика */
};

/*! \ingroup uart_api
* \brief Приватная структура хранения*/
struct sUartApiTemp_{
    uint8_t receivedByte; /*!< Последний принятый байт */
    uint8_t *txDataPointer; /*!< Указатель на массив данный на передачу */
    uint32_t txDataLength; /*!< Количество данных на передачу */
};

//private functions
static eErrorCode ReceiveCB_safe (uint8_t *receiveByte){ // функция- затычка если пользователь не установил ф-ию обратного вызова
    (void) *receiveByte;
    return E_COMMERR;
}

// public functions
eErrorCode uartInit(sUartApi *uartApi, eErrorCode (*init) (void)){
    //! \todo add init != NULL assert
    if (init == NULL) return E_INITERR;
    uartApi->config = malloc(sizeof(sUartApiConfig));
    uartApi->state = malloc(sizeof(sUartApiState));
    uartApi->temp = malloc(sizeof(sUartApiTemp));
    uartApi->functions = malloc(sizeof(sUartApiFunctions));
    // memory allocation error check:
    if ((uartApi->config == NULL) || (uartApi->state == NULL) ||
        (uartApi->temp == NULL) || (uartApi->functions == NULL)){ 
        if (uartApi->config != NULL) free(uartApi->config);
        if (uartApi->state != NULL) free(uartApi->state);
        if (uartApi->temp != NULL) free(uartApi->temp);
        if (uartApi->state != NULL) free(uartApi->functions);
        return E_INITERR;
    }
    init(); // calling a user-defined init function
    uartApi->config->ReceiveCB = ReceiveCB_safe;
    uartApi->state->rxState = STATE_RX_IDLE;
    uartApi->state->txState = STATE_TX_IDLE;
    uartApi->temp->txDataLength = 0;
    return E_NOERR;
}

eErrorCode uartDeinit(sUartApi *uartApi){
    free(uartApi->config);
    free(uartApi->state);
    free(uartApi->temp);
    free(uartApi->functions);
    return E_NOERR;
}

eErrorCode uartSetBaudrate(sUartApi *uartApi, uint32_t baudrate){
    //! \todo add assert max, min baudrate
    //! \todo add uartApi->functions->setBaudrate != NULL assert
    uartApi->functions->setBaudrate(baudrate); // calling a user-defined function
    uartApi->config->baudrate = baudrate; // update config
    return E_NOERR;
}

eErrorCode uartSetParity(sUartApi *uartApi, eParity parity){
    //! \todo add enum entry (parity) assert
    //! \todo add uartApi->functions->setParity != NULL assert
    uartApi->functions->setParity(parity); // calling a user-defined function
    uartApi->config->parity = parity; // update config
    return E_NOERR;
}

eErrorCode uartSetStopBits(sUartApi *uartApi, eStopBits stopBits){
    //! \todo add enum entry (stopBits) assert
    //! \todo add uartApi->functions->setStopBits != NULL assert
    uartApi->functions->setStopBits(stopBits); // calling a user-defined function
    uartApi->config->stopBits = stopBits; // update config
    return E_NOERR;
}

eErrorCode uartEnable (sUartApi *uartApi, eRxSwitch rxSwitch, eTxSwitch txSwitch){
    //! \todo add enum entry (rxSwitch, txSwitch) assert
    //! \todo add uartApi->functions->uartEnable != NULL assert
    uartApi->functions->uartEnable(rxSwitch, txSwitch);
    return E_NOERR;
}

uint32_t uartGetBaudrate(sUartApi *uartApi){
    return uartApi->config->baudrate;
}

eParity uartGetParity(sUartApi *uartApi){
    return uartApi->config->parity;
}

eStopBits uartGetStopBits(sUartApi *uartApi){
    return uartApi->config->stopBits;
}

eRxState uartGetRxStatus(sUartApi *uartApi){
    return uartApi->state->rxState;
}

eTxState uartGetTxStatus(sUartApi *uartApi){
    return uartApi->state->txState;
}

eErrorCode uartSetReceiveCB(sUartApi *uartApi, eErrorCode (*ReceiveCB) (uint8_t *receiveByte)){
    //! \todo add ReceiveCB != NULL assert
    if (ReceiveCB == NULL) return E_COMMERR;
    uartApi->config->ReceiveCB = ReceiveCB;
    return E_NOERR;
}

eErrorCode CBByteReceivedIT(sUartApi *uartApi){
    //! \todo add uartApi->functions->uartGetByte != NULL assert
    uartApi->state->rxState = STATE_RX_BUSY;
    uartApi->functions->uartGetByte(&uartApi->temp->receivedByte); 
    uartApi->config->ReceiveCB(&uartApi->temp->receivedByte);
    uartApi->state->rxState = STATE_RX_IDLE;
    return E_NOERR;
}

eErrorCode uartSend (sUartApi *uartApi, uint8_t *data, uint32_t dataLength){
    // потенциальный HardFault, нужно обеспечить защиту
    //! \todo add uartApi->functions->uartPutByte != NULL assert
    if (uartApi->temp->txDataLength > 0){
        return E_COMMERR; // already transmitting
    }

    uartApi->temp->txDataPointer = data;
    uartApi->temp->txDataLength = dataLength;

    uartApi->state->txState = STATE_TX_BUSY;
    uartApi->temp->txDataLength--;
    uartApi->functions->uartPutByte(*data); // this will call tx interrupt (CBTransmitterEmptyIT())
    
    return E_NOERR;
}

eErrorCode CBTransmitterEmptyIT(sUartApi *uartApi){
    //! \todo add uartApi->functions->uartPutByte != NULL assert
    if (uartApi->temp->txDataLength != 0){
        uartApi->temp->txDataLength--;
        uartApi->temp->txDataPointer++;
        uartApi->functions->uartPutByte(*uartApi->temp->txDataPointer);
    }
    else{
        uartApi->state->txState = STATE_TX_IDLE;
    }

    return E_NOERR;
}
