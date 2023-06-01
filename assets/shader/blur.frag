#version 150
// Based on Gaussian Blur shader made by ThinMatrix

const int radius = 2;

out vec4 out_color;
in vec2 blur_coords[radius*2 + 1];
uniform sampler2D tex;

void main(void) {
	out_color = vec4(0.0);

	for(int i = 0; i < (radius*2 + 1); ++i) {
		out_color += vec4(texture2D(tex, blur_coords[i])) / float(radius*2 + 1);
	}
}