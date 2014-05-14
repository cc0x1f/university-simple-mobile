#version 330

in vec4 vColor;
out vec4 FragColor;

struct DirectionalLight
{
  vec3 color;
  float ambientIntensity;
};
uniform DirectionalLight gDirectionalLight;

void main()
{
  FragColor = vColor * vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.ambientIntensity;
}