#include "TextureMaterial.h"

#include "_texture_vshader.h"
#include "_texture_2d_fshader.h"

TextureMaterial::TextureMaterial(const char* fileName) : Material(_texture_vshader, _texture_2d_fshader, NULL) {
  textures[Material::DIFFUSE_TEXTURE_INDEX] = Material::loadTexture(fileName);
}