#include "utils.h"

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);//�ṩ�йر������glsl��ɫ������Ϣ
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log:" << log << std::endl;
		free(log);
	}
}

void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);//�ṩ�йر������glsl�������Ϣ
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log:" << log << std::endl;
		free(log);
	}
}

bool checkOpenGLError() {
	bool findError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		findError = true;
		glErr = glGetError();
	}
	return findError;
}

std::string readShaderSource(const char* filePath) {
	std::string content;

	std::ifstream fileStream(filePath, std::ios::in);
	bool is_open = fileStream.is_open();
	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint createShaderProgram(const char* vp, const char* fp) {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vp_str, fp_str;
	std::ifstream vfileStream(vp, std::ios::in);
	bool is_open = vfileStream.is_open();
	std::string vline = "";
	while (!vfileStream.eof()) {
		std::getline(vfileStream, vline);
		vp_str.append(vline + "\n");
	}
	vfileStream.close();
	std::ifstream pfileStream(fp, std::ios::in);
	std::string pline = "";
	while (!pfileStream.eof()) {
		std::getline(pfileStream, pline);
		fp_str.append(pline + "\n");
	}
	pfileStream.close();

	const char * vp_str_chars = vp_str.c_str();
	const char * fp_str_chars = fp_str.c_str();
	//				��ɫ�� �ַ������� �ַ���ָ�� 
	glShaderSource(vShader, 1, &vp_str_chars, NULL);	//��GLSL������ַ����������ɫ������
	glShaderSource(fShader, 1, &fp_str_chars, nullptr);
	glCompileShader(vShader);	//����
	checkOpenGLError();//���������ɫ��ʱ�Ĵ���
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		std::cout << "vertex compilation failed!" << std::endl;
		printShaderLog(vShader);
	}
	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		std::cout << "fragment compilation failed!" << std::endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();//��������
	glAttachShader(vfProgram, vShader);	//����ɫ������������
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);	//����GLSL������ȷ��������
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "linked failed!" << std::endl;
		printProgramLog(vfProgram);
	}

	return vfProgram;
}

GLuint createShaderProgram(const char* vp, const char* gp, const char* fp) {
	return 0;
}

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* fp) {
	return 0;
}

GLuint createShaderProgram(const char* vp, const char* tCs, const char* tEs, const char* gp,
	const char* fp) {
	return 0;
}