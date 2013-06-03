#define M_PI 3.14159265358979323846
uniform int testing123 = 999;
const mat2 rotation = mat2( cos(M_PI/4.0), sin(M_PI/4.0),-sin(M_PI/4.0), cos(M_PI/4.0));
	
void main(void) {
	vec2 pos = mod(rotation * gl_FragCoord.xy, vec2(50.0)) - vec2(25.0);
	float dist_squared = dot(pos, pos);

	if (testing123 == 999 || testing123 == 123) {
		gl_FragColor = mix(vec4(.90, .90, .90, 1.0), vec4(.20, .20, .40, 1.0),smoothstep(380.25, 420.25, dist_squared));
	}
	
	gl_FragColor = mix(vec4(.90, .90, .90, 1.0), vec4(.20, .20, .40, 1.0),smoothstep(380.25, 420.25, dist_squared));
}
