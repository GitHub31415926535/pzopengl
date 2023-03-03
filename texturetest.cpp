#include "texturetest.h"

void TextureTest::setupVertices()
{
	float pyramidPositions[54] = {//������5�����㣬6�������Σ�ԭ���Σ�-1~1����3ά
		 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//ǰ���棬������ʱ�뻭��
		 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//�Ҳ���
		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//�����
		-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//�����
		 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,	//����1
		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f,	//����2
	};

	float pyTexCoords[36] = {//����2ά
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	//	ǰ���棬�Ҳ���
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	//	����棬�����
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f		//	����
	};
	//��������ؽ�������
	//					����	ID
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//��vao���Ϊ��Ծ
	//����vbo��һ�����ڶ���һ��������������
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);//�������������ݵ����鸴�ƽ���Ծ������
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyTexCoords), pyTexCoords, GL_STATIC_DRAW);
}

void TextureTest::init(GLFWwindow* window) {
	brickTexture = Utils::loadTexture("yellowbaby.jpg");
	renderingProgram = Utils::createShaderProgram("vertShaderTextureTest1.glsl", "fragShaderTextureTest1.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocx = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;//��y������չʾ͸��
	setupVertices();
}

void TextureTest::display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	//��ȡ��ɫ��������ͳһ������λ��
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
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

	//�����ݷ��͵�ͳһ�����У����ݸ�ͳһ����
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//���������е�ֵ���͵���ɫ���еĶ�������
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//����Ծ����������ɫ���еĶ������������
	glEnableVertexAttribArray(0);//���ö�������

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//��������Ԫ������󶨵��ض����������
	glActiveTexture(GL_TEXTURE0);//ʹ�õ�0������Ԫ���ڼ���״̬
	glBindTexture(GL_TEXTURE_2D, brickTexture);

	//�༶��Զ���������Թ��ˣ����Խ���
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);*/

	//�������Թ���AF
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {//�����Կ��Ƿ�֧��AF
		GLfloat anisoSetting = 0;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);//��ȡ�������̶�
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);//����Ӧ���ڼ����������
	}

	//ʹ�����������;���֮�佻��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//���ñ߿���ɫ��ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float sideColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, sideColor);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//vbo���ݴ��͸�layout���η��Ķ���������
	glDrawArrays(GL_TRIANGLES, 0, 18);
}