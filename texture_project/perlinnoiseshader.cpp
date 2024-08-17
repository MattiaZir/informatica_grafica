#include "perlinnoiseshader.h"

void PerlinNoiseShader::set_model_transform(const glm::mat4 &transform)
{
    // setta la matrice di trasformazione nel vertex shader
    glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}

void PerlinNoiseShader::set_camera_transform(const glm::mat4 &transform)
{
    // setta la matrice di trasformazione della camera nel vertex shader
    glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));
}

void PerlinNoiseShader::set_camera_position(const glm::vec3 &pos)
{
    // setta la posizione della camera nel vertex shader
    glUniform3fv(_camera_position_location, 1, const_cast<float *>(&pos[0]));
}

bool PerlinNoiseShader::load_shaders()
{
        return  add_shader(GL_VERTEX_SHADER,"perlinnoise.vert") &&
                add_shader(GL_FRAGMENT_SHADER,"perlinnoise.frag");
}

bool PerlinNoiseShader::load_done()
{
    _model_transform_location = get_uniform_location("Model2World");
    _camera_transform_location = get_uniform_location("World2Camera");
    _camera_transform_location = get_uniform_location("World2Camera");

    return  (_model_transform_location != INVALID_UNIFORM_LOCATION) &&
            (_camera_transform_location != INVALID_UNIFORM_LOCATION);
}