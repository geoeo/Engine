#include "Scene.h"
// TODO: this should not depend on view
#include "../view.h"

Scene::Scene() {


  debugScreen = new Model(new PlaneVert(), new Material(_simple_vshader, _texture_2d_fshader, NULL));

  // Create and initialize a Scene
  if (!create()) {
    fprintf(stderr, "ERROR: An error occurred while creating the scene!\n");
    exit(EXIT_FAILURE);
  }
}

Scene::~Scene() {
	debugScreen->~Model();

}

int Scene::create() {

  // Set the default background color
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // TODO: we should document what all those settings are doing
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Enable Transparency - TODO look at this. Atm this produces strange artifacts when enabled
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return SCENE_SUCCESS;
}

void Scene::update(const Event& e) {

  const UpdateEvent& event = static_cast<const UpdateEvent&>( e );

  deltaTime = event.time - currentTime;
  currentTime = event.time;

  // Draw all buffers
  for (unsigned b=0; b < buffers.size(); b++) {
    // Clear the canvas
	glBindFramebuffer(GL_FRAMEBUFFER, buffers[b]->frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the meshes of the Scene
	for (unsigned i = 0; i < models.size(); i++) {
		if (models[i]->isTexture == false) {
			if (models[i]->shouldSetData())
				models[i]->setData();
			for each (Mesh* mesh in models[i]->meshes)
			{
				setData(mesh->material->id);
				buffers[b]->setData(mesh->material->id);
				mesh->material->setMVP(models[i]->model, buffers[b]->model, buffers[b]->view, buffers[b]->projection);

				// Set the light information
				for (unsigned l = 0; l < lights.size(); l++) {
					lights[l]->setData(mesh->material->id);
				}
				// if mesh is imported we have to set textures for each child mesh before the draw call
				if (mesh->shouldSetData())
					mesh->setData();

				mesh->draw(buffers[b]->frameBuffer, currentTime, buffers[b]->effect_roll);
			}
      }
    }

    // Check for error which occurred during the scene rendering
    checkGLErrors("Scene::update", "RENDERING LOOP BUFFER");
    glFlush();
  }

  // Draw the real scene
  for (unsigned c=0; c < cameras.size(); c++) {
    // Clear the canvas
	glBindFramebuffer(GL_FRAMEBUFFER, cameras[c]->frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cameras[c]->animate(currentTime);

    // Render the meshes of the Scene
	for (unsigned i = 0; i < models.size(); i++) {
		if (models[i]->shouldSetData())
			models[i]->setData();

		for each (Mesh* mesh in models[i]->meshes)
		{
			setData(mesh->material->id);
			cameras[c]->setData(mesh->material->id);
			mesh->material->setMVP(models[i]->model, cameras[c]->model, cameras[c]->view, cameras[c]->projection);

			// Set the light information
			for (unsigned l = 0; l < lights.size(); l++) {
				lights[l]->setData(mesh->material->id);
			}
			if (mesh->shouldSetData())
				mesh->setData();

			mesh->draw(cameras[c]->frameBuffer, currentTime, 0.0/* cameras[i]->effect_roll*/);
		}
    }

    // Check for error which occurred during the scene rendering
    checkGLErrors("Scene::update", "RENDERING LOOP");
    glFlush();
  }

  //DEBUG = DEBUG_SCENE;
  if (DEBUG == DEBUG_SCENE && cameras.size() > 0){
	  BufferCamera* cam = (BufferCamera*)cameras[0];
	  cam->Position = vec3(0.0f, 0.0f, 1.0f);
	  cam->update();
	  GLuint textureToDisplay = cam->texture;
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  debugScreen->meshes[0]->material->textures[Material::DIFFUSE_TEXTURE_INDEX] = textureToDisplay;
	  debugScreen->meshes[0]->material->setMVP(debugScreen->model, cam->model, cam->view, cam->projection);
	  debugScreen->meshes[0]->setData();
	  debugScreen->meshes[0]->draw(0, currentTime);

	  // Check for error which occurred during the scene rendering
	  checkGLErrors("Scene::update", "DEBUG POST LOOP");
	  glFlush();
  }

  else if (postProcess.size() > 0){
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  // Render the postProcess of the Scene
	  for (unsigned i = 0; i < postProcess.size(); i++) {
		  for each (Mesh* mesh in postProcess[i]->meshes)
		  {
			  mesh->material->setMVP(postProcess[i]->model, postProcess[i]->model, postProcess[i]->model, postProcess[i]->model);
		  }
		  postProcess[i]->setData();
		  postProcess[i]->draw(0, currentTime);
	  }

	  // Check for error which occurred during the scene rendering
	  checkGLErrors("Scene::update", "POST LOOP");
	  glFlush();

  }


}


void Scene::onKeyInput(const Event& e) {

  const KeyEvent& event = static_cast<const KeyEvent&>( e );

  // Toggle wireframe view
  if (event.key == GLFW_KEY_M && event.action == GLFW_PRESS){
    toggleWireFrame = !toggleWireFrame;

    if (toggleWireFrame) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }

  // Reset the view
  if (event.key == GLFW_KEY_R && event.action == GLFW_PRESS){
    // RESET
  }
}

void Scene::add(BufferCamera* _buffer) {
  buffers.push_back(_buffer);
}

void Scene::add(Camera* _camera) {
  cameras.push_back(_camera);
}

void Scene::addBufferToScene(BufferCamera* _camera) {
	cameras.push_back(_camera);
}

void Scene::add(Model* model) {
	models.push_back(model);
}

void Scene::add(Light* light) {
  lights.push_back(light);
}

void Scene::addToPost(Model* model){
	postProcess.push_back(model);
}

void Scene::setData(GLuint id){

}
