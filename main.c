#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <GLFW/glfw3.h>

void* threadFunc(void* data) {
  FILE* file = fopen("log.d", "a+");
  fclose(file);
  printf("%s\n", "threadFunc");
  sleep(1);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    printf("Key %d; Action %d;\n", key, action);
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
  return 0;
}
