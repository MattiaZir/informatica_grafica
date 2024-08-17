#version 330

// struct AmbientLightStruct {
// 	vec3 color;
// 	float intensity;
// };

// struct DiffusiveLightStruct {
// 	vec3 color;
// 	vec3 direction;
// 	float intensity;
// };

// struct SpecularLightStruct {
// 	float intensity;
// 	float shininess;
// };

// // Vettori della normali ricevuti dal vertex shader
// in vec3 fragment_normal;

// // Coordinate spaziali dei punti ricervuti dal vertex shader
// in vec3 fragment_position;

// // Coordinate di texture dei punti ricervuti dal vertex shader
// in vec2 fragment_textcoord;

// // Informazioni di luce ambientale
// uniform AmbientLightStruct AmbientLight;

// // Informazioni di luce diffusiva
// uniform DiffusiveLightStruct DiffusiveLight;

// // Informazioni di luce speculare
// uniform SpecularLightStruct SpecularLight;

// // Posizione della camera in coordinate mondo
// uniform vec3 CameraPosition;

// uniform sampler2D TextSampler;

out vec4 out_color;

void main()
{
	// La funzione texture ritorna un vec4.

	out_color = vec4(0,255,0,0);
}