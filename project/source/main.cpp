#include "globals.h"

#include "threecpp/Window.h"
#include "threecpp/Cameras.h"
#include "scenes/MainScene.h"

#include "view.h"

int main(int, char**) {

	Window* window = new Window(WIDTH, HEIGHT);

	MainScene* scene = new MainScene();
	//Scene* postProcessScene = new Scene();

	// Create a camera
	// Create scene camera with a texture as a render target
	BufferCamera* camera = new BufferCamera(FOV, ASPECT, NEAR, FAR,false);
	//camera->frameBuffer = 0;
	camera->createFrameBuffer(1024, 768, false, true);
	// There might be a more elegant way to do this
	//camera->position = CAM_POS;
	//camera->lookAt = CAM_LOOK;
	//camera->up = CAM_UP;

	camera->update();

	window->registerCamera(camera);

	// Create a Scene
	createView(window, scene, camera);

	// Register the Scenes
	window->registerScene(scene);

	// Animation

	// Animate Position
	// (0, 60, 150);
	camera->animatePositionTo(vec3(0, 60, 150));
	camera->animatePositionTo(vec3(80, 60, 150));
	camera->animatePositionTo(vec3(80, 60, 50));

	// Animate LookAt
	// (0, 0, -100);
	camera->animateLookAt(vec3(0, 0, -100));
	camera->animateLookAt(vec3(0, 0, -100));
	camera->animateLookAt(vec3(0, 0, -100));
	camera->animateLookAt(vec3(0, 0, -100));
	camera->animateLookAt(vec3(0, 0, -100));
	camera->animateLookAt(vec3(-100, 10, -100));

	// Start the animation, at time 0.0 for 2.0
	//camera->startAnimation(15.0, 1.0);

	// Start the event loop, and use the scene callback
	// to update the scene on every frame
	window->startEventLoop();

	if (!window->destroy()) {
		fprintf(stderr, "ERROR: An error occurred while destroying the widow!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}