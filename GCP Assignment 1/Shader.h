#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <SDL.h>

#include "misc/Mat4.h"

//Modified but a previous version was used in another assignment

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
	
	/** @brief	Destructor. */
	~Shader();

	/**
	@brief Get the shader program
	@return GLuint - Shader Program
	*/
	GLuint getProgram() { return program; }

	//Set Uniforms
	/**
	 @brief	Pass 3 float values to the shader.
	
	 @param	name	The shader variable name.
	 @param	x   	The x coordinate.
	 @param	y   	The y coordinate.
	 @param	z   	The z coordinate.
	 */
	void setUniform(std::string name, float x, float y, float z);

	/**
	 @brief	Pass Vector2 to the shader.
	
	 @param	name	The shader variable name.
	 @param	v   	The Vec2.
	 */
	void setUniform(std::string name, const glm::vec2 & v);

	/**
	 @brief	Pass Vector3 to the shader.

	 @param	name	The shader variable name.
	 @param	v   	The Vec3.
	 */
	void setUniform(std::string name, const glm::vec3 & v);

	/**
	 @brief	Pass Vector4 to the shader.

	 @param	name	The shader variable name.
	 @param	v   	The Vec4.
	 */
	void setUniform(std::string name, const glm::vec4 & v);

	/**
	 @brief	Pass Mat4 to the shader.

	 @param	name	The shader variable name.
	 @param	m   	The Mat4.
	 */
	void setUniform(std::string name, const glm::mat4 & m);

	/**
	 @brief	Pass Mat4 to the shader.

	 @param	name	The shader variable name.
	 @param	m   	The Mat4.
	 */
	void setUniform(std::string name, const Mat4 & m);

	/**
	 @brief	Pass Mat4 to the shader.

	 @param	name	  The shader variable name.
	 @param	m   	  The Mat4.
	 @param transpose Should the matrix be transposed (Pass GL_TRUE or GL_FALSE)
	 */
	void setUniform(std::string name, const Mat4 & m, int transpose);

	/**
	 @brief	Pass Mat3 to the shader.

	 @param	name	The shader variable name.
	 @param	m   	The Mat3.
	 */
	void setUniform(std::string name, const glm::mat3 & m);

	/**
	 @brief	Pass a float to the shader.

	 @param	name	The shader variable name.
	 @param	val  	The float.
	 */
	void setUniform(std::string name, float val);

	/**
	 @brief	Pass a int to the shader.

	 @param	name	The shader variable name.
	 @param	val  	The int.
	 */
	void setUniform(std::string name, int val);

	/**
	 @brief	Pass a boolean to the shader.

	 @param	name	The shader variable name.
	 @param	val  	The boolean.
	 */
	void setUniform(std::string name, bool val);
	
	/**
	 @brief	Pass a GLuint to the shader.

	 @param	name	The shader variable name.
	 @param	val  	The GLuint.
	 */
	void setUniform(std::string name, GLuint val);

private:
	///Shader Program
	GLuint program;

	///Individual Shader IDs
	GLuint vShader, fShader;

	/** @brief	The uniform locations in the shader. */
	std::map<std::string, int> uniformLocations;

	/**
	 @brief	Gets a uniform location from the shader or creates it.
	
	 @param	name	The shader variable name.
	
	 @return	The uniform location.
	 */
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