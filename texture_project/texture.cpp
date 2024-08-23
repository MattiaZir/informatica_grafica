#include "texture.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Libreria di suporto per leggere immagini

Texture::Texture() : _texture(-1), _target(GL_TEXTURE_2D), _valid(false) {}

Texture::~Texture() {
  clear();
}


void Texture::clear() {
  if (is_valid()) {
    glDeleteTextures(1, &_texture);
    _texture = -1;
    _valid = false;
  }
}

bool Texture::load(const std::string& FileName) {
  int width, height, channels;
  unsigned char *image = nullptr;
  GLint format;

  clear();

  stbi_set_flip_vertically_on_load(true);

  // Usa la libreria lodepng per caricare l'immagine png
  image = stbi_load(FileName.c_str(), &width, &height, &channels, 0);

  if (channels == 3) {
    format = GL_RGB;
  }
  else if (channels == 4) {
    format = GL_RGBA;
  }
  else return false;

  //std::cout<<channels<<std::endl;

  if (image==nullptr) {
    std::cerr<<" Failed to load texture " << FileName << std::endl;
    exit(0);
  }

  load(image, width, height, format);

  stbi_image_free(image);

  _filename = FileName;

  return true;
}

bool Texture::load(const unsigned char* image, int width, int height, int format)
{
  // Crea un oggetto Texture in OpenGL
  glGenTextures(1, &_texture);

  // Collega la texture al target specifico (tipo)
  glBindTexture(_target,_texture);

  // Passa le informazioni dell'immagine sulla GPU:
  // Target
  // Numero di livelli del mipmap (0 in questo caso)
  // Formato della texture
  // Larghezza
  // Altezza
  // 0
  // Formato dei pixel dell'immagine di input
  // Tipo di dati dei pixel dell'immagine di input
  // Puntatore ai dati

  // unsigned char* imageData = (unsigned char*)malloc(20000 * 20000 * 3 * sizeof(unsigned char));

  // for (int i = 0; i < width * height * 3; i += 3) {
  //     imageData[i] = rand()*255;      // Red
  //     imageData[i + 1] = rand()*255;  // Green
  //     imageData[i + 2] = rand()*255;  // Blue
  // }

  glTexImage2D(_target, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, image);

  // Imposta il filtro da usare per la texture minification
  glTexParameterf(_target, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);

  // Imposta il filtro da usare per la texture magnification
  glTexParameterf(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbinda la texture
  glBindTexture(_target,0);

  _valid = true;

  return true;
}

void Texture::setTextureID(GLuint textureID) {
    // Ensure the texture ID is valid and update the class members
    if (textureID > 0) {
        _texture = textureID;
        _valid = true;
    } else {
        _texture = -1;
        _valid = false;
    }
}


void Texture::bind(int TextureUnit) const {
  GLenum unit = GL_TEXTURE0 + TextureUnit;

  // Attiviamo la TextureUnit da usare per il sampling
  glActiveTexture(unit);

  // Bindiamo la texture
  glBindTexture(_target, _texture);
}

bool Texture::is_valid(void) const {
  return _valid;
}