#include "Mesh.h"

Mesh::Mesh(Geometry* _geometry, Material* _material, bool _shouldSetData) {
  geometry = _geometry;
  material = _material;
  shouldSetDataVal = _shouldSetData;
  setup();
}

Mesh::~Mesh() {
  delete geometry;
  delete material;
}
//
void Mesh::setup() {
  glUseProgram(material->id);

  glGenVertexArrays(ONE, &(material->vertexArrayObject));
  glBindVertexArray(material->vertexArrayObject);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER vertextArrayObject");

  // buffer that holds the vertex data of the geometry object
  GLuint vertexBufferObject;

  glGenBuffers(ONE, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumVertices() * sizeof(vec3), geometry->getVertices(), GL_STATIC_DRAW);


  checkGLErrors("MATERIAL::CompileShaders", "AFTER vertexBufferObject");

  if (geometry->getNumIndices() > 0){

	  GLuint elementBufferObject;

	  glGenBuffers(ONE, &elementBufferObject);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->getNumIndices() * sizeof(GLuint),
		  geometry->getIndices(), GL_STATIC_DRAW);

	  checkGLErrors("MATERIAL::CompileShaders", "AFTER elementBufferObject");
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
  glEnableVertexAttribArray(0);


  // buffer that holds the normals of the vertices
  GLuint normalBufferObject;
  glGenBuffers(ONE, &normalBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumNormals()  * sizeof(vec3), geometry->getNormals(), GL_STATIC_DRAW);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

  glEnableVertexAttribArray(1);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER normalBufferObject");

  // buffer that holds the UVs of the vertices
  GLuint uvBufferObject;
  glGenBuffers(ONE, &uvBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumUVs() * sizeof(vec2), geometry->getUVs(), GL_STATIC_DRAW);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

  glEnableVertexAttribArray(2);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER uvBufferObject");

  // buffer that holds the color data of the vertices
  GLuint colorBufferObject;
  glGenBuffers(ONE, &colorBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumColors() * sizeof(vec3), geometry->getColors(), GL_STATIC_DRAW);

  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

  glEnableVertexAttribArray(3);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER colorBufferObject");

  // buffer that holds the tangent data of the vertices
  GLuint tangentBufferObject;
  glGenBuffers(ONE, &tangentBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, tangentBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumTangent() * sizeof(vec3), geometry->getTangent(), GL_STATIC_DRAW);

  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

  glEnableVertexAttribArray(4);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER tangentBufferObject");

  // buffer that holds the bitangent data of the vertices
  GLuint bitangentBufferObject;
  glGenBuffers(ONE, &bitangentBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, bitangentBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumBitangent()* sizeof(vec3), geometry->getBitangent(), GL_STATIC_DRAW);

  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

  glEnableVertexAttribArray(5);

  checkGLErrors("MATERIAL::CompileShaders", "AFTER bitangentBufferObject");

  // Clean up
  glBindBuffer(GL_ARRAY_BUFFER, CLEAR);
  glBindVertexArray(CLEAR);

  glUseProgram(CLEAR);

  checkGLErrors("MATERIAL::CompileShaders","END");
}

void Mesh::draw(GLuint frameBuffer, float _time, float _effect) {
  //glDepthMask(GL_FALSE);
  glUseProgram(material->id);

  glUniform1f(glGetUniformLocation(material->id, "time"), _time);
  glUniform1f(glGetUniformLocation(material->id, "effect"), _effect);

  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glBindVertexArray(material->vertexArrayObject);

  if (geometry->getNumIndices() > 0)
	  glDrawElements(geometry->getDrawMode(), geometry->getNumIndices(), GL_UNSIGNED_INT, 0);
  else
	glDrawArrays(geometry->getDrawMode(), 0, geometry->getNumVertices());

  glBindVertexArray(CLEAR);
  glUseProgram(CLEAR);

  glBindTexture(GL_TEXTURE_2D, CLEAR);
  glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);
  //glDepthMask(GL_TRUE);
}


void Mesh::setData(){
  glUseProgram(material->id);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->textures[Material::DIFFUSE_TEXTURE_INDEX]);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "textureSamplerDiffuse"), 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, material->textures[Material::SPECULAR_TEXTURE_INDEX]);

  glUniform1i(glGetUniformLocation(material->id, "textureSamplerSpecular"), 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, material->textures[Material::NORMAL_TEXTURE_INDEX]);

  glUniform1i(glGetUniformLocation(material->id, "textureSamplerNormal"), 2);



  glUseProgram(CLEAR);
}

