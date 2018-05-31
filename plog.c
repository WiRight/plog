#include "plog.h"

// Инициализация модуля
void plogInit() {
  sem_init(&semaphore, 0, 0);
  int start = 30;
  pthread_create(&logThread, NULL, threadFunc, &start);
  // pthread_detach(&logThread); // TODO: тщательно протестировать
}

// Уничтожение модуля
void plogDestroy() {
  pthread_cancel(logThread);
  sem_destroy(&semaphore);
}

// Основная бизнес-логика
static void* threadFunc(void* params) {
  // int start = *((int*)params);
  // printf("[threadFunc] start with %d\n", start);
  while (1) {
    printf("[threadFunc] - %s\n", msg);
    sem_wait(&semaphore);
    printf("[threadFunc] - %s -- semaphore\n", msg);
    int value;
    sem_getvalue(&semaphore, &value);
    FILE* file = fopen("log.d", "a+");
    fprintf(file, "%s [%d]\n", msg, value);
    msg = NULL;
    fclose(file);
    pthread_testcancel();
  }
  pthread_exit(0);
}

// TODO: думать
void plogLog(char* message) {
  printf("[plogLog] try send %s\n", message);
  msg = message;
  sem_post(&semaphore);
}
