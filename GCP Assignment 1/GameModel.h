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

	GameModel(
		std::vector<glm::vec3>* vertices,
		std::vector<glm::vec3>* normals,
		std::vector<glm::vec2>* uvs,
		std::vector<unsigned int>* indices,
		Texture* texture);
	
	~GameModel();

	void addTexture(Texture* texture, std::string shaderVarName);

	void deleteTexturesFromGPU();

	/**
	 @brief Draws object using the given camera view and projection matrices.
	
	 @param [in,out] modelMatrix The model matrix.
	 @param [in,out] viewMatrix  The view matrix.
	 @param [in,out] projMatrix  The projection matrix.
	 @param [in,out] shader		 Shader used for rendering this model.
	 */
	void draw(glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix, Shader* shader);

	void draw2D(Shader* shader);
private:

	struct TextureWrapper
	{
		GLint textureUnit;
		GLuint textureID;
		std::string shaderVarName;
		Texture* texture;
	};

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/** @brief Buffers for vertex data. */
	std::vector<GLuint> VBOs;

	/// Buffer for indices
	GLuint indexBuffer;

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

	void addVBO(std::vector<glm::vec3> &data);
	void addVBO(std::vector<glm::vec2> &data);

	void addIndexBuffer(std::vector<unsigned int> &indices);

	

	std::vector<unsigned int> extractMeshIndexData(aiMesh* mesh);

	/// Number of vertices in the model
	unsigned int numVertices;

	unsigned int numIndices;
};