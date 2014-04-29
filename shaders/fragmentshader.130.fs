#version 130
#extension GL_ARB_explicit_attrib_location : enable

in vec4 vColor;

out vec4 FragColor;

void main()
{
    FragColor = vColor;
}