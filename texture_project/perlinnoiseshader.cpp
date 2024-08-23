#include "perlinnoiseshader.h"
#include <iostream>

struct Vertex {
    glm::vec2 position; ///< Coordinate spaziali
    glm::vec2 textcoord;///< Coordinate di texture

    Vertex(
      float x, float y,
      float s, float t) {

      position = glm::vec2(x,y);
      textcoord = glm::vec2(s,t);
    }

    Vertex(const glm::vec2 &xy, const glm::vec2 &txt)
      : position(xy), textcoord(txt) {}
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

    #pragma region framebuffer setup
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    #pragma endregion

    #pragma region texture setup
    GLuint texture_color_buffer;
    glGenTextures(1, &texture_color_buffer);
    glBindTexture(GL_TEXTURE_2D, texture_color_buffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach texture to fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_color_buffer, 0);
    #pragma endregion

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    #pragma region Quad Setup
    Vertex vertices[] =
    {
        // how should texture coords be handled?
        Vertex(glm::vec2(+1.0f, -1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec2(+1.0f, +1.0f), glm::vec2(1.0f,1.0f)),
        Vertex(glm::vec2(-1.0f, +1.0f), glm::vec2(0.0f,1.0f)),
        Vertex(glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f,0.0f)),
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (char*) (2 * sizeof(float)));
    #pragma endregion

    #pragma region Shader Noise setup
    init();
    enable();

    int resolutionLocation = get_uniform_location("u_resolution");
    glUniform2f(resolutionLocation, 1024, 1024);

    #pragma endregion

    #pragma region draw
    GLushort indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, 1024, 1024);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1024, 768);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    #pragma endregion

      GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }

    return texture_color_buffer;
}

void PerlinNoiseShader::texture(GLuint texture) {
    _perlin_noise_texture = texture;
}

int PerlinNoiseShader::texture() {
    return _perlin_noise_texture;
}
