#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


static bool setUpVAO = true;
static int squaresCount = 0;
static int pointsCount = 0;

static float* vertices;
static std::vector<float> vertexData;

//Fragment Shader source code
std::string  LoadShader(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void PrepareShader(GLuint& shaderProgram)
{
	std::string vs = LoadShader("basic.vert");
	const char* vertexSource = vs.c_str();

	std::string fs = LoadShader("basic.frag");
	const char* fragmentSource = fs.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	int  success;
	char infoLog[1024];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create Shader Program Object and get its reference
	shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void PrepareVertexArray(GLuint& VAO)
{
	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, pointsCount * sizeof(float), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));


	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

		// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

struct Color
{
	float R;
	float G;
	float B;

	Color(float r, float g, float b)
		: R(r), G(g), B(b)
	{
	}
};

struct Point
{
	float x;
	float y;
	Color color;

	Point(float _x, float _y, Color _color)
		: x(_x), y(_y), color(_color)
	{
	}
};

void NumberOfSquares(int squares)
{
	squaresCount = squares;
	pointsCount = 30 * squaresCount;
	vertices = new float[pointsCount];
}

static GLuint shaderProgram;
static GLuint VAO;

void DrawSquare(Point point, float size)
{

	if (squaresCount > 0)
	{
		vertexData.push_back(point.x);            //left up
		vertexData.push_back(point.y);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);
		vertexData.push_back(point.x);            //left up
		vertexData.push_back(point.y);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);
		vertexData.push_back(point.x + size);     //right up
		vertexData.push_back(point.y);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);
		vertexData.push_back(point.x);            //left down
		vertexData.push_back(point.y - size);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);
		vertexData.push_back(point.x + size);     //right down
		vertexData.push_back(point.y - size);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);
		vertexData.push_back(point.x + size);     //right down
		vertexData.push_back(point.y - size);
		vertexData.push_back(point.color.R);
		vertexData.push_back(point.color.G);
		vertexData.push_back(point.color.B);


		squaresCount--;
	}
	else if (squaresCount == 0 && setUpVAO)
	{
		int i = 0;
		for (float vertex : vertexData)
		{
			vertices[i++] = vertex;
		}

		PrepareShader(shaderProgram);
		PrepareVertexArray(VAO);
		setUpVAO = false;
	}
	else
	{
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, pointsCount);
	}


}
