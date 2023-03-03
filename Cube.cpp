#include "Cube.h"

void Cube::setupVertices(void) {//36�����㣬12��������
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
	//renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");//1��,24��
	renderingProgram = Utils::createShaderProgram("vertShaderManyCube.glsl", "fragShader.glsl");
	//cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;//��
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 420.0f;//Զ
	cubeLocx = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;//��y������չʾ͸��
	setupVertices();
}

//����
void Cube::display(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//������ɫ������gpu�ϰ�װGLSL����

	//��ȡMV�����ͶӰ�����ͳһ����
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	//����͸�Ӿ���
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

	//��͸�Ӿ����mv�����Ƹ���Ӧ��ͳһ����1,2
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//��VBO������������ɫ������Ӧ�Ķ�������
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//					vbo[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);//vbo[0]��location��

	//����OpenGL������ģ��
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//24
void Cube::display_2(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//������ɫ������gpu�ϰ�װGLSL����

	//��ȡMV�����ͶӰ�����ͳһ����
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	//����͸�Ӿ���
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);

	//������ͼ����
	float time_factor;
	for (int i = 0; i < 24; i++) {//���
		time_factor = currentTime + i;
		vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
		tMat = glm::translate(glm::mat4(1.0f), glm::vec3(glm::sin(.35f*time_factor)*8.0f, glm::sin(.52f * time_factor) * 8.0f, glm::sin(.70f * time_factor) * 8.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(glm::mat4(1.0f), 1.75f * time_factor, glm::vec3(1.0f, 0.0f, 0.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * time_factor, glm::vec3(0.0f, 1.0f, 0.0f));
		rMat = glm::rotate<double, glm::qualifier::defaultp>(rMat, 1.75f * time_factor, glm::vec3(0.0f, 0.0f, 1.0f));

		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		//��͸�Ӿ����mv�����Ƹ���Ӧ��ͳһ����1,2
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		//��VBO������������ɫ������Ӧ�Ķ�������
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//					vbo[0]
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);//vbo[0]��location��

		//����OpenGL������ģ��
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//������뵥��1�����������2
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

//ʵ�������ƶ����ͬͼ��
void Cube::display_3(GLFWwindow* window, const double& currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);//������ɫ������gpu�ϰ�װGLSL����

	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
	vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	tfLoc = glGetUniformLocation(renderingProgram, "time_factor");

	
	

	//����͸�Ӿ���
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0427f, aspect, 0.1f, 1000.0f);

	//������ͼ����
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

	//��VBO������������ɫ������Ӧ�Ķ�������
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);//vbo[0]��location��

	//����OpenGL������ģ��
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Ӳ������������1000��
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10000);
}