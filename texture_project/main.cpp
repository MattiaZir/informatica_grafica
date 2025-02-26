#include <iostream>
#include <sstream>
#include "GL/glew.h" // prima di freeglut
#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include "transform.h"
#include "camera.h"

#include "cube.h"
#include "myshaderclass.h"

#include "mesh.h"

MyShaderClass myshaders;
//PerlinNoiseShader perlinshaders;
Cube cube;

unsigned char MODEL_TO_RENDER = 'c';

GLuint perlin_texture_id;


/**
  Struttura di comodo dove sono memorizzate tutte le variabili globali
*/
struct global_struct {

  int WINDOW_WIDTH  = 1024; // Larghezza della finestra
  int WINDOW_HEIGHT = 768; // Altezza della finestra

  Camera camera;

  AmbientLight   ambient_light;
  DiffusiveLight diffusive_light;
  SpecularLight  specular_light;

  const float SPEED = 1;
  float gradX;
  float gradY;

  global_struct() : gradX(0.0f), gradY(0.0f) {}

} global;


struct perlin_params {
  int width = 512;
  int height = 512;
  int octaves = 1;
  int grid_size = 100;
  float contrast = 1.0;

  int GRID_MODIFIER = 10;
  int SIZE_MODIFIER = 256;
  float CONTRAST_MODIFIER = 0.1;

} perlin_params;



/**
Prototipi della nostre funzioni di callback.
Sono definite più avanti nel codice.
*/
void MyRenderScene(void);
void MyIdle(void);
void MyKeyboard(unsigned char key, int x, int y);
void MyClose(void);
void MySpecialKeyboard(int Key, int x, int y);
void MyMouse(int x, int y);

void init(int argc, char*argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);


  glutInitWindowSize(global.WINDOW_WIDTH, global.WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Informatica Grafica");

/*
  // Imposta la modalità a schemo intero e nasconde il cursore
  std::stringstream game_mode;
  game_mode << global.WINDOW_WIDTH << "x" << global.WINDOW_HEIGHT << ":32";
  glutGameModeString(game_mode.str().c_str());
  glutEnterGameMode();
*/
  glutSetCursor(GLUT_CURSOR_NONE);

  global.camera.set_mouse_init_position(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);
  global.camera.lock_mouse_position(true);
  glutWarpPointer(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);

 // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK) {
      std::cerr<<"Error : "<<glewGetErrorString(res)<<std::endl;
    exit(1);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glutDisplayFunc(MyRenderScene);

  glutKeyboardFunc(MyKeyboard);

  glutCloseFunc(MyClose);

  glutSpecialFunc(MySpecialKeyboard);

  glutPassiveMotionFunc(MyMouse);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);
}

void create_scene() {
  global.camera.set_camera(
          glm::vec3(0, 0, 0),
          glm::vec3(0, 0,-1),
          glm::vec3(0, 1, 0)
      );

  global.camera.set_perspective(
    30.0f,
    global.WINDOW_WIDTH,
    global.WINDOW_HEIGHT,
    0.1,
    100
  );

  global.ambient_light = AmbientLight(glm::vec3(1,1,1),0.2);
  global.diffusive_light = DiffusiveLight(glm::vec3(1,1,1),glm::vec3(0,0,-1),0.5); // 0.5
  global.specular_light = SpecularLight(0.5,30);

  myshaders.init();
  //perlinshaders.init();
  // myshaders.enable();
  // myshaders.set_sampler(0);

}


void render_cube() {
  LocalTransform modelT;
  modelT.rotate(global.gradX, global.gradY, 0.0f);
  modelT.translate(0,0,-5);

  myshaders.set_model_transform(modelT.T());
  myshaders.set_camera_transform(global.camera.CP());
  myshaders.set_ambient_light(global.ambient_light);
  myshaders.set_diffusive_light(global.diffusive_light);
  myshaders.set_specular_light(global.specular_light);
  myshaders.set_camera_position(global.camera.position());
  cube.shaders(myshaders);

  // if (perlin_texture_id)
  // {
  //   cube.swap_textures(perlin_texture_id);
  // }


  cube.render();
}

void MyRenderScene() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  switch (MODEL_TO_RENDER) {
    case 'c': render_cube(); break;
    case 'r':
      cube.generate_perlin_noise(
        perlin_params.width,
        perlin_params.height,
        perlin_params.octaves,
        perlin_params.grid_size,
        perlin_params.contrast);
      MODEL_TO_RENDER = 'c'; break;
  }

  glutSwapBuffers();
  glutPostRedisplay();
}

