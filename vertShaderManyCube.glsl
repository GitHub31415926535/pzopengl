#version 430
layout (location=0) in vec3 position;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float time_factor;//用于动画和放置立方体的时间因子

out vec4 varyingColor;

mat4 buildRotateX(float rad);//glsl要求函数先声明后调用
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void){
	float i = gl_InstanceID + time_factor;//取值基于时间因子，但是对于每个立方体是不同的
	float a = sin(203.0 * i / 8000.0) * 403.0;//平移用的x,y,x分量
	float b = sin(301.0 * i / 4001.0) * 401.0;
	float c = sin(400.0 * i / 6003.0) * 405.0;

	//构建旋转和平移矩阵，将会应用于当前立方体
	mat4 localRotX = buildRotateX(1000 * i);
	mat4 localRotY = buildRotateY(1000 * i);
	mat4 localRotZ = buildRotateZ(1000 * i);
	mat4 localTrans = buildTranslate(a, b, c);

	//构建模型矩阵，然后是模型-视图矩阵
	mat4 newM_matrix = m_matrix * localTrans * localRotX * localRotY * localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

//构建平移矩阵的工具函数
mat4 buildTranslate(float x, float y, float z){
mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,//这是第一列，而非第一行
				  0.0, 1.0, 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  x, y,z, 1.0);
	return trans;
}

//构建并返回绕X轴旋转的矩阵
mat4 buildRotateX(float rad){
mat4 rotx = mat4(1.0, 0.0, 0.0, 0.0,//这是第一列，而非第一行
				  0.0, cos(rad), -sin(rad), 0.0,
				  0.0, sin(rad), cos(rad), 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return rotx;
}

//构建并返回绕Y轴旋转的矩阵
mat4 buildRotateY(float rad){
mat4 roty = mat4(cos(rad), 0.0, sin(rad), 0.0,//这是第一列，而非第一行
				  0.0, 1.0, 0.0, 0.0,
				  -sin(rad), 0.0, cos(rad), 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return roty;
}

//构建并返回绕Z轴旋转的矩阵
mat4 buildRotateZ(float rad){
mat4 rotz = mat4(cos(rad), -sin(rad), 0.0, 0.0,//这是第一列，而非第一行
				  sin(rad), cos(rad), 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return rotz;
}