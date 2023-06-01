#version 150
// Based on Gaussian Blur shader made by ThinMatrix

const int radius = 2;

in vec2 position;
out vec2 blur_coords[radius*2 + 1];
uniform float height;

void main(void){
	gl_Position = vec4(position * 2.0 - 1, 0.0, 1.0);
	for(int i = -radius; i <= radius; i++) {
		blur_coords[i+radius] = position + vec2(0.0, (1.0 / height) * i);
	}
}
