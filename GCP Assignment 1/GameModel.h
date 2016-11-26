#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "misc/Vertex.h"
#include "misc/Mat4.h"

//Modified but a previous version was used in another assignment

//Forward Declaration
class ResourceManager;

/// Class to store and display a model
class GameModel : public Resource
{
public:

	/**
	@brief Constructor.
	
	@param [in,out] mesh    Mesh data.
	@param [in,out] texture Texture to use for the model.
	 */
	GameModel(aiMesh* mesh, Texture* texture);

	/**
	 @brief	Constructor.
	
	 @param [in,out]	vertices	If non-null, the vertices.
	 @param [in,out]	normals 	If non-null, the normals.
	 @param [in,out]	uvs			If non-null, the uvs.
	 @param [in,out]	indices 	If non-null, the indices.
	 @param [in,out]	texture 	If non-null, the texture.
	 */
	GameModel(
		std::vector<glm::vec3>* vertices,
		std::vector<glm::vec3>* normals,
		std::vector<glm::vec2>* uvs,
		std::vector<unsigned int>* indices,
		Texture* texture);
	
	/** @brief	Destructor. */
	~GameModel();

	/**
	 @brief	Adds a texture to 'shaderVarName' in the shader.
	
	 @param [in]	texture	If non-null, the texture data.
	 @param	shaderVarName	   	Name of the shader variable.
	 */
	void addTexture(Texture* texture, std::string shaderVarName);

	/** @brief	Deletes the textures from GPU. */
	void deleteTexturesFromGPU();

	/**
	 @brief Draws object using the given camera view and projection matrices.
	
	 @param [in,out] modelMatrix The model matrix.
	 @param [in,out] viewMatrix  The view matrix.
	 @param [in,out] projMatrix  The projection matrix.
	 @param [in,out] shader		 Shader used for rendering this model.
	 */
	void draw(Mat4 modelMatrix, Mat4 viewMatrix, Mat4 projMatrix, Shader* shader);

	/**
	 @brief	Draw a 2D UI element.
	
	 @param [in,out]	shader	If non-null, the shader.
	 */
	void draw2D(Shader* shader);
private:

	/** @brief	A wrapper around the OpenGL representation of a Texture. */
	struct TextureWrapper
	{
		
		/** @brief	The texture unit e.x GL_TEXTURE0. */
		GLint textureUnit;
		/** @brief	OpenGL identifier for the texture. */
		GLuint textureID;
		/** @brief	Name of the shader variable the texure is passed to. */
		std::string shaderVarName;
		/** @brief	The texture data. */
		Texture* texture;
	};

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/** @brief Buffers for vertex data. */
	std::vector<GLuint> VBOs;

	/// Buffer for indices
	GLuint indexBuffer;

	/**
	 @brief	The next available texture unit in OpenGL.
	 @todo Redundant, remove in graphics rewrite
	 */
	int nextAvailableTextureUnit;

	/** @brief Identifier for the textures. */
	std::vector<TextureWrapper> textures;

	/** @brief The texture data. */
	//Texture* texture;

	/** @brief true to disable, false to enable the matrix uniforms. (Is used to avoid passing matrices to 2D UI objects)*/
	bool disableMatUniforms;

	/**
	@brief Initialises the Vertices and Indicies from a model imported by ASSIMP
	@param mesh Mesh data.
	*/
	void loadModelDataFromASSIMP(aiMesh* mesh);

	/**
	 @brief	Adds a VBO of Vec3 data to the VAO.
	
	 @param [in]	data	The data.
	 */
	void addVBO(std::vector<glm::vec3> &data);

	/**
	@brief	Adds a VBO of Vec2 data to the VAO.

	@param [in]	data	The data.
	*/
	void addVBO(std::vector<glm::vec2> &data);

	/**
	 @brief	Adds an index buffer to the VAO.
	
	 @param [in]	indices	The indices.
	 */
	void addIndexBuffer(std::vector<unsigned int> &indices);

	/**
	 @brief	Extracts the mesh index data described by mesh.
	
	 @param [in,out]	mesh	If non-null, the mesh.
	
	 @return	The extracted mesh indices.
	 */
	std::vector<unsigned int> extractMeshIndexData(aiMesh* mesh);

	/// Number of vertices in the model
	unsigned int numVertices;

	/** @brief	Number of indices in the model. */
	unsigned int numIndices;
};