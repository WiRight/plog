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

#define TIME_L 80
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
 * @since 1.0
 */
static sem_t semaphore;

/**
 * Структура данных сообщения
 * @since 1.0
 */
typedef struct PLogMsg {
    char* logType;
    char* fileName;
    char* functionName;
    char* message;
    int line;
} PLogMsg;

/**
 * Переменная для работы с сообщением лога
 * @since 1.0
 */
static PLogMsg pLogMsg;

/**
 * Переменная для работы с потоком
 * @since 1.0
 */
static pthread_t logThread;

/**
 * Переменная для обозначения корректного выхода потока
 * @since 1.0
 */
static unsigned short int pExit;

/**
 * Форматирование времени
 * @since 1.0
 */
char* ptimeFormat;

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
 * @since 1.0
 */
char* plogFormat;

// ------------------------------------------------------

/**
 * Инициализация модуля логирования
 * @since 1.0
 */
void plogInit();

/**
 * Функция, которая будет в фоне работать с логами
 * @param params Некоторые параметры для функции потока
 * @since 1.0
 */
static void* threadFunc(void *);

/**
 * Фукнция для записи данных в файл
 * На данные момент запись производится только в файл log.d
 * TODO: стоит добавить кастомизацию, куда писать логи
 * TODO: стоит писать каждый день в новый файл (для уникальности)
 * @since 1.0
 */
static inline void writeFile(char *);

/**
 * Получение текущего времени в формате [ptimeFormat]
 * @return Формированное время
 * @since 1.0
 */
static inline char* getFormatTime();

/**
 * Закрытие работы с модулем логирования
 * @since 1.0
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
 * @since 1.0
 */
void plogLog(char *, char *, const char *, int, char *);

// ------------------------------------------------------

#endif // _P_LOG_H_
