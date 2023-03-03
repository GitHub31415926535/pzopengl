#include "texturetest.h"

void TextureTest::setupVertices()
{
	float pyramidPositions[54] = {//金字塔5个顶点，6个三角形；原矩形（-1~1），3维
		 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//前侧面，这里逆时针画的
		 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//右侧面
		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//后侧面
		-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//左侧面
		 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,	//底面1
		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f,	//底面2
	};

	float pyTexCoords[36] = {//纹理2维
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	//	前侧面，右侧面
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	//	后侧面，左侧面
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f		//	底面
	};
	//将纹理加载进缓冲区
	//					数量	ID
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//将vao标记为活跃
	//两个vbo，一个用于顶点一个用于纹理坐标
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);//将包含顶点数据的数组复制进活跃缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyTexCoords), pyTexCoords, GL_STATIC_DRAW);
}

void TextureTest::init(GLFWwindow* window) {
	brickTexture = Utils::loadTexture("yellowbaby.jpg");
	renderingProgram = Utils::createShaderProgram("vertShaderTextureTest1.glsl", "fragShaderTextureTest1.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocx = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;//延y轴以下展示透视
	setupVertices();
}

void TextureTest::display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	//获取着色器程序中统一变量的位置
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

	//将数据发送到统一变量中，传递给统一变量
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//将缓冲区中的值发送到着色器中的顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//将活跃缓冲区与着色器中的顶点属性相关联
	glEnableVertexAttribArray(0);//启用顶点属性

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//激活纹理单元并将其绑定到特定的纹理对象
	glActiveTexture(GL_TEXTURE0);//使得第0个纹理单元处于激活状态
	glBindTexture(GL_TEXTURE_2D, brickTexture);

	//多级渐远纹理：三线性过滤；可以禁用
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);*/

	//各向异性过滤AF
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {//测试显卡是否支持AF
		GLfloat anisoSetting = 0;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);//获取最大采样程度
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);//将其应用于激活纹理对象
	}

	//使纹理在正常和镜像之间交替
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//设置边框颜色的模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float sideColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, sideColor);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//vbo数据传送给layout修饰符的顶点属性中
	glDrawArrays(GL_TRIANGLES, 0, 18);
}