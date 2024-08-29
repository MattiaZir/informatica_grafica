#ifndef CUBE_H
#define CUBE_H

#include <string>
#include "GL/glew.h" // prima di freeglut
#include "texture.h"
#include "myshaderclass.h"

class Cube {
public:

  /**
    Costruttore
  */
  Cube();

  /**
    Renderizza l'oggetto. Se necessario, l'oggetto viene prima inizializzato
    chiamando la init().
  */
  void render(void);

  bool shaders(MyShaderClass &shader);
  MyShaderClass &shaders();

  void swap_textures(int texture_id);

  void generate_perlin_noise();
 private:
  GLuint _VAO;       // Vertex Array Object
  Texture _texture;  // Texture
  bool _initialized; // Oggetto usabile?

  MyShaderClass _shaders; // Shaders da usare con Cube


  /**
    Inizializzazione degli oggetti OpenGL. E' fatta in un secondo tempo
    poichè è necessario avere inizializzato GLUT prima di qualunque
    uso delle funzioni di OpenGL. La init è chiamata, se necessario,
    dalla render().
  */
  void init(void);

  glm::vec3 perlin_noise_to_color(float value);
  glm::vec2 randomGradient(int ix, int iy);
  float dotGridGradient(int ix, int iy, float x, float y);
  float interpolate(float a0, float a1, float w);
  float perlin(float x, float y);

  // Blocchiamo le operazioni di copia di una istanza di Cube:
  // non possiamo condividere un VAO
  Cube&operator=(const Cube &other);
  Cube(const Cube &other);

};

#endif