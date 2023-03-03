#version 430
in vec2 tc;//插值过的材质纹理坐标
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D samp;//采样器变量，指定其与纹理单元0相关联
void main(void){color = texture(samp, tc);
}