/*! \file lib.h*/

#ifndef LIB_H
#define LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*! \defgroup uart_api UART_API
* \details
* \ref id1
*/

/*! \ingroup uart_api
* \brief Статус приемника
* \see uartGetRxStatus()*/
typedef enum{
    STATE_RX_IDLE, /*!< Приемник свободен */
    STATE_RX_ERROR, /*!< Ошибка приема */
    STATE_RX_BUSY /*!< Приемник занят */
} eRxState;

/*! \ingroup uart_api
* \brief Включение\выключение приемника
* \see uartEnable()*/
typedef enum{
    STATE_RX_DISABLE, /*!< Приемник выключен */
    STATE_RX_ENABLE /*!< Приемник включен */
}eRxSwitch;

/*! \ingroup uart_api
* \brief Статус передатчика
* \see uartGetTxStatus()*/
typedef enum{
    STATE_TX_IDLE, /*!< Передатчик свободен */
    STATE_TX_ERROR, /*!< Ошибка передачи */
    STATE_TX_BUSY /*!< Передатчик занят */
} eTxState;

/*! \ingroup uart_api
* \brief Включение\выключение передатчика
* \see uartEnable()*/
typedef enum{
    STATE_TX_DISABLE, /*!< Передатчик выключен */
    STATE_TX_ENABLE /*!< Передатчик включен */
}eTxSwitch;

/*! \ingroup uart_api
* \brief Коды ошибок*/
typedef enum{
    E_NOERR, /*!< Ол райт */
    E_INITERR, /*!< Ошибка инициализации */
    E_COMMERR /*!< Общая ошибка */
} eErrorCode;

/*! \ingroup uart_api
* \brief Бит четности
* \see uartSetParity(), uartGetParity()*/
typedef enum{
    PARITY_NONE, /*!< Бит четности отсутствует */
    PARITY_ODD, /*!< Бит четности нечетный */
    PARITY_EVEN /*!< Бит четности четный */
} eParity;

/*! \ingroup uart_api
* \brief Количество стоп-битов
* \see uartSetStopBits(), uartGetStopBits()*/
typedef enum{
    STOP_BITS_0_5, /*!< 0,5 */
    STOP_BITS_1, /*!< 1 */
    STOP_BITS_1_5, /*!< 1,5 */
    STOP_BITS_2 /*!< 2 */
} eStopBits;

struct sUartApiConfig_;
typedef struct sUartApiConfig_ sUartApiConfig;

struct sUartApiState_;
typedef struct sUartApiState_ sUartApiState;

struct sUartApiTemp_;
typedef struct sUartApiTemp_ sUartApiTemp;

/*! \ingroup uart_api
* \brief Указатели на platform-specific функции
* \note Пример передачи указателя: \code sUartApiFunctions->setBaudrate = foo; \endcode*/
typedef struct{
    eErrorCode (*setBaudrate) (uint32_t); /*!< Установка бодовой скорости */
    eErrorCode (*setParity) (eParity); /*!< Установка бита четности */
    eErrorCode (*setStopBits) (eStopBits); /*!< Установка количества стоп-битов */
    eErrorCode (*uartEnable) (eRxSwitch, eTxSwitch); /*!< Включение\выключение прерываний приемника\передатчика */
    eErrorCode (*uartPutByte) (uint8_t); /*!< Отправка байта данных */
    eErrorCode (*uartGetByte) (uint8_t *); /*!< Получение байта данных */
}sUartApiFunctions;

/*! \ingroup uart_api
* \brief Интерфейсы объекта API
* \note Пример объявления: \code sUartApi uart1 \endcode*/
typedef struct{
    sUartApiConfig *config; /*!< Приватная структура конфигурации периферийного блока */
    sUartApiState *state; /*!< Приватная структура состояний приемника и передатчика */
    sUartApiTemp *temp; /*!< Приватная структура хранения  */
    sUartApiFunctions *functions; /*!< Указатели на platform-specific функции  */
}sUartApi;

