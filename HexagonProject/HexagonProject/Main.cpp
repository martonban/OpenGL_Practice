#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main();
void rotation(GLfloat* vertices[]);

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Triangle Rotation Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	
	gladLoadGL();
	glViewport(0, 0, 800, 800);


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] =
	{
		0.0f,	0.0f,	0.0f,
		0.66f,	0.33f,	0.0f,
		0.33f,	0.66f,	0.0f,
		-0.33f,	0.66f,	0.0f,
		-0.66f,	0.33f,	0.0f,
		-0.66f,	-0.33f,	0.0f,
		-0.33f,	-0.66f,	0.0f,
		0.33f,	-0.66f,	0.0f,
		0.66f,	-0.33f,	0.0f,
	};

	GLuint indices[] =
	{
		0, 1, 8,
		0, 1, 2,
		0, 3, 2,
		0, 4, 3,
		0, 5, 4,
		0, 6, 5,
		0, 7, 6,
		0, 8, 7
	};




	while (!glfwWindowShouldClose(window))
	{
		GLfloat *pointerVertices = &vertices;
		rotation(pointerVertices);

		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// I hade to change for sizte of the vertices for 3 to sizeof(vertices)/sizeof(vertices[0]) 
		glDrawElements(GL_TRIANGLES, sizeof(vertices)/sizeof(vertices[0]), GL_UNSIGNED_INT, 0);
		//Shader lezárása
		glfwSwapBuffers(window);
		glfwPollEvents();


		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram);
		glfwDestroyWindow(window);
		glfwTerminate();
		
	}

	
	return 0;
}

void rotation(GLfloat* vertices) {
	int size = sizeof(vertices) / sizeof(vertices[0]);
	float angle = 0.001f;
	for (int i = 0; i < size; i += 3) {
		vertices[i] = static_cast<GLfloat> (vertices[i] * cos(angle)) - (vertices[i] * sin(angle));
		vertices[i] = static_cast<GLfloat> (vertices[i+1] * cos(angle)) + (vertices[i+1] * sin(angle));
	}
}



