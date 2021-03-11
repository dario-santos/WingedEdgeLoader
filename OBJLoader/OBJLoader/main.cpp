#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

#include "Mesh/Loader.hpp"

#include "Mesh/Mesh.hpp"


#include "Shader/GLSLProgram.hpp"

#include <iostream>


int main() 
{
  // Initialization of the GLFW
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4); //4xMSAA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Opengl 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Opengl 3.3
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Removes functionality deprecated opengl functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // sets the Opengl profile as core, added in 3.2

  // Creates the window
  vec2 dimensions = vec2(800, 600);
  GLFWwindow* window = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, "Winged-Edge Loader", NULL, NULL);

  // Create window context
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE; // Needed for core profile

  // Initialization of GLEW
  glewInit();

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Background Color

  //glClearColor(45.f/255, 52.f/255, 54.f/255, 0.0f);
  glClearColor(229.f / 255, 229.f / 255, 229.f / 255, 0.0f);

  // Enable depth test and blend
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Transfer VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);


  Loader* l = new Loader();
  Mesh* mesh = l->LoadOBJ("Cube.obj");
 
  glm::mat4 projection = glm::perspective(45.0f, 4/3.0f, 0.1f, 500.0f);
  glm::mat4 view = glm::lookAt(vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0));

  try
  {
    GLSLProgram* shader = new GLSLProgram();

    shader->compileShader("./GLSLShaders/OpaqueShader.vert");
    shader->compileShader("./GLSLShaders/OpaqueShader.frag");

    shader->link();
    shader->use();
  }
  catch (GLSLProgramException& e)
  {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }


  glfwSwapInterval(1);
  // render scene for each frame
  do
  {
    // Iterate Objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);







      // Uses shaderId as our shader
      GLuint shaderId = shader->getHandle();
      glUseProgram(shader->getHandle());

      // Gets the mvp position
      unsigned int m = glGetUniformLocation(shaderId, "model");
      // Passes the matrix to the shader
      glUniformMatrix4fv(m, 1, GL_FALSE, &model[0][0]);

      unsigned int v = glGetUniformLocation(shaderId, "view");
      // Passes the matrix to the shader
      glUniformMatrix4fv(v, 1, GL_FALSE, &view[0][0]);

      unsigned int p = glGetUniformLocation(shaderId, "projection");
      // Passes the matrix to the shader
      glUniformMatrix4fv(p, 1, GL_FALSE, &projection[0][0]);

      // be sure to activate shader when setting uniforms/drawing objects
      vec3 color = vec3(255.f, 0.0f, 0.0f) / vec3(255.f);
      glUniform3f(glGetUniformLocation(shaderId, "objectColor"), color.x, color.y, color.z);


      glEnableVertexAttribArray(0);

      mesh->Render();


      glDisableVertexAttribArray(0);
  







    // Swap buffers
    glfwSwapBuffers(window);

    // looking for events
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  /// Frees the vertex array
  glDeleteVertexArrays(1, &VertexArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}