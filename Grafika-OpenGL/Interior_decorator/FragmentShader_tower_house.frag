#version 330 core

// Interpolated values from the vertex shaders
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec2 TexCoords;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
uniform sampler2D texture_diffuse1; // CHANGED 23092016
uniform vec3 shine;

void main(){

	// Light emission properties
	// Might come in handy putting them as uniform
	vec4 LightColor = vec4(0.9921,0.7215,0.0745,0.8);
	vec4 WhiteLight = vec4(1,1,1,0.8);
	float LightPower = 150.0f;
	
	// Material properties
	vec4 MaterialDiffuseColor = vec4(texture( texture_diffuse1, TexCoords ));
	vec4 MaterialAmbientColor = vec4(0.3,0.3,0.3,0) * MaterialDiffuseColor;
	vec4 MaterialSpecularColor = vec4(0.3,0.3,0.3,0);

	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color =  vec4(shine,0) * MaterialDiffuseColor + vec4(shine,0) * pow(cosTheta,3) + vec4(shine,0) * pow(cosAlpha,60) +
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		0.6 * MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,60) / (distance*distance)+
		// Linear Specular light color
		0.015 * MaterialSpecularColor * WhiteLight * LightPower * pow(cosAlpha,5) / (distance/20) + 
		//White Diffusion
		WhiteLight * MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance)
		;
}