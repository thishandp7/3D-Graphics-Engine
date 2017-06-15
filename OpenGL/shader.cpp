#include "shader.h"
#include <fstream>
#include <iostream>


//To check and reports errors in the shader - Helper method
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
//To check whether the shader loading is successful - Helper method
static string LoadShader(const string& fileName);
//To create a shader - Helper method
static GLuint CreateShader(const string& text, GLenum shaderType);

Shader::Shader(const string& fileName)
{
	m_program = glCreateProgram();//Creating a shader program
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);//Creating a Vertex shader
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);//Creating a Fragment shader

	for (unsigned int x = 0; x < NUM_SHADERS; x++)
	{
		glAttachShader(m_program, m_shaders[x]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 1, "normal");

	//Linking the program
	glLinkProgram(m_program);
	//To check whether the shader program has linked properly
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: program linking failed: ");
	//Validating the the program
	glValidateProgram(m_program);
	//To validate the shader program
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: program is invalid: ");

	glShadeModel(GL_SMOOTH);

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}
Shader::~Shader()
{
	for (unsigned int x = 0; x < NUM_SHADERS; x++)
	{
		glDetachShader(m_program, m_shaders[x]);//Detaching the shaders from the shader program
		glDeleteShader(m_shaders[x]);//Deleting the shaders
	}
	glDeleteProgram(m_program);//To delete the shader program
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{

	 mat4 model = camera.GetViewProjection()* transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);

}

static GLuint CreateShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		cout << "Error: Shader creation failed!" << endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	//To check the shader complilation status
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static string LoadShader(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cout << "Unable to load shader: " << fileName << endl;
	}
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		cout << errorMessage << ": '" << error << "'" << endl;
	}
}