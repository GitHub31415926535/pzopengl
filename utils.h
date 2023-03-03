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

#ifndef GLM_FORCE_RADIANS	//以弧度表示
#define GLM_FORCE_RADIANS
#endif // !GLM_FORCE_RADIANS


namespace Utils {
	//检查OpenGL错误标志，即是否发生OpenGL错误;既检测编译又检测运行时错误
	bool checkOpenGLError();

	//当GLSL编译失败时，显示Opengl日志内容
	void printShaderLog(GLuint shader);

	//当GLSL链接失败时，显示Opengl日志内容
	void printProgramLog(int prog);

	//shader处理
	//std::string readShaderSource(const char* filePath);

	GLuint createShaderProgram(const char* vp, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* fp);

	GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* gp, const char* fp);

	//图片处理
	GLuint loadTexture(const char* texImagePath);
}
