#ifndef PERLINNOISESHADER_H
#define PERLINNOISESHADER_H

#include "shaderclass.h"
#include "light.h"

/**
 * Classe shader per l'implementazione del perlin noise
 */
class PerlinNoiseShader : public ShaderClass {
public:
    // void set_model_transform(const glm::mat4 &transform);
    // void set_camera_transform(const glm::mat4 &transform);
    // void set_camera_position(const glm::vec3 &pos);

    bool load_shaders();
    bool load_done();

    void install_shaders();

    GLuint generate_perlin_texture();

    void texture(GLuint texture);
    int texture();

   private:
    // GLint _model_transform_location;
    // GLint _camera_transform_location;
    // GLint _camera_position_location;
    GLuint _perlin_noise_texture;
};

#endif // PERLINNOISESHADER_H