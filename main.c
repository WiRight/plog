#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <GLFW/glfw3.h>

sem_t semaphore;

void* threadFunc(void* data) {
  // FILE* file = fopen("log.d", "a+");
  // fclose(file);
  printf("%s\n", "threadFunc end");
  // while (1) {
    // sem_wait(&semaphore);
    int value;
    sem_getvalue(&semaphore, &value);
    printf("%s %d\n", "Data", value);
    // sem_post(&semaphore);
  // }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == 257) {
    sem_destroy(&semaphore);
    int value;
    sem_getvalue(&semaphore, &value);
    printf("%s %d\n", "key_callback Enter Data", value);
    return;
  }
  if (action == GLFW_PRESS) {
    printf("Key %d;\n", key);
    sem_wait(&semaphore);
    int value;
    sem_getvalue(&semaphore, &value);
    printf("%s %d\n", "key_callback Data", value);
    sem_post(&semaphore);
    // sem_post(&semaphore);
  }
}

int main() {
  GLFWwindow* window;
  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }
  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  pthread_t thread;
  sem_init(&semaphore, 0, 2);
  pthread_create(&thread, NULL, threadFunc, NULL);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
  }
  glfwTerminate();
  sem_destroy(&semaphore);
  return 0;
}
