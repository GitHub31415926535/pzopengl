#pragma once

#include "utils.h"

class TextureTest
{
public:
	void init(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);
	
protected:
	void setupVertices();
private:
	const int numVAOs = 1;
	const int numVBOs = 2;
	float cameraX, cameraY, cameraZ;
	float cubeLocx, cubeLocY, cubeLocZ;
	GLuint vao[1];
	GLuint vbo[2];
	GLuint brickTexture;//×©¿éÎÆÀí
	GLuint renderingProgram;
	GLuint mvLoc, projLoc;
	int width, height;
	float aspect;
	glm::mat4 pMat, mMat, vMat, mvMat, tMat, rMat;
};

