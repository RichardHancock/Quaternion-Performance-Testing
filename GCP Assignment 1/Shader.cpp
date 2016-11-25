#include "Shader.h"
#include "misc/Log.h"
#include <fstream>

Shader::Shader(std::string vShaderFilename, std::string fShaderFilename)
{
	initialiseShaders(vShaderFilename, fShaderFilename);
}

Shader::~Shader()
{
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteProgram(program);
}

void Shader::initialiseShaders(std::string vShaderFilename, std::string fShaderFilename)
{	
	std::string vShaderRaw = loadShaderFromFile(vShaderFilename);
	std::string fShaderRaw = loadShaderFromFile(fShaderFilename);
	const char* vShaderText = vShaderRaw.c_str();
	const char* fShaderText = fShaderRaw.c_str();

	// The 'program' stores the shaders
	program = glCreateProgram();

	// Create the vertex shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	// Give GL the source for it
	glShaderSource(vShader, 1, &vShaderText, NULL);
	// Compile the shader
	glCompileShader(vShader);
	// Check it compiled and give useful output if it didn't work!
	if (!checkShaderCompiled(vShader))
	{
		return;
	}
	// This links the shader to the program
	glAttachShader(program, vShader);

	// Same for the fragment shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	if (!checkShaderCompiled(fShader))
	{
		return;
	}
	glAttachShader(program, fShader);

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram(program);
	// Check this worked
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		Log::logE("Shader linking failed: " + std::string(log));
		delete[] log;

		return;
	}

}

bool Shader::checkShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		
		Log::logE("Shader compilation failed: " + std::string(log));
		//std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}

std::string Shader::loadShaderFromFile(std::string path)
{
	std::string shader;
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		Log::logE("Shader couldn't be opened: " + std::string(path));
		return "";
	}

	std::string line;
	while (!file.eof())
	{
		//file.getline(line,(std::streamsize) 2000);
		std::getline(file, line);
		line.append("\n");
		shader.append(line);
	}
	file.close();

	return shader;

}

GLint Shader::getUniformLocation(std::string name)
{
	std::map<std::string, int>::iterator pos;
	pos = uniformLocations.find(name);

	if (pos == uniformLocations.end()) {
		uniformLocations[name] = glGetUniformLocation(program, name.c_str());
	}

	return uniformLocations[name];
}

void Shader::setUniform(std::string name, float x, float y, float z)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc, x, y, z);
}

void Shader::setUniform(std::string name, const glm::vec3 & v)
{
	this->setUniform(name, v.x, v.y, v.z);
}

void Shader::setUniform(std::string name, const glm::vec4 & v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void Shader::setUniform(std::string name, const glm::vec2 & v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void Shader::setUniform(std::string name, const glm::mat4 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::setUniform(std::string name, const Mat4 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_TRUE, m[0]);
}

void Shader::setUniform(std::string name, const Mat4 & m, int transpose)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, transpose, m[0]);
}

void Shader::setUniform(std::string name, const glm::mat3 & m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::setUniform(std::string name, float val)
{
	GLint loc = getUniformLocation(name);
	glUniform1f(loc, val);
}

void Shader::setUniform(std::string name, int val)
{
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, val);
}

void Shader::setUniform(std::string name, GLuint val)
{
	GLint loc = getUniformLocation(name);
	glUniform1ui(loc, val);
}

void Shader::setUniform(std::string name, bool val)
{
	int loc = getUniformLocation(name);
	glUniform1i(loc, val);
}