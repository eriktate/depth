#version 330 core
in vec3 vertex_color;
in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	vec2 flip_tex = tex_coord;
	flip_tex.x *= -1;
	frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	frag_color = vec4(vertex_color, 1.0);
	frag_color = texture(texture1, tex_coord) * vec4(vertex_color, 1.0);
	frag_color = mix(texture(texture1, tex_coord).rgba, texture(texture2, flip_tex).rgba, vec4(texture(texture2, tex_coord)).a * 0.2);
	frag_color = texture(texture2, tex_coord);
}
