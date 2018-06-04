//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Texture.cpp"
// Description	: Texture implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Texture.h"

Texture::Texture() {}
Texture::~Texture() {}
EShape Texture::m_shape = TWOD;

/***********************
* BindTexture: Binds the texture
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: filename - file name of the texture
* @parameter: _fWidth - the width of the texture specified by the creator
* @parameter: _fHeight - the height of the texture specified by the creator
* @parameter: _colour - the specified colour vec of the texture
* @parameter: _vao - the vertex array object passed in by reference
* @parameter: _texture - the texture variable passed in by reference
* @parameter: _shape - the specific shape of the object (enum)
***********************/
void Texture::BindTexture(const char * filename, float _fWidth, float _fHeight,
	glm::vec4 _colour, GLuint & _vao, GLuint & _texture, EShape _shape)
{
	float halfHeight = _fHeight;
	float halfWidth = _fWidth;

	m_shape = _shape;

	// Initialise Verticies depending on shape of sprite
	switch (m_shape)
	{
	case PYRAMID:
	{
		//3D pyramid vertices
		GLfloat actualVerticesPyramid[] = {
			//Positions			// Colors			// Tex Coords
			-halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // 0 // Base
			halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // 1
			halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f, // 2
			-halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f, // 3

			-halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // 4 // Side 1
			-halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // 5

			-halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // 6 // Side 2
			halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // 7

			halfWidth, halfHeight, 1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // 8 // Side 3
			halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // 9

			halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // 10 // Side 4
			-halfWidth, halfHeight, -1.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // 11

			halfWidth, halfHeight, 0.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.5f, 0.0f, // 12 // Top Point
		};

		for (int i = 0; i < 117; ++i)
		{
			verticesPyramid[i] = actualVerticesPyramid[i];
		}
		break;
	}
	case CUBE:
	{
		//3D cube vertices
		GLfloat actualVerticesCube[216] = {
			// Front Face
			-halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			-halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,
			// Right Face
			halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,

			// Back Face
			halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			-halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			-halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,
			// Left Face
			-halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			-halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			-halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			-halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,

			// Top Face
			-halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			halfWidth, halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			-halfWidth, halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,
			// Bottom Face
			-halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f,
			halfWidth, -halfHeight, 1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f,
			halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f,
			-halfWidth, -halfHeight, -1.0f,			_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f,
		};

		for (int i = 0; i < 216; ++i)
		{
			verticesCube[i] = actualVerticesCube[i];
		}
		break;
	}
	default: //2D box
	{
		//2D vertices
		GLfloat actualVertices[] = {
			// Positions // Colors // Tex Coords
			-halfWidth, halfHeight, 0.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 0.0f, // Top Left
			halfWidth, halfHeight, 0.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 0.0f, // Top Right 
			halfWidth, -halfHeight, 0.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		1.0f, 1.0f, // Bottom Right
			-halfWidth, -halfHeight, 0.0f,		_colour.r, _colour.g, _colour.b, _colour.a,		0.0f, 1.0f, // Bottom Left
		};

		for (int i = 0; i < 36; ++i)
		{
			vertices[i] = actualVertices[i];
		}
		break;
	}
	}

	// Create local variables (Not needed after binding complete
	GLuint vbo;
	GLuint ebo;
	//GLuint vao;
	//GLuint texture;

	// Generating and binding texture (Set up)
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Image mode if UV bigger (Set to repeat)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// MipMap whether image is blurred or set to exact pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set Image via SOIL library
	int width, height;
	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


	//Generate Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free soil image
	SOIL_free_image_data(image);

	// Clear texture 2D
	glBindTexture(GL_TEXTURE_2D, 0);

	//_texture = texture;

	// Generating objects and texture
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// Bind objects and texture
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (m_shape == PYRAMID)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPyramid), verticesPyramid, GL_STATIC_DRAW);
	}
	else if (m_shape == CUBE)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);

	glVertexAttribPointer(
		0, // Layout location on vertex shader
		3, // 3 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)0); // Offset
	glVertexAttribPointer(
		1, // Layout location on vertex shader
		4, // 4 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset
	glVertexAttribPointer(
		2, // Layout location on vertex shader
		2, // 2 float components (eg position)
		GL_FLOAT, // Type of data
		GL_FALSE, // Data normalized?
		9 * sizeof(GLfloat), //Stride of the single vertex(pos + color + uv)
		(GLvoid*)(7 * sizeof(GLfloat))); // Offset
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	if (m_shape == PYRAMID)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPyramid), indicesPyramid, GL_STATIC_DRAW);
	}
	else if (m_shape == CUBE)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesCube), indicesCube, GL_STATIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	//_vao = vao;

}

/***********************
* Render: Render the texture
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: vao - vertex array object
* @parameter: texture - texture of the object
***********************/
void Texture::Render(GLuint vao, GLuint texture)
{
	glEnable(GL_DEPTH_TEST); //TEXT WILL NOT WORK IF ON IN PERSPECTIVE CAM
							 //glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	//glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(Utils::programTextured, "tex"), 0); //not sending in texture itself
	glUseProgram(Utils::programTextured);
	glBindVertexArray(vao);

	switch (m_shape)
	{
	case PYRAMID:
	{
		glDrawElements(GL_TRIANGLES, sizeof(indicesPyramid) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		break;
	}
	case CUBE:
	{
		glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		break;
	}
	default:
	{
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		break;
	}
	}

	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

	//glDisable(GL_CULL_FACE);
}