#include "globals.h"

#include "meshes/Skybox.h"
#include "meshes/Cloud.h"
#include "meshes/Water.h"
#include "meshes/Terrain.h"
#include "meshes/Mirror.h"
#include "meshes/TerrainShadow.h"
#include "meshes/Displacement.h"
#include "meshes/Blur.h"
#include "meshes/Bloom.h"
#include "threecpp/Lights.h"
#include "threecpp/Window.h"

inline void createView(Window* window, Scene* scene, BufferCamera* camera, BufferCamera* gBufferCamera){

  /* HEIGHT MAP: START */
  Scene* heightmap = new Scene();
  Displacement* displacement = new Displacement();
  if (DEBUG == DEBUG_HEIGHTMAP) {
    printf("=====> Render: Displacement => Scene\n");
    scene->add(displacement);
  }
  else {
    printf("=====> Render: Displacement => Heightmap\n");
    heightmap->add(displacement);
  }
  /* HEIGHT MAP: END */


  /* LIGHT: START */
  PointLight* light = new PointLight("globalLight");

  light->lookAt = LIGHT_LOOK;
  light->up = LIGHT_UP;
  light->position = LIGHT_POS;
  // light->update();
  // light->translate(LIGHT_POS[0], LIGHT_POS[1], LIGHT_POS[2]);
  // light->translate(0, 60, 60);

  // light->translate(0.0, 20.0, 0.0);
  // light->rotateX(0.25*M_PI);

  // if (DEBUG == DEBUG_TERRAIN ||!DEBUG){
  printf("=====> Render: PointLight => Scene\n");
  scene->add(light);
  //}
  /* LIGHT: END */


  /* TERRAIN SHADOW: START */
  Scene* shadowmap = new Scene();
  TerrainShadow* shadow = new TerrainShadow(camera, light);
  shadow->translate(0.0, -5.0, 0.0);
  shadow->scale(200);
  heightmap->add(shadow->heightMapBuffer);
  window->registerBuffer(shadow->heightMapBuffer);

  if (DEBUG == DEBUG_SHADOWMAP) {
    printf("=====> Render: TerrainShadow => Scene\n");
    //scene->add(shadow);
  }
  else {
    printf("=====> Render: TerrainShadow => Shadowmap\n");
    shadowmap->add(shadow);
  }
  /* TERRAIN SHADOW: END */


  /* TERRAIN: START */

  Terrain* terrain = new Terrain(camera);
  terrain->translate(0.0, -5.0, 0.0);
  terrain->scale(200);

  if (DEBUG == DEBUG_TERRAIN || !DEBUG){
    printf("=====> Buffer: Heightmap => Terrain::heightMapBuffer\n");
    heightmap->add(terrain->heightMapBuffer);
    window->registerBuffer(terrain->heightMapBuffer);
    //printf("=====> Buffer: Shadowmap => Terrain::shadowMapBuffer\n");
    shadowmap->add(terrain->shadowMapBuffer);
	window->registerBuffer(terrain->shadowMapBuffer);
     window->registerCamera(terrain->shadowMapBuffer);
    //printf("=====> Render: Terrain => Scene\n");
   // scene->add(terrain);
  }

  shadow->heightMapBuffer = terrain->heightMapBuffer;

  Skybox* skybox = new Skybox();
  skybox->scale(200);
  if (DEBUG == DEBUG_SKYBOX || !DEBUG){
    printf("=====> Render: Skybox => Scene\n");
    
	scene->add(skybox);
  }

  Water* water = new Water(camera, skybox);
  water->translate(0.0, 0.0, 0.0);
  water->scale(200);


  if (DEBUG == DEBUG_TERRAIN || !DEBUG){
    printf("=====> Buffer: Shadowmap => Water::shadowMapBuffer\n");
    shadowmap->add(water->shadowMapBuffer);
	window->registerBuffer(terrain->shadowMapBuffer);
    printf("=====> Render: Water => Scene\n");
    scene->add(water);
  }

  /* TERRAIN: END */

  Model* box = new Model(new BoxIndicesGeometry(), new Material(_simple_vshader, _simple_fshader, NULL));
  //scene->add(box);

  string path = __DIR__ + string("resources/nanosuit/nanosuit.obj");
  Model* obj = new Model(path);
  //obj->resetTranslation();
  //obj->scale(.1);
  obj->translate(0, 0, 0);
  scene->add(obj);

  string path_2 = __DIR__ + string("meshes/Shark.obj");
  //Model* shark = new Model(path_2);
  //shark->translate(20, 0, 0);
  //scene->add(shark);

  // Cloud* cloud1 = new Cloud();
  // cloud1->scale(100, 1, 50);
  // cloud1->rotateX(-1.5*M_PI);
  // cloud1->translate(-60.0, 60.0, -100.0);
  // scene->add(cloud1);

  // Cloud* cloud2 = new Cloud();
  // cloud2->scale(100, 1, 50);
  // cloud2->rotateX(-1.5*M_PI);
  // cloud2->translate(-120.0, 60.0, -1000.0);
  // scene->add(cloud2);

  // // Mirror* mirror = new Mirror(camera);
  // // mirror->translate(0.0, 0.0, 10.0);
  // // mirror->scale(100);
  // // scene->add(mirror);
  // // scene->add(mirror->reflection);



  // Add blur as post effect material

  Blur* blur = new Blur(camera);
  Bloom* bloom = new Bloom(camera, blur);
  scene->addToPost(blur);
  scene->addToPost(bloom);
  //scene->addToPost(shadow);
  //scene->addToPost(displacement);
  
  //scene->add(camera);
  // as buffer camera to the scene
  scene->addBufferToScene(camera);
  scene->addBufferToScene(gBufferCamera);

  window->registerScene(heightmap);
  window->registerScene(shadowmap);




}