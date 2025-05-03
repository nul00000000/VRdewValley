#version 400 core

in vec3 colorPass;
in vec3 pNormal;
in vec3 fragPos;

out vec4 fragColor;

void main(void) {
    fragColor = vec4(0, 1, 0, 1);
}
