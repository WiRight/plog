#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/**
 * Семафор для работы с потоком
 */
static sem_t semaphore;

/**
 * Переменная для хранения текущего сообщения
 * TODO: возможно понадобится сделать массив значений (vector | stack)
 */
static char* msg;

/**
 * Переменная для работы с потоком 
 */
static pthread_t logThread;

// ------------------------------------------------------

/**
 * Инициализация модуля логирования
 */
void plogInit();

/**
 * Функция, которая будет в фоне работать с логами
 */
static void* threadFunc();

/**
 * Закрытие работы с модулем логирования
 */
void plogDestroy();

// ------------------------------------------------------

void plogLog(char* message);
