#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "Texture.h"
// Description	: Texture declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "stdafx.h"

class Texture
{
public:

	Texture();
	~Texture();

	static void BindTexture(const char* filename, float _fHalfWidth, 
		float _fHalfHeight, glm::vec4 _colour, GLuint& vao, 
		GLuint& vbo, GLuint& ebo, GLuint& texture, EShape _shape);
	static void Render(GLuint vao, GLuint texture, EShape shape);
	GLuint tex;

private:
	static EShape m_shape;

};
