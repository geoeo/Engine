#pragma once

#include <stdlib.h>
#include <assert.h>
#include <cstdlib>
#include <functional>

#ifdef _WIN32
  // Fix issues due to
  // std::min/max compatibility
  #include <algorithm>
  #include <cctype>
  #include <locale>
  #define __DIR__ "../../source/"
#else
  #define __DIR__ "../source/"
#endif

// OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Utilities to parse shader and compile shader files
#include <OpenGP/GL/glfw_helpers.h>
#include <OpenGP/GL/glfw_trackball.h>

#include <OpenGP/GL/EigenOpenGLSupport3.h>

#include <OpenGP/GL/shader_helpers.h>

// For mesh I/O we use OpenGP
#include <OpenGP/Surface_mesh.h>

// For loading external mesh formats we use Assimp
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

/// We use Eigen for linear algebra
typedef Eigen::Vector2f vec2;
typedef Eigen::Vector3f vec3;
typedef Eigen::Vector4f vec4;
typedef Eigen::Matrix4f mat4;
typedef Eigen::Matrix3f mat3;

// Define exit flags
#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 1
#endif

static const GLuint CLEAR = 0;

// Using namespaces by default
using namespace std;
using namespace opengp;

static void checkGLErrors(char* location, char* msg){
	GLenum error_enum = glGetError();
	if (error_enum != GL_NO_ERROR){
		fprintf(
			stdout,
			"Error: Error in %s (%s): %s\n",
			location,
			msg,
			glGetString(error_enum)
			);
	}
}


