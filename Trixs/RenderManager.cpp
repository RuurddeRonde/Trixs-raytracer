#include "RenderManager.h"
#include "MainManager.h"
#include "Scene.h"
#include <iostream>


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace Trixs
{
	//todo move to input manager
	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	RenderManager::RenderManager(Window* basewindow)
	{
		this->basewindow = basewindow;
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------	

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		basewindow->setSize(mode->width, mode->height);

		basewindow->setWindow(glfwCreateWindow(basewindow->getWidth(), basewindow->getHeight(), "Trixs", NULL, NULL));

		if (basewindow->getWindow() == NULL)
		{
			//std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(basewindow->getWindow());
		auto Resizefunc = [](GLFWwindow* w, int width, int height)
		{
			static_cast<RenderManager*>(glfwGetWindowUserPointer(w))->framebufferSizeCallback(width, height);
		};
		glfwSetFramebufferSizeCallback(basewindow->getWindow(), Resizefunc);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		shader = new Shader("C:\\Users\\Ruurd\\source\\repos\\Trixs\\Trixs\\basicShader.vs", "C:\\Users\\Ruurd\\source\\repos\\Trixs\\Trixs\\basicShader.fs");
		Lampshader = new Shader("C:\\Users\\Ruurd\\source\\repos\\Trixs\\Trixs\\lampShader.vs", "C:\\Users\\Ruurd\\source\\repos\\Trixs\\Trixs\\lampShader.fs");

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------

		//glGenVertexArrays(1, &lightVAO);
		//glGenBuffers(1, &lightVBO);
		//glBindVertexArray(lightVAO);

		//glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		//// note that we update the lamp's position attribute's stride to reflect the updated buffer data
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		glEnable(GL_DEPTH_TEST);

		// framebuffer configuration
		// -------------------------
		framebuffer = 0;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		unsigned int textureColorbuffer;
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		width = 800;
		height = 600;
	}

	RenderManager::~RenderManager()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glfwTerminate();
	}

	void RenderManager::render()
	{
		processInput(basewindow->getWindow());


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader->use();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		vec3 campos = MainManager::getInstance().getProject()->getCurrentScene()->getCamera().getPosition();
		view = glm::translate(view, glm::vec3(campos.x(), campos.y(), campos.z())); //todo add camera here

		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		shader->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
		shader->setVec3("viewPos", 0.0f, 0.5f, -3.0f);
		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		unsigned int transformLoc = glGetUniformLocation(shader->ID, "model"); //model transform

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));


		glBindVertexArray(VAO);
		glDrawElements(GL_LINES, 22, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		std::vector<Hittable*>* world = MainManager::getInstance().getProject()->getCurrentScene()->getObjects();
		for (auto i = 0; i < world->size(); i++)
		{
			glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

			Transform* t = world->at(i)->getTransform();
			glm::vec3 pos(t->getPos().x(), t->getPos().y(), t->getPos().z());
			glm::vec3 rot(t->getRot().x(), t->getRot().y(), t->getRot().z());
			glm::vec3 scale(t->getScale().x(), t->getScale().y(), t->getScale().z());
			transform = glm::translate(transform, pos);
			transform = glm::rotate(transform, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, scale);

			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


			world->at(i)->draw();
		}

		//Lampshader->use();
		//Lampshader->setMat4("projection", projection);
		//Lampshader->setMat4("view", view);
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
		//model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		//Lampshader->setMat4("model", model);

		//glBindVertexArray(lightVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// clear all relevant buffers
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		//glClear(GL_COLOR_BUFFER_BIT);

	}

	void RenderManager::drawGrid()
	{

	}

	bool RenderManager::WindowShouldClose()
	{
		return glfwWindowShouldClose(basewindow->getWindow());
	}

	GLFWwindow * RenderManager::getWindow()
	{
		return basewindow->getWindow();
	}
	void RenderManager::framebufferSizeCallback(int width, int height)
	{
		//glViewport(0, 0, width, height);
		MainManager::getInstance().getWindow()->setSize(width, height);
	}
	void RenderManager::setNewSize(int width, int height)
	{
		glViewport(0, 0, width, height);

		//aspect ratio 
		this->width = width;
		this->height = height;

		//glDeleteFramebuffers(1, &framebuffer);

		// framebuffer configuration
		// -------------------------
		framebuffer = 0;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}