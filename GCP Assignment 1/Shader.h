#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <SDL.h>

#include "misc/Mat4.h"

/** 
@brief A GLSL shader program. 

Contains a compiled shader program and any uniform locations
*/
class Shader 
{
public:

	/**
	 @brief Constructor.
	
	 @param vShaderFilename Filename of the vertex shader.
	 @param fShaderFilename Filename of the fragment shader.
	 */
	Shader(std::string vShaderFilename, std::string fShaderFilename);
	
	~Shader();

	/**
	@brief Get the shader program
	@return GLuint - Shader Program
	*/
	GLuint getProgram() { return program; }

	
	void setUniform(std::string name, float x, float y, float z);
	void setUniform(std::string name, const glm::vec2 & v);
	void setUniform(std::string name, const glm::vec3 & v);
	void setUniform(std::string name, const glm::vec4 & v);
	void setUniform(std::string name, const glm::mat4 & m);
	void setUniform(std::string name, const Mat4 & m);
	void setUniform(std::string name, const glm::mat3 & m);
	void setUniform(std::string name, float val);
	void setUniform(std::string name, int val);
	void setUniform(std::string name, bool val);
	void setUniform(std::string name, GLuint val);

private:
	///Shader Program
	GLuint program;

	///Individual Shader IDs
	GLuint vShader, fShader;

	std::map<std::string, int> uniformLocations;

	GLint getUniformLocation(std::string name);

	/**
	@brief Loads a shader from a file and returns its contents
	@param path Path to the shader
	@return std::string - Shader file contents
	*/
	std::string loadShaderFromFile(std::string path);
	
	/**
	@brief Checks for any errors in the loaded shader/compile errors
	@param shader Shader to check
	@return bool - Compiled Successfully
	*/
	bool checkShaderCompiled(GLint shader);

	/**
	 @brief Initialises the shaders.
	 Calls the load function to load the shaders and compile them into a program.
	 @param vShaderFilename Filename of the shader file.
	 @param fShaderFilename Filename of the shader file.
	 */
	void initialiseShaders(std::string vShaderFilename, std::string fShaderFilename);
};