#pragma once

#include "utils.h"
class Cube
{
public:
	void init(GLFWwindow* window);
	void display(GLFWwindow* window, const double& currentTime);//1��
	void display_2(GLFWwindow* window, const double& currentTime);//24��
	void display_3(GLFWwindow* window, const double& currentTime);//ʵ����10000��

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

	//use for ��������壬ʵ������Ⱦ
	GLuint mLoc, vLoc, tfLoc;
	float timeFactor;
};

