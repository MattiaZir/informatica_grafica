#include "perlinnoiseshader.h"

struct Vertex {
    glm::vec3 position; ///< Coordinate spaziali
    glm::vec3 normal;   ///< Normale
    glm::vec2 textcoord;///< Coordinate di texture

    Vertex(
      float x, float y, float z,
      float xn, float yn, float zn,
      float s, float t) {

      position = glm::vec3(x,y,z);
      normal = glm::vec3(xn,yn,zn);
      textcoord = glm::vec2(s,t);
    }

    Vertex(const glm::vec3 &xyz, const glm::vec3 &norm, const glm::vec2 &txt)
      : position(xyz), normal(norm), textcoord(txt) {}
};

// void PerlinNoiseShader::set_model_transform(const glm::mat4 &transform)
// {
//     // setta la matrice di trasformazione nel vertex shader
//     glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
// }

// void PerlinNoiseShader::set_camera_transform(const glm::mat4 &transform)
// {
//     // setta la matrice di trasformazione della camera nel vertex shader
//     glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
// }

// void PerlinNoiseShader::set_camera_position(const glm::vec3 &pos)
// {
//     // setta la posizione della camera nel vertex shader
//     glUniform3fv(_camera_position_location, 1, const_cast<float *>(&pos[0]));
// }

bool PerlinNoiseShader::load_shaders()
{
        return  add_shader(GL_VERTEX_SHADER,"perlinnoise.vert") &&
                add_shader(GL_FRAGMENT_SHADER,"perlinnoise.frag");
}

bool PerlinNoiseShader::load_done()
{
    // _model_transform_location = get_uniform_location("Model2World");
    // _camera_transform_location = get_uniform_location("World2Camera");
    // _camera_transform_location = get_uniform_location("World2Camera");

    // return  (_model_transform_location != INVALID_UNIFORM_LOCATION) &&
    //         (_camera_transform_location != INVALID_UNIFORM_LOCATION);

    return true;
}

void PerlinNoiseShader::install_shaders()
{
}

GLuint PerlinNoiseShader::generate_perlin_texture()
{
    GLfloat vertices[] =
    {
    //  X       Y       R      G     B
        +1.0f, -1.0f, +0.5f, +0.1f, +0.1f,
        +1.0f, +1.0f, +0.3f, +0.5f, +0.5f,
        -1.0f, +1.0f, +0.0f, +0.4f, +0.0f,
        -1.0f, -1.0f, +0.0f, +0.3f, +0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char*) (2 * sizeof(float)));

    init();
    enable();

    GLushort indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glViewport(0, 0, 1024, 1024);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void PerlinNoiseShader::texture(GLuint texture) {
    _perlin_noise_texture = texture;
}

int PerlinNoiseShader::texture() {
    return _perlin_noise_texture;
}