/*! \ingroup uart_api
* \brief Функция инициализации объекта API
* \note Эта функция выделяет память.
* Для завершения работы интерфейса необходимо вызывать uartDeinit(),
* для ее освобождения\n
* Пример вызова: \code 
* sUartApi uart1;
* eErrorCode bar (void){
*   //do some platform-specific stuff
*   return E_NOERR;
* }
* uartInit(&uart1, &bar);
* // do something usefull
* uartDeinit(&uart1);
* \endcode
* \param uartApi Указатель на объект API
* \param init Указатель на platform-specific функцию инициализации периферийного блока
* \return E_INITERR- если не удалось выделить память для объекта API\n
* E_NOERR- если выполнена успешно
*/
eErrorCode uartInit(sUartApi *uartApi, eErrorCode (*init) (void));

/*! \ingroup uart_api
* \brief Функция деинициализации объекта API
* \param uartApi Указатель на объект API
* \return E_NOERR- если выполнена успешно
*/
eErrorCode uartDeinit(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция установки бодовой скорости
* \param uartApi Указатель на объект API
* \param baudrate Значение бодовой скорости
* \return E_NOERR- если выполнена успешно
*/
eErrorCode uartSetBaudrate(sUartApi *uartApi, uint32_t baudrate);

/*! \ingroup uart_api
* \brief Функция установки бита четности
* \param uartApi Указатель на объект API
* \param parity Значение бита четности
* \return E_NOERR- если выполнена успешно
*/
eErrorCode uartSetParity(sUartApi *uartApi, eParity parity);

/*! \ingroup uart_api
* \brief Функция установки количества стоп-битов
* \param uartApi Указатель на объект API
* \param stopBits Значение количества стоп-битов
* \return E_NOERR- если выполнена успешно
*/
eErrorCode uartSetStopBits(sUartApi *uartApi, eStopBits stopBits);

/*! \ingroup uart_api
* \brief Функция включение\выключение прерываний приемника\передатчика
* \param uartApi Указатель на объект API
* \param rxSwitch Включение\выключение приемника 
* \param txSwitch Включение\выключение передатчика
* \return E_NOERR- если выполнена успешно
*/
eErrorCode uartEnable (sUartApi *uartApi, eRxSwitch rxSwitch, eTxSwitch txSwitch);

/*! \ingroup uart_api
* \brief Функция получения бодовой скорости
* \param uartApi Указатель на объект API
* \return Значение бодовой скорости
*/
uint32_t uartGetBaudrate(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция получения бита четности
* \param uartApi Указатель на объект API
* \return Значение бита четности
*/
eParity uartGetParity(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция получения количества стоп-битов
* \param uartApi Указатель на объект API
* \return Значение количества стоп-битов
*/
eStopBits uartGetStopBits(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция получения статуса приемника
* \param uartApi Указатель на объект API
* \return Значение статуса приемника
*/
eRxState uartGetRxStatus(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция получения статуса передатчика
* \param uartApi Указатель на объект API
* \return Значение статуса передатчика
*/
eTxState uartGetTxStatus(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция установки функции обратного вызова (callback) для приема данных
* \param uartApi Указатель на объект API
* \param ReceiveCB Указатель на функцию обратного вызова
* \return E_COMMERR- если передаваемый указатель NULL\n
* E_NOERR- если выполнена успешно
*/
eErrorCode uartSetReceiveCB(sUartApi *uartApi, eErrorCode (*ReceiveCB) (uint8_t *receiveByte));


/*! \ingroup uart_api
* \brief Функция обработчика прерывания приемника
* \param uartApi Указатель на объект API
* \return E_NOERR- если выполнена успешно
*/
eErrorCode CBByteReceivedIT(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция обработчика прерывания передатчика
* \param uartApi Указатель на объект API
* \return E_NOERR- если выполнена успешно
*/
eErrorCode CBTransmitterEmptyIT(sUartApi *uartApi);

/*! \ingroup uart_api
* \brief Функция передачи массива данных
* \param uartApi Указатель на объект API
* \param data Указатель на массив данный на передачу
* \param dataLength Количество данных на передачу
* \return E_COMMERR- если передатчик занят
* E_NOERR- если выполнена успешно
*/
eErrorCode uartSend (sUartApi *uartApi, uint8_t *data, uint32_t dataLength);

# ifdef __cplusplus
}
# endif

#endif // LIB_H