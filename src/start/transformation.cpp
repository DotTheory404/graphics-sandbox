#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void processInput(GLFWwindow* window);

const int SRC_Width = 1000;
const int SRC_Height = 800;

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SRC_Width,SRC_Height, "transformation", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail create window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		std::cout << "Faild init Glad.\n";
		return -1;
	}

	Shader ourShader("shaders/shader.vs", "shaders/shader.fs");

	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 -0.7f,  -0.3f, 0.0f,   1.0f, 0.0f, 0.0f,    // top right
	//	 0.0f, 0.7f, 0.0f,   0.0f, 1.0f, 0.0f,    // bottom right
	//	0.7f, -0.3f, 0.0f,   0.0f, 0.0f, 1.0f,    // bottom left
 //    // top left 
	//};

	float vertices[] = {

		0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 
		-0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	ourShader.use();


	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 transform = glm::mat4(1.0f);
		float timeCount = glfwGetTime() * 0.5f;

		transform = glm::translate(transform, glm::vec3(0.6f, -0.4f, 0.0));
		transform = glm::rotate(transform, sin(timeCount), glm::vec3(0.0f, 0.0f, 1.0f));
		float scaleRestriction = 1.0f + sin(timeCount) * 0.2f;
		//transform = glm::scale(transform, glm::vec3(sin(timeCount), sin(timeCount), sin(timeCount)));
		transform = glm::scale(transform, glm::vec3(scaleRestriction, scaleRestriction, scaleRestriction));
		
		//transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// second transformation
		// ---------------------
		transform = glm::mat4(1.0f); 
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = static_cast<float>(sin(glfwGetTime()) * 0.2);
		transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}