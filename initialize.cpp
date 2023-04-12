#include "initialize.h"
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Helper_classes.h"


void WindowSizeRecall(GLFWwindow* window , vec2<int> menu_size)
{
	int height = NULL, width = NULL;
	glfwGetWindowSize(window, &width, &height);
	//glViewport(menu_size.x,NULL , width, height);
    //glViewport(NULL, NULL, width, height);
    glViewport(NULL, NULL, menu_size.x, menu_size.y);
}

GLFWwindow* initializeWindow(int windowwidth , int windowheight , const char*windowname)
{

	if (!glfwInit())
	{
		std::cerr << "Error initializing glfw" << std::endl;
	
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glEnable(GL_MULTISAMPLE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);
    if (!window) {

        std::cerr << "Failed to create window with opengl context version: 4.6" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

        if (window) {

            std::cerr << "Failed to create window with opengl context version: 4.5" << std::endl;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

            if (!window) {

                std::cerr << "Failed to create window with opengl context version: 4.4" << std::endl;

                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

                if (!window) {

                    std::cerr << "Failed to create window with opengl context version: 4.3" << std::endl;

                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                    GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

                    if (!window) {

                        std::cerr << "Failed to create window with opengl context version: 4.2" << std::endl;

                        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                        GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

                        if (!window) {

                            std::cerr << "Failed to create window with opengl context version: 4.1" << std::endl;

                            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                            GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);


                            if (!window) {

                                std::cerr << "Failed to create window with opengl context version: 4.0" << std::endl;

                                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                                GLFWwindow* window = glfwCreateWindow(windowwidth, windowheight, windowname, NULL, NULL);

                                if (!window) {

                                    std::cerr << "Failed to create window" << std::endl;
                                    glfwTerminate();
                                    exit(-1);
                                    
                                }
                            }

                        }

                    }

                }

            }

        }

    }

	
	if (window == NULL)
	{

		std::cerr << "Error Creating a window" << std::endl;
		glfwTerminate();
		

	}
	

	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
	{

		std::cerr << "Error::initializing glew" << "\n";
		glfwTerminate();
		

	}

	return window;

}

void DeinitializeWindow()
{
	glfwTerminate();
}









