#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "minbe_api.h"


GLuint m_pro;
GLuint m_vao;

int Prepare();

int Draw();

int Destroy();

static void key_callback(GLFWwindow *window, int key, int scancode,
                         int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, 800, 600);

    Prepare();


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Destroy();

    glfwTerminate();

    return 0;
}

int Prepare() {
  minbe_init();
  minbe_load("./mesh11_61818.gltf");
    return 0;
}


int Draw() {
  minbe_render();
  return 0;
}

int Destroy() {
  minbe_destroy();
  return 0;
}
