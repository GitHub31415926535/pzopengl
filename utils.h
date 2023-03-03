#pragma once
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <GLEW/glew.h>	//opengl extension wrangler
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include <fstream>
#include <iostream>

#ifndef GLM_FORCE_RADIANS	//�Ի��ȱ�ʾ
#define GLM_FORCE_RADIANS
#endif // !GLM_FORCE_RADIANS


namespace Utils {
	//���OpenGL�����־�����Ƿ���OpenGL����;�ȼ������ּ������ʱ����
	bool checkOpenGLError();

	//��GLSL����ʧ��ʱ����ʾOpengl��־����
	void printShaderLog(GLuint shader);

	//��GLSL����ʧ��ʱ����ʾOpengl��־����
	void printProgramLog(int prog);

	//shader����
	//std::string readShaderSource(const char* filePath);

	GLuint createShaderProgram(const char* vp, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* gp, const char* fp);

	//ͼƬ����
	GLuint loadTexture(const char* texImagePath);
}
