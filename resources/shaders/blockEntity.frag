#version 430 core
#extension GL_ARB_bindless_texture: require

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 position;
layout (location = 2) out ivec3 out_normals;
layout (location = 3) out vec3 out_bloom;
layout (location = 4) out float out_materials; //just roughness for now


in vec2 v_uv;
in flat int v_id;
in vec3 v_vertexPosition;
in vec3 v_normals;


uniform sampler2D u_texture[6];
uniform mat4 u_view;

uniform float u_exposure;
flat in float v_ambient;


ivec3 fromFloatTouShort(vec3 a)
{
	//[-1 1] -> [0 2]
	a += 1.f;

	//[0 2] -> [0 1]
	a /= 2.f;

	//[0 1] -> [0 65536]
	a *= 65536;

	return ivec3(a);
}



void main()
{

	color = texture(u_texture[v_id/6], v_uv).rgba;
	if(color.a <= 0){discard;}

	color.rgb = pow(color.rgb, vec3(2.2));
	//color.rgb *= 0.7f;
	color.rgb *= v_ambient;
	

	position.xyz = (u_view * vec4(v_vertexPosition,1)).xyz;
	out_normals = fromFloatTouShort(v_normals);
	out_bloom = vec3(0,0,0);
	out_materials.r = 0.9;
}