#include "cube.h"
#include "glm/glm.hpp"

#include <iostream>
  /**
    Struttura dati che contiene gli attributi di un vertice.
  */
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


Cube::Cube() : _initialized(false) {}


void Cube::init(void) {

  if (!_shaders.init()) {
    std::cerr << "Error initializing shaders..." << std::endl;
    exit(0);
  }

  _texture.load("sagm.jpg");

  Vertex Vertices[] = {
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1,0)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0,1)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0,0)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0,1)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1,0)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1,1)),

    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0,0)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1,0)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1,1)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1,1)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0,1)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0,0)),

    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1,1)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0,0)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0,0)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1,1)),

    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1,1)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0,0)),

    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0,0)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1,1)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1,1)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0,0)),

    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1,1)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1,0)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0,1)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0,0))
  };

  glGenVertexArrays(1, &(_VAO));
  glBindVertexArray(_VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    reinterpret_cast<GLvoid*>(offsetof(struct Vertex, position)));

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    reinterpret_cast<GLvoid*>(offsetof(struct Vertex, normal)));

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    reinterpret_cast<GLvoid*>(offsetof(struct Vertex, textcoord)));

  _initialized = true;
}

void Cube::render(void) {

  if (!_initialized)
    init();

  _shaders.enable();

  glBindVertexArray(_VAO);

  //_shaders.set_sampler(0);

  _texture.bind(0);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}

bool Cube::shaders(MyShaderClass &shader) {
  _shaders = shader;

  //_shaders.init();

  return true;
}

MyShaderClass &Cube::shaders() {
  return _shaders;
}

void Cube::swap_textures(int texture_id) {
  _texture.setTextureID(texture_id);
}

void Cube::generate_perlin_noise() {
  int width = 32, height = 32;
  unsigned char* imageData = (unsigned char*) malloc(width * height * 4 * sizeof(unsigned char));

  const int OCTAVES = 8;
  const int GRID_SIZE = 4; // Frequenza base del perlin noise

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      int index = (y * width + x) * 4;

      float value = 0;
      float frequency = 1;
      float amplitude = 1;

      for (int i = 0; i < OCTAVES; i++)
      {
        value += perlin(x * frequency / GRID_SIZE, y * frequency / GRID_SIZE) * amplitude;

        frequency *= 2;
        amplitude /= 2;
      }

      // contrasto
      value *= 1.2f;

      //clipping
      if (value > 1.0f)
        value = 1.0f;
      else if (value < -1.0f)
        value = -1.0f;

      // convert from clamped values to 0-255 range
      int color = (int) (((value + 1.0f) * 0.5f) *255);

      imageData[index] = color;
      imageData[index + 1] = color;
      imageData[index + 2] = color;
      imageData[index + 3] = 255;
    }
  }

  _texture.load(imageData, width, height, GL_RGBA);
}

// TODO: Sposta in una classe a parte.

glm::vec2 Cube::randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    glm::vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float Cube::dotGridGradient(int ix, int iy, float x, float y)
{
  glm::vec2 gradient = randomGradient(ix, iy);

  // calcolo del vettore distanza
  float dx = x - (float) ix;
  float dy = y - (float) iy;

  return (dx * gradient.x + dy * gradient.y);
}

float Cube::interpolate(float a0, float a1, float weight)
{
  // Cubic Interpolation formula
  return (a1 - a0) * (3.0 - weight * 2.0) * weight * weight + a0;
}

float Cube::perlin(float x, float y)
{
  // Angolo della cella e angolo opposto
  int x0 = (int) x;
  int y0 = (int) y;
  int x1 = x0 + 1;
  int y1 = y0 + 1;

  // distanza punto-angolo
  float sx = x - (float) x0;
  float sy = y - (float) y0;

  // Calcolo del gradiente degli angoli superiori
  float n0 =  dotGridGradient(x0, y0, x, y);
  float n1 =  dotGridGradient(x1, y0, x, y);
  float ix0 = interpolate(n0, n1, sx);

  // Calcolo gradienti angoli inferiori
  n0 =  dotGridGradient(x0, y1, x, y);
  n1 =  dotGridGradient(x1, y1, x, y);
  float ix1 = interpolate(n0, n1, sx);

  // interpola tra le due x ma in y
  float value = interpolate(ix0, ix1, sy);

  return value;
}