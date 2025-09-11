#include <fstream>
#include "Shader.h"

using namespace std;

Shader::Shader()
{
	shaderId = 0;
	compiled = false;
}

void Shader::initFromSource(const ShaderType type, const string& source)
{
	const char* sourcePtr = source.c_str();
	GLint status;
	char buffer[512];

	switch (type)
	{
	case VERTEX_SHADER:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	if (shaderId == 0)
	{
		compiled = false;
		errorLog = "Error creating shader type " + to_string(type) + "\n";
		return;
	}

	glShaderSource(shaderId, 1, &sourcePtr, NULL);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	compiled = (status == GL_TRUE);
	glGetShaderInfoLog(shaderId, 512, NULL, buffer);
	errorLog.assign(buffer);
}

bool Shader::initFromFile(ShaderType type, const string &filename)
{
	string shaderSource;
	if (!loadShaderSource(filename, shaderSource))
	{
		compiled = false;
		errorLog = "Error loading shader source: " + filename + "\n";
		return false;
	}

	initFromSource(type, shaderSource);
	if (!compiled)
	{
		errorLog = "Error compiling shader: " + filename + "\n" + errorLog;
		return false;
	}
	return true;
}

void Shader::free()
{
	glDeleteShader(shaderId);
	shaderId = 0;
	compiled = false;
}

GLuint Shader::getShaderId() const
{
	return shaderId;
}

bool Shader::isCompiled() const
{
	return compiled;
}

const string &Shader::log() const
{
	return errorLog;
}

bool Shader::loadShaderSource(const string &filename, string &shaderSource)
{
	ifstream file;
	file.open(filename.c_str());
	if (!file.is_open())
		return false;

	shaderSource.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
	return true;
}