#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textcoord;

// out vec3 fragment_normal;
// out vec3 fragment_position;
out vec2 fragment_textcoord;

void main()
{
    // gl_Position = World2Camera * Model2World * vec4(position, 1.0);

    // mat4 Model2WorldTI = transpose(inverse(Model2World));

    // fragment_normal = (Model2WorldTI * vec4(normal,0.0)).xyz;
    // fragment_position = (Model2World * vec4(position,1.0)).xyz;
    fragment_textcoord = textcoord;
}