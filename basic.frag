#version 460 core
in vec3 zColor;
out vec4 FragColor;
void main()
{
	FragColor = vec4(zColor, 1.0);
}