#include "MainScene.h"

MainScene::MainScene() : Scene() {

}

MainScene::~MainScene() {

}

void MainScene::onKeyInput(const Event& e) {

  const KeyEvent& event = static_cast<const KeyEvent&>( e );

  // E .. Textures
  if (event.key == GLFW_KEY_E && event.action == GLFW_PRESS){
    featureTextures = !featureTextures;
    printf("Set featureTextures to %i\n", featureTextures);
  }

  // R .. Steep Rock Textures
  if (event.key == GLFW_KEY_R && event.action == GLFW_PRESS){
    featureSteepTextures = !featureSteepTextures;
    printf("Set featureSteepTextures to %i\n", featureSteepTextures);
  }

  // T .. Shadow
  if (event.key == GLFW_KEY_T && event.action == GLFW_PRESS){
    featureShadows = !featureShadows;
    printf("Set featureShadows to %i\n", featureShadows);
  }

  // Z .. Smooth Shadow
  if (event.key == GLFW_KEY_Y && event.action == GLFW_PRESS){
    featureSmoothShadows = !featureSmoothShadows;
    printf("Set featureSmoothShadows to %i\n", featureSmoothShadows);
  }

  // U .. Reflection
  if (event.key == GLFW_KEY_U && event.action == GLFW_PRESS){
    featureReflection = !featureReflection;
    printf("Set featureReflection to %i\n", featureReflection);
  }



  // F .. Debug Slope
  if (event.key == GLFW_KEY_F && event.action == GLFW_PRESS){
    debugSlope = !debugSlope;
    printf("Set debugSlope to %i\n", debugSlope);
  }

  // G .. Debug Displacement
  if (event.key == GLFW_KEY_G && event.action == GLFW_PRESS){
    debugDisplacement = !debugDisplacement;
    printf("Set debugDisplacement to %i\n", debugDisplacement);
  }

  // G .. Debug Visibility
  if (event.key == GLFW_KEY_H && event.action == GLFW_PRESS){
    debugVisibility = !debugVisibility;
    printf("Set debugVisibility to %i\n", debugVisibility);
  }

  // J .. Debug Normalmap
  if (event.key == GLFW_KEY_J && event.action == GLFW_PRESS){
    debugNormals = !debugNormals;
    printf("Set debugNormals to %i\n", debugNormals);
  }

  // K .. Debug Reflection
  if (event.key == GLFW_KEY_K && event.action == GLFW_PRESS){
    debugReflection = !debugReflection;
    printf("Set debugReflection to %i\n", debugReflection);
  }
}

void MainScene::setData(GLuint id){
  glUseProgram(id);
  glUniform1ui(glGetUniformLocation(id, "featureTextures"), featureTextures);
  glUniform1ui(glGetUniformLocation(id, "featureSteepTextures"), featureSteepTextures);
  glUniform1ui(glGetUniformLocation(id, "featureShadows"), featureShadows);
  glUniform1ui(glGetUniformLocation(id, "featureSmoothShadows"), featureSmoothShadows);
  glUniform1ui(glGetUniformLocation(id, "featureReflection"), featureReflection);
  glUniform1ui(glGetUniformLocation(id, "debugSlope"), debugSlope);
  glUniform1ui(glGetUniformLocation(id, "debugDisplacement"), debugDisplacement);
  glUniform1ui(glGetUniformLocation(id, "debugVisibility"), debugVisibility);
  glUniform1ui(glGetUniformLocation(id, "debugNormals"), debugNormals);
  glUniform1ui(glGetUniformLocation(id, "debugReflection"), debugReflection);
}