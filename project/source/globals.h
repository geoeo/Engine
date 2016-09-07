#pragma once

#include "common.h"

// We should use following naming convention
// for global vars: GLOBAL_VALUE

// Window parameters
static int WIDTH = 1024;
static int HEIGHT = 768;

// Initial Camera Intrinsics
static float FOV = 45.0f;
static float ASPECT = WIDTH / HEIGHT;
static float NEAR = 0.1f;
static float FAR = 1000.0f;

static vec3 CAM_POS = vec3(0, 60, 150);
static vec3 CAM_LOOK = vec3(0, 0, -100);
static vec3 CAM_UP = vec3(0, 1, 0);

static vec3 LIGHT_POS = vec3(0, 80,200);
static vec3 LIGHT_LOOK = vec3(0, 0, -100);
static vec3 LIGHT_UP = vec3(0, 1, 0);

// Control parameters
static double speed = 20.0; // 3 units / second
static double mouseSpeed = 0.005f;

// horizontal angle : toward -Z
static double horizontalAngle = 0.0f;
// vertical angle : 0, look at the horizon
static double verticalAngle = 0.0f;

static unsigned int DEBUG_NOPE = 0;
static unsigned int DEBUG_HEIGHTMAP = 1;
static unsigned int DEBUG_TERRAIN = 2;
static unsigned int DEBUG_SHADOWMAP = 3;
static unsigned int DEBUG_SKYBOX = 4;


static unsigned int DEBUG = DEBUG_NOPE;

