#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "utils.h"
class Cube
{
public:
	void init(GLFWwindow* window);
	void display(GLFWwindow* window, const double& currentTime);

protected:
	void setupVertices(void);

private:
	const int numVAOs = 1;
	const int numVBOs = 2;
	float cameraX, cameraY, cameraZ;
	float cubeLocx, cubeLocY, cubeLocZ;
	GLuint renderingProgram;
	GLuint vao[1];
	GLuint vbo[2];

	GLuint mvLoc, projLoc;
	int width, height;
	float aspect;
	glm::mat4 pMat, mMat, vMat, mvMat, tMat, rMat;
};

