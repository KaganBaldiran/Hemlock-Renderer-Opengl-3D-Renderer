#include "Camera.h"
#include "Helper_classes.h"
#include "Texture.h"

Camera::Camera(int window_width, int window_height, glm::vec3 position)
{
	w_width = window_width;
	w_height = window_height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane , GLFWwindow* window, vec2<int> menu_size)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);

	this->cam_view = view;

	int height = NULL, width = NULL;
	glfwGetWindowSize(window, &width, &height);

	//std::cout <<"IN CAMERA: " << "WINSIZE.X: " << width - menu_size.x << "WINSIZE.Y: " << menu_size.y << "\n";

	//float aspect_rat = (float)(width - menu_size.x) / (float)menu_size.y;
	float aspect_rat = (float)(w_width/w_height);
	//float aspect_rat = (float)((1000 - 175.438) / (1000 - 18));

	//std::cout << "ASPECT RATIO: "<< aspect_rat << "\n";


	proj = glm::perspective(glm::radians(FOVdeg),aspect_rat , nearPlane, farPlane);

	this->projection = proj;
	//proj = glm::ortho(0, w_width, w_height, 0, 0, 100);

	glm::mat4 screenratiodefault = glm::mat4(1.0f);

	screenratiodefault = glm::scale(screenratiodefault, glm::vec3(GetScreenRatio(window,menu_size).x, GetScreenRatio(window,menu_size).y, 1.0f));

	cammatrix = screenratiodefault * proj * view;
}

void Camera::Matrix(GLuint shaderprogram, const char* uniform)
{
	
	glUniformMatrix4fv(glGetUniformLocation(shaderprogram, uniform), 1, GL_FALSE, glm::value_ptr(cammatrix));

}

void Camera::HandleInputs(GLFWwindow* window, vec2<int> menu_size)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		Position += speed * Orientation;

	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{

		Position += speed * -glm::normalize(glm::cross(Orientation,Up));

	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		Position += speed * -Orientation;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

		Position += speed * glm::normalize(glm::cross(Orientation, Up));;

	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

		Position += speed * Up;

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{

		Position += speed * -Up;

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{

		speed = 0.07f;

	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{

		speed = 0.03f;

	}


	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS))
	{
		int height = NULL, width = NULL;
		glfwGetWindowSize(window, &width, &height);

		//w_width = width - menu_size.x;
		//w_height = menu_size.y;
		//w_width = 1000 - 175.438;
		//w_height = 1000 - 18;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstclick)
		{
			glfwSetCursorPos(window, (w_width / 2), (w_height / 2));
			firstclick = false;
		}

		vec2<double> mousepos;

		glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

		vec2<float> rot;

		rot.x = sensitivity * (float)(mousepos.y - (w_height / 2)) / w_height;
		rot.y = sensitivity * (float)(mousepos.x - (w_width / 2)) / w_width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rot.x), glm::normalize(glm::cross(Orientation, Up)));

		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{

			Orientation = newOrientation;

		}

		Orientation = glm::rotate(Orientation, glm::radians(-rot.y), Up);

		//int height = NULL, width = NULL;
		//glfwGetWindowSize(window, &width, &height);

		glfwSetCursorPos(window, (w_width / 2), (w_height / 2));
	}

	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE )
	{

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		firstclick = true;

	}



}


