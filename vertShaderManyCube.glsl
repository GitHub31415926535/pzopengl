#version 430
layout (location=0) in vec3 position;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float time_factor;//���ڶ����ͷ����������ʱ������

out vec4 varyingColor;

mat4 buildRotateX(float rad);//glslҪ���������������
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void){
	float i = gl_InstanceID + time_factor;//ȡֵ����ʱ�����ӣ����Ƕ���ÿ���������ǲ�ͬ��
	float a = sin(203.0 * i / 8000.0) * 403.0;//ƽ���õ�x,y,x����
	float b = sin(301.0 * i / 4001.0) * 401.0;
	float c = sin(400.0 * i / 6003.0) * 405.0;

	//������ת��ƽ�ƾ��󣬽���Ӧ���ڵ�ǰ������
	mat4 localRotX = buildRotateX(1000 * i);
	mat4 localRotY = buildRotateY(1000 * i);
	mat4 localRotZ = buildRotateZ(1000 * i);
	mat4 localTrans = buildTranslate(a, b, c);

	//����ģ�;���Ȼ����ģ��-��ͼ����
	mat4 newM_matrix = m_matrix * localTrans * localRotX * localRotY * localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

//����ƽ�ƾ���Ĺ��ߺ���
mat4 buildTranslate(float x, float y, float z){
mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,//���ǵ�һ�У����ǵ�һ��
				  0.0, 1.0, 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  x, y,z, 1.0);
	return trans;
}

//������������X����ת�ľ���
mat4 buildRotateX(float rad){
mat4 rotx = mat4(1.0, 0.0, 0.0, 0.0,//���ǵ�һ�У����ǵ�һ��
				  0.0, cos(rad), -sin(rad), 0.0,
				  0.0, sin(rad), cos(rad), 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return rotx;
}

//������������Y����ת�ľ���
mat4 buildRotateY(float rad){
mat4 roty = mat4(cos(rad), 0.0, sin(rad), 0.0,//���ǵ�һ�У����ǵ�һ��
				  0.0, 1.0, 0.0, 0.0,
				  -sin(rad), 0.0, cos(rad), 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return roty;
}

//������������Z����ת�ľ���
mat4 buildRotateZ(float rad){
mat4 rotz = mat4(cos(rad), -sin(rad), 0.0, 0.0,//���ǵ�һ�У����ǵ�һ��
				  sin(rad), cos(rad), 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  0.0, 0.0, 0.0, 1.0);
	return rotz;
}