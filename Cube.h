#pragma once

#include "utils.h"
class Cube
{
public:
	void init(GLFWwindow* window);
	void display(GLFWwindow* window, const double& currentTime);//1个
	void display_2(GLFWwindow* window, const double& currentTime);//24个
	void display_3(GLFWwindow* window, const double& currentTime);//实例化10000个

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

	//use for 多个立方体，实例化渲染
	GLuint mLoc, vLoc, tfLoc;
	float timeFactor;
};

