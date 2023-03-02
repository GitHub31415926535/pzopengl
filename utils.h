#pragma once
#include <GLEW/glew.h>	//opengl extension wrangler
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

//检查OpenGL错误标志，即是否发生OpenGL错误;既检测编译又检测运行时错误
bool checkOpenGLError();

//当GLSL编译失败时，显示Opengl日志内容
void printShaderLog(GLuint shader);

//当GLSL链接失败时，显示Opengl日志内容
void printProgramLog(int prog);

//std::string readShaderSource(const char* filePath);

GLuint createShaderProgram(const char* vp, const char* fp);

GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* fp);

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* gp, const char* fp);