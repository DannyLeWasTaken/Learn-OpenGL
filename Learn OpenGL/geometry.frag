#version 330
out vec4 FragColor;
in vec3 fColor;

void main () {
    FragColor = vec4(fColor, 0.0);
}