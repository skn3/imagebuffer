// simple fragment shader
 
// 'time' contains seconds since the program was linked.
uniform float time;
 
uniform sampler2D tex;
uniform sampler2D tex2;
 
float radius = .5;
 
void main()
{
	float t = clamp(time / 6., 0., 1.);
 
	vec2 coords = gl_TexCoord[0].st;
	vec2 dir = coords - vec2(.5);
	
	float dist = distance(coords, vec2(.5));
	vec2 offset = dir * (sin(dist * 80. - time*15.) + .5) / 30.;
 
	vec2 texCoord = coords + offset;
	vec4 diffuse = texture2D(tex, texCoord);
 
	vec4 mixin = texture2D(tex2, texCoord);
 
 	gl_FragColor = mixin * t + diffuse * (1. - t);
}