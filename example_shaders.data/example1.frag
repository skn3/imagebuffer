#define M_PI .0//3.14159265358979323846
uniform float angle;

void main(void) {
	//mat2 rotation = mat2( cos(M_PI/4.0), sin(M_PI/4.0),-sin(M_PI/4.0), cos(M_PI/4.0));
	mat2 rotation = mat2( cos(angle/4.0), sin(angle/4.0),-sin(angle/4.0), cos(angle/4.0));
	vec2 pos = mod(rotation * gl_FragCoord.xy, vec2(50.0)) - vec2(25.0);
	float dist_squared = dot(pos, pos);
	
	gl_FragColor = mix(vec4(.90, .90, .90, 1.0), vec4(.20, .20, .40, 1.0),smoothstep(380.25, 420.25, dist_squared));
}
