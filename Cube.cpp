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
	//renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");//1个,24个
	renderingProgram = Utils::createShaderProgram("vertShaderManyCube.glsl", "fragShader.glsl");
	//cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;//近
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 420.0f;//远
	cubeLocx = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;//延y轴以下展示透视
	setupVertices();
}

//单个
void Cube::display(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//清除深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//启用着色器，在gpu上安装GLSL代码

	//获取MV矩阵和投影矩阵的统一变量
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	//构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	tMat = glm::translate(glm::mat4(1.0f), glm::vec3(glm::sin(0.035f * currentTime) * 2.0f,
		glm::cos(0.052f * currentTime) * 2.0f, glm::sin(0.07f * currentTime) * 2.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(glm::mat4(1.0f), 1.75f * currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));

	mMat = tMat * rMat;
	mvMat = vMat * mMat;

	//将透视矩阵和mv矩阵复制给相应的统一变量1,2
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//将VBO关联给顶点着色器中相应的顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//					vbo[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);//vbo[0]（location）

	//调整OpenGL，绘制模型
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//24
void Cube::display_2(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//清除深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//启用着色器，在gpu上安装GLSL代码

	//获取MV矩阵和投影矩阵的统一变量
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	//构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);

	//构建视图矩阵
	float time_factor;
	for (int i = 0; i < 24; i++) {//多个
		time_factor = currentTime + i;
		vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
		tMat = glm::translate(glm::mat4(1.0f), glm::vec3(glm::sin(.35f*time_factor)*8.0f, glm::sin(.52f * time_factor) * 8.0f, glm::sin(.70f * time_factor) * 8.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(glm::mat4(1.0f), 1.75f * time_factor, glm::vec3(1.0f, 0.0f, 0.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * time_factor, glm::vec3(0.0f, 1.0f, 0.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * time_factor, glm::vec3(0.0f, 0.0f, 1.0f));

		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		//将透视矩阵和mv矩阵复制给相应的统一变量1,2
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		//将VBO关联给顶点着色器中相应的顶点属性
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//					vbo[0]
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);//vbo[0]（location）

		//调整OpenGL，绘制模型
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//软件编码单个1，多个立方体2
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//实例化绘制多个相同图形
void Cube::display_3(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//清除深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//启用着色器，在gpu上安装GLSL代码

	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
	vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	tfLoc = glGetUniformLocation(renderingProgram, "time_factor");

	
	

	//构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);

	//构建视图矩阵
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	tMat = glm::translate(glm::mat4(1.0f), glm::vec3(glm::sin(0.035f * currentTime) * 2.0f,
		glm::cos(0.052f * currentTime) * 2.0f, glm::sin(0.07f * currentTime) * 2.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(glm::mat4(1.0f), 1.75f * currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
	mMat = tMat * rMat;
	
	timeFactor = (float)currentTime;

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
	glUniform1f(tfLoc, (float)timeFactor);

	//将VBO关联给顶点着色器中相应的顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);//vbo[0]（location）

	//调整OpenGL，绘制模型
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//硬件编码立方体1000个
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10000);
}