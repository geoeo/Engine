#include "DirectedLight.h"

DirectedLight::DirectedLight(const char* _desc) : Light(_desc), OrthographicCamera(-20.0, 20.0, -20.0, 20.0, 10.0f, 50.0f) {

}

DirectedLight::~DirectedLight() {

}