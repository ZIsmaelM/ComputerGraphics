#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <iostream>
#include "stb_image.h"

#include <algorithm>

////////////////////////////////////////
// Globals
////////////////////////////////////////
float textureMix = 0.5f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
float NEAR_PLANE = 0.1f;
float FAR_PLANE = 100.0f;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f); 
Camera camera = Camera();

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPosition, double yPosition)
{
	camera.updateView(xPosition, yPosition);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.updateZoom(yOffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		textureMix += 0.01f;
		textureMix = std::min(textureMix, 1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		textureMix -= 0.01f;
		textureMix = std::max(textureMix, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		camera.resetToStartPosition();
	}

	// camera movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(RIGHT, deltaTime);
}

void setupBuffers(unsigned int* VBO, unsigned int* objectVAO, unsigned int* EBO, unsigned int* lightVAO)
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glGenVertexArrays(1, objectVAO);
	glBindVertexArray(*objectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, lightVAO);
	glBindVertexArray(*lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void setupTextures(unsigned int* textureID, const char* path)
{
	glGenTextures(1, textureID);
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, *textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void updateModelMatrix(glm::mat4 model, Shader shader)
{
	unsigned int modelMatrixLocation = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void updateViewMatrix(glm::mat4& view, Shader shader)
{
	unsigned int viewMatrixLocation = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void updateProjectionMatrix(glm::mat4& projection, Shader shader)
{
	unsigned int projectionMatrixLocation = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO, objectVAO, EBO, lightVAO;
	setupBuffers(&VBO, &objectVAO, &EBO, &lightVAO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	const char* objectVSPath = "O:/GraphicsProgramming/LearningOpenGL/LearningOpenGLSolution/LearningOpenGLProject/objectVS.glsl";
	const char* objectFSPath = "O:/GraphicsProgramming/LearningOpenGL/LearningOpenGLSolution/LearningOpenGLProject/objectFS.glsl";
	Shader objectShader(objectVSPath, objectFSPath);
	unsigned int texture1, texture2;
	//setupTextures(&texture1, &texture2);

	const char* lightVSPath = "O:/GraphicsProgramming/LearningOpenGL/LearningOpenGLSolution/LearningOpenGLProject/lightVS.glsl";
	const char* lightFSPath = "O:/GraphicsProgramming/LearningOpenGL/LearningOpenGLSolution/LearningOpenGLProject/lightFS.glsl";
	Shader lightShader(lightVSPath, lightFSPath);

	unsigned int crateTexture;
	const char* crateTextPath = "textures/crate.png";
	setupTextures(&crateTexture, crateTextPath);
	unsigned int crateSpectral;
	const char* crateSpecPath = "textures/crate_specular.png";
	setupTextures(&crateSpectral, crateSpecPath);
	unsigned int crateEmission;
	const char* crateEmitPath = "textures/crate_emission.jpg";
	setupTextures(&crateEmission, crateEmitPath);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crateTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, crateSpectral);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, crateEmission);
	////////////////////////////////////////
	// render loop
	////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/*
		lightPos.x = 2.0f * sin(glfwGetTime()/100); // 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = 0.45f;
		lightPos.z = 1.5f * cos(glfwGetTime()/100); // sin(glfwGetTime() / 2.0f) * 1.0f;
		*/

		objectShader.use();
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getView();
		updateViewMatrix(view, objectShader);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(camera.getZoom(), ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
		updateProjectionMatrix(projection, objectShader);		
		glm::mat4 model = glm::mat4(1.0f);
		updateModelMatrix(model, objectShader);

		objectShader.setVec3("lightPos", lightPos);
		objectShader.setVec3("viewPos", camera.getPosition());

		objectShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		objectShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		objectShader.setFloat("light.constant", 1.0f);
		objectShader.setFloat("light.linear", 0.09f);
		objectShader.setFloat("light.quadratic", 0.032f);
		
		objectShader.setInt("material.diffuse", 0);
		objectShader.setInt("material.specular", 1);
		objectShader.setInt("material.emission", 2);
		objectShader.setFloat("material.shininess", 32.0f);
		
		//objectShader.setMat4("model", model);
		objectShader.setMat4("view", view);
		objectShader.setMat4("projection", projection);
		glBindVertexArray(objectVAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objectShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		
		lightShader.setVec3("lampColor", 1.0f, 1.0f, 1.0f);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &objectVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}