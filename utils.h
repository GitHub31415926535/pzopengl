#pragma once
#include <GLEW/glew.h>	//opengl extension wrangler
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

//���OpenGL�����־�����Ƿ���OpenGL����;�ȼ������ּ������ʱ����
bool checkOpenGLError();

//��GLSL����ʧ��ʱ����ʾOpengl��־����
void printShaderLog(GLuint shader);

//��GLSL����ʧ��ʱ����ʾOpengl��־����
void printProgramLog(int prog);

//std::string readShaderSource(const char* filePath);

GLuint createShaderProgram(const char* vp, const char* fp);

GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* fp);

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* gp, const char* fp);