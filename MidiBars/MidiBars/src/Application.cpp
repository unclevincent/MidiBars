#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    } 

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW NOT OK" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -.5f, -.5f, 0.0f, 0.0f,
            .5f, -.5f, 1.0f, 0.0f, 
            .5f, .5f, 1.0f, 1.0f,
            -.5f, .5f, 0.0f, 1.0f
        };
        unsigned int indices[] = { 0,1,2,2,3,0 };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray vertexArray;
        VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout bufferLayout;
        bufferLayout.push<float>(2); // so many units of information 
        bufferLayout.push<float>(2);
        vertexArray.addBuffer(vertexBuffer, bufferLayout);

      
        IndexBuffer indexBuffer(indices, 6);

        Shader shader("res/shaders/basic.shader");
        shader.bind();
        shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/PNG_transparency_demonstration_1.png");
        texture.bind();
        shader.setUniform1i("u_Texture", 0);

        vertexArray.unbind();
        vertexBuffer.unbind();
        indexBuffer.unbind();
        shader.unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);



            renderer.draw(vertexArray, indexBuffer, shader);
            
            if (r > 1.0f) {
                increment = -0.05f;
            }
            else if (r < 0.0f) {
                increment = 0.05f;
            }
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