// Funzione globale che si occupa di gestire l'input da tastiera.
void MyKeyboard(unsigned char key, int x, int y) {
  switch ( key )
  {
    // case 'a':
    //   global.gradY -= global.SPEED;
    // break;
    // case 'd':
    //   global.gradY += global.SPEED;
    // break;
    // case 'w':
    //   global.gradX -= global.SPEED;
    // break;
    // case 's':
    //   global.gradX += global.SPEED;
    // break;

    case 27: // Escape key
      glutDestroyWindow(glutGetWindow());
      return;
    break;

    case 'w':
      global.diffusive_light.direction(global.diffusive_light.direction() + glm::vec3(0,0.05,0));
    break;

    case 's':
      global.diffusive_light.direction(global.diffusive_light.direction() - glm::vec3(0,0.05,0));
    break;

    case 'a':
      global.diffusive_light.direction(global.diffusive_light.direction() - glm::vec3(0.05,0,0));
    break;

    case 'd':
      global.diffusive_light.direction(global.diffusive_light.direction() + glm::vec3(0.05,0,0));
    break;

    case 'q':
      global.diffusive_light.direction(global.diffusive_light.direction() - glm::vec3(0,0,0.05));
    break;

    case 'e':
      global.diffusive_light.direction(global.diffusive_light.direction() + glm::vec3(0,0,0.05));
    break;

    // Variamo l'intensità di luce ambientale
    case '1':
      global.ambient_light.dec(0.05);
    break;

    // Variamo l'intensità di luce ambientale
    case '2':
      global.ambient_light.inc(0.05);
    break;

    // Variamo l'intensità di luce diffusiva
    case '3':
      global.diffusive_light.dec(0.05);
    break;

    // Variamo l'intensità di luce diffusiva
    case '4':
      global.diffusive_light.inc(0.05);
    break;

    // Variamo l'intensità di luce speculare
    case '5':
      global.specular_light.dec(0.05);
    break;

    // Variamo l'intensità di luce speculare
    case '6':
      global.specular_light.inc(0.05);
    break;

    // Variamo l'esponente della luce speculare
    case '7':
      global.specular_light.dec_shine(1);
    break;

    // Variamo l'esponente della luce speculare
    case '8':
      global.specular_light.inc_shine(1);
    break;

    case 'o':
      perlin_params.width += perlin_params.SIZE_MODIFIER;
      perlin_params.height += perlin_params.SIZE_MODIFIER;
      MODEL_TO_RENDER = 'r';
    break;

    case 'l':
      perlin_params.width = std::max(perlin_params.SIZE_MODIFIER, perlin_params.width - perlin_params.SIZE_MODIFIER);
      perlin_params.height = std::max(perlin_params.SIZE_MODIFIER, perlin_params.width - perlin_params.SIZE_MODIFIER);
      MODEL_TO_RENDER = 'r';
    break;

    case 'i':
      perlin_params.grid_size += perlin_params.GRID_MODIFIER;
      MODEL_TO_RENDER = 'r';
    break;

    case 'k':
      perlin_params.grid_size = std::max(perlin_params.GRID_MODIFIER, perlin_params.grid_size - perlin_params.GRID_MODIFIER);
      MODEL_TO_RENDER = 'r';
    break;

    case 'f':
      global.gradY -= global.SPEED;
    break;
    case 'h':
      global.gradY += global.SPEED;
    break;
    case 't':
      global.gradX -= global.SPEED;
    break;
    case 'g':
      global.gradX += global.SPEED;
    break;

    case 'z':
      perlin_params.contrast = std::max(0.1f, perlin_params.contrast - perlin_params.CONTRAST_MODIFIER);
      MODEL_TO_RENDER = 'r';
    break;
    case 'x':
      perlin_params.contrast += perlin_params.CONTRAST_MODIFIER;
      MODEL_TO_RENDER = 'r';
    break;

    case ' ': // Reimpostiamo la camera
      global.camera.set_camera(
          glm::vec3(0, 0, 0),
          glm::vec3(0, 0,-1),
          glm::vec3(0, 1, 0)
      );
    break;

    case 'c':
    MODEL_TO_RENDER = key;
    break;
    case 'r':
    MODEL_TO_RENDER = key;
    break;
  }

  glutPostRedisplay();
}

void MySpecialKeyboard(int Key, int x, int y) {
  switch (Key) {
    case GLUT_KEY_PAGE_UP:
      perlin_params.octaves++;
      MODEL_TO_RENDER = 'r';
    break;

    case GLUT_KEY_PAGE_DOWN:
      perlin_params.octaves = std::max(1, perlin_params.octaves - 1);
      MODEL_TO_RENDER = 'r';
    break;

    default:
    global.camera.onSpecialKeyboard(Key);
    break;
  }

  glutPostRedisplay();
}

void MyMouse(int x, int y) {
  if (global.camera.onMouse(x,y)) {
    // Risposto il mouse al centro della finestra
    glutWarpPointer(global.WINDOW_WIDTH/2, global.WINDOW_HEIGHT/2);
  }
  glutPostRedisplay();
}

// Funzione globale che si occupa di gestire la chiusura della finestra.
void MyClose(void) {
  std::cout << "Tearing down the system..." << std::endl;
  // Clean up here

  // A schermo intero dobbiamo uccidere l'applicazione.
  exit(0);
}

void MyIdle(void) {
  glutPostRedisplay();
}

int main(int argc, char* argv[])
{
  init(argc,argv);

  create_scene();

  glutMainLoop();

  return 0;
}