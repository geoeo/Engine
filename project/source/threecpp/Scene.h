#pragma once

#include "common.h"
#include "Cameras.h"
#include "Events.h"
#include "Model.h"
#include "Lights.h"

class Scene {

private:

  std::vector<Model*> postProcess;
  std::vector<Model*> models;
  std::vector<Camera*> cameras;
  std::vector<BufferCamera*> buffers;
  std::vector<Light*> lights;

  Model* debugScreen;

public:

  static const int SCENE_SUCCESS = 1;
  static const int SCENE_ERROR = 0;

  double currentTime = 0;
  double deltaTime = 0;
  bool toggleWireFrame = false;

  GLuint shadowMap;

  // Constructor
  Scene();

  // Destructor
  ~Scene();

  virtual int create();
  virtual void update(const Event&);
  virtual void onKeyInput(const Event&);
  virtual void add(BufferCamera*);
  virtual void add(Camera*);
  virtual void add(Model*);
  virtual void addToPost(Model*);
  virtual void add(Light*);
  virtual void addBufferToScene(BufferCamera*);
  virtual void setData(GLuint);
};