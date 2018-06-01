#ifndef _P_LOG_H_
#define _P_LOG_H_

// ------------------------------------------------------

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

// ------------------------------------------------------

#define PLOG_ASSERT "assert"
#define PLOG_INFO "info"
#define PLOG_WARNING "warning"
#define PLOG_DEBUG "debug"

#define assertLog(message) \
  plogLog(PLOG_ASSERT, __FILE__, __FUNCTION__, __LINE__, message);

#define infoLog(message) \
  plogLog(PLOG_INFO, __FILE__, __FUNCTION__, __LINE__, message);

#define warningLog(message) \
  plogLog(PLOG_WARNING, __FILE__, __FUNCTION__, __LINE__, message);

#define debugLog(message) \
  plogLog(PLOG_DEBUG, __FILE__, __FUNCTION__, __LINE__, message);

// ------------------------------------------------------

/**
 * Семафор для работы с потоком
 */
static sem_t semaphore;

/**
 * Структура данных сообщения
 */
typedef struct PLogMsg {
    char *logType;
    char *fileName;
    char *functionName;
    char *message;
    int line;
} PLogMsg;

/**
 * Переменная для работы с сообщением лога
 */
static PLogMsg pLogMsg;

/**
 * Переменная для работы с потоком
 */
static pthread_t logThread;

/**
 * Переменная для обозначения корректного выхода потока
 */
static unsigned short int pExit;

/**
 * Форматирование времени
 */
char *ptimeFormat;

/**
 * Форматирование лога
 * ------------------------------
 * Список параметров
 *
 * 1 - Текущая дата/время
 * 2 - Тип сообщения
 * 3 - Имя файла
 * 4 - Имя функции
 * 5 - Линия, где был вызван лог
 * 6 - Сообщение пользователя
 * ------------------------------
 */
char *plogFormat;

// ------------------------------------------------------

/**
 * Инициализация модуля логирования
 */
void plogInit();

/**
 * Функция, которая будет в фоне работать с логами
 * @param params Некоторые параметры для функции потока
 * @return
 */
static void *threadFunc(void *);

/**
 * Закрытие работы с модулем логирования
 */
void plogDestroy();

/**
 * Отправляет сообщение в поток для дальнейшей записи
 * @note Не использовать на прямую!
 * @param logType Тип сообщения
 * @param fileName Имя файла
 * @param functionName Имя функции
 * @param line Лииния, где вызвался лог
 * @param message Сообщение пользователя
 */
void plogLog(char *, char *, const char *, int, char *);

// ------------------------------------------------------

#endif // _P_LOG_H_
