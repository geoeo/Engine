#include "BillboardMaterial.h"

#include "_billboard_vshader.h"
#include "_billboard_fshader.h"

BillboardMaterial::BillboardMaterial(const char* fileName) : Material(_billboard_vshader, _billboard_fshader, NULL) {
  textures[Material::DIFFUSE_TEXTURE_INDEX] = Material::loadTexture(fileName);
}