#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

sem_t semaphore;

void* threadFunc(void* data) {
  while (1) {
    sem_wait(&semaphore);
    FILE* file = fopen("log.d", "a+");
    int value;
    sem_getvalue(&semaphore, &value);
    fprintf(file, "%s [%d]\n", "some message", value);
    fclose(file);
    sem_destroy(&semaphore);
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (key == 257) {
      sem_post(&semaphore);
      return;
    }
    printf("Key %d;\n", key);
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
  sem_init(&semaphore, 0, 0);
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
