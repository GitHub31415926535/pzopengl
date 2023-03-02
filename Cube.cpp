#include "Cube.h"

void Cube::setupVertices(void) {//36个顶点，12个三角形
	float vertexPositions[108] = {
		-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,//5
		-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,
	};
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void Cube::init(GLFWwindow* window) {
	renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocx = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;//延y轴以下展示透视
	setupVertices();
}

void Cube::display(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	//获取MV矩阵和投影矩阵的统一变量
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	//构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);

	//构建视图矩阵
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	/*tMat = glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(glm::sin(0.35f * currentTime) * 2.0f),
		static_cast<float>(glm::cos(0.52f * currentTime) * 2.0f), static_cast<float>(glm::sin(0.7f * currentTime) * 2.0f)));
	rMat = glm::rotate<double, glm::qualifier::defaultp> (rMat, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));*/

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocx, cubeLocY, cubeLocZ));
	mvMat = vMat * mMat;

	//将透视矩阵和mv矩阵复制给相应的统一变量
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//将VBO关联给顶点着色器中相应的顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//调整OpenGL，绘制模型
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
