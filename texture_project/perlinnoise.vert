#version 330

in layout(location = 0) vec2 aPos;
in layout(location = 1) vec2 aTexPos;

// out vec3 fragment_normal;
// out vec3 fragment_position;
// out vec3 fragColor;

void main()
{
    // gl_Position = World2Camera * Model2World * vec4(position, 1.0);

    // mat4 Model2WorldTI = transpose(inverse(Model2World));

    // fragment_normal = (Model2WorldTI * vec4(normal,0.0)).xyz;
    // fragment_position = (Model2World * vec4(position,1.0)).xyz;
    gl_Position = vec4(aPos,0.0, 1.0);
}