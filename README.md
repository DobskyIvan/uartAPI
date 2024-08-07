# UART LIBRARY WITH A PUBLIC API

## [Документация](/lib/doc/html/index.html "\lib\doc\html\index.html")

## Описание {#id1}
``` #include lib.h ```  
Этот модуль определяет интерфейс приложения. Он содержит базовые функции, структуры и типы.  
Типичное приложение состоит из:  
1. Определения объекта интерфейса при помощи структуры sUartApi;  

2. Инициализации при помощи uartInit() (**Важный момент, эта функция выделяет память.
Для завершения работы интерфейса необходимо вызывать uartDeinit(),
для ее освобождения**);  

3. Передачи в эту структуру указателей на platform-specific функции;  

4. Установку необходимых параметров периферии (baudrate, parity, stopbits) 
при помощи функций uartSetBaudrate(), uartSetParity(), uartSetStopBits().
(Получить текущие значения параметров можно с помощью uartGetBaudrate(),
uartGetParity(), uartGetStopBits());  

5. Установку функции обратного вызова (callback) для приема данных, с помощью
uartSetReceiveCB();  

6. Разрешения прерываний с помощью uartEnable(), в обработчике прерываний,
соответствующего периферийного блока необходимо вызывать функции CBByteReceivedIT()
и CBTransmitterEmptyIT().  

7. Передача массива данных осуществляется функцией uartSend()
  
## Пример использования

Создаем объект интерфейса:  
```c 
sUartApi uart1; 
```  

Создаем platform-specific функцию инициализации периферии и передаем ее указатель в uartInit():  
```c 
eErrorCode uart1_init (void){
  //do some platform-specific stuff
  return E_NOERR;
}

uartInit(&uart1, uart1_init);
```  

Далее необходимо заполнить поле структуры sUartApi "functions" передав все необходимые указатели на platform-specific функций. Например для stm32f103r6 функция передачи байта данных:  

```c

#include "stm32f103x6.h"

eErrorCode uart1_putByte (uint8_t byteToSend){
    USART1->DR = byteToSend;
    return E_NOERR;
}

uart1.functions->uartPutByte = uart1_putByte;
```  

Для корректной работы, необходимо в обработчике прерываний модуля вызывать соответствующие библиотечные функции CBTransmitterEmptyIT() и CBByteReceivedIT().  
Например для stm32f103r6:

```c

#include "stm32f103x6.h"

void USART1_IRQHandler(void){
    if((USART1->SR&USART_SR_TXE)){ // "Transmit Data Register Empty"
        CBTransmitterEmptyIT(&uart1);
        USART1->SR&=~USART_SR_TXE; // clear the pending TXE flag
    }

    if((USART1->SR&USART_SR_RXNE)){ // "Read Data Register Not Empty"
        CBByteReceivedIT(&uart1);
        USART1->SR&=~USART_SR_RXNE; // clear the pending RXNE flag
    }
}
```

Опционально, установить функцию обратного вызова, например:  

```c
eErrorCode my_callback (uint8_t *receivedByte){
    printf("callback echo from uart 1, byte received: 0x%x\n", *receivedByte);
    return E_NOERR;
}

uartSetReceiveCB(&uart1, my_callback);
```

Задать режим работы UART, например, что бы разрешить прерывания только на передачу:  

```c
uartEnable(&uart1, STATE_RX_DISABLE, STATE_TX_ENABLE);
```

Пример передачи данных:  
```c
uint8_t dataToSend[14] = "hello, world!";

if (uartGetTxStatus(&uart1) != STATE_TX_BUSY){
    uartSend(&uart1, dataToSend, 14);
}
```

По окончании использования интерфейса необходимо произвести его деинициализацию:

```c
uartDeinit(&uart1);
```