#include "Mesh.h"
//
//#include "_simple_fshader.h"
//#include "_simple_vshader.h"
//#include "_texture_2d_fshader.h"
//
Mesh::Mesh(Geometry* _geometry, Material* _material) {
  geometry = _geometry;
  material = _material;
  //setup();
}
//
//Model::Model(string pathToMesh){
//	material = new Material(_simple_vshader, _simple_fshader, NULL);
//	loadModel(pathToMesh);
//	setup();
//}
//
Mesh::~Mesh() {
  delete geometry;
  delete material;
}
//
//void Model::setup() {
//  glUseProgram(material->id);
//
//  glGenVertexArrays(ONE, &(material->vertexArrayObject));
//  glBindVertexArray(material->vertexArrayObject);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER vertextArrayObject");
//
//  // buffer that holds the vertex data of the geometry object
//  GLuint vertexBufferObject;
//
//  glGenBuffers(ONE, &vertexBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumVertices() * sizeof(vec3), geometry->getVertices(), GL_STATIC_DRAW);
//
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER vertexBufferObject");
//
//  if (geometry->getNumIndices() > 0){
//
//	  GLuint elementBufferObject;
//
//	  glGenBuffers(ONE, &elementBufferObject);
//	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
//	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->getNumIndices() * sizeof(GLuint),
//		  geometry->getIndices(), GL_STATIC_DRAW);
//
//	  checkGLErrors("MATERIAL::CompileShaders", "AFTER elementBufferObject");
//  }
//
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//  glEnableVertexAttribArray(0);
//
//
//  // buffer that holds the normals of the vertices
//  GLuint normalBufferObject;
//  glGenBuffers(ONE, &normalBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumNormals()  * sizeof(vec3), geometry->getNormals(), GL_STATIC_DRAW);
//
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//
//  glEnableVertexAttribArray(1);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER normalBufferObject");
//
//  // buffer that holds the UVs of the vertices
//  GLuint uvBufferObject;
//  glGenBuffers(ONE, &uvBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumUVs() * sizeof(vec2), geometry->getUVs(), GL_STATIC_DRAW);
//
//  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//
//  glEnableVertexAttribArray(2);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER uvBufferObject");
//
//  // buffer that holds the color data of the vertices
//  GLuint colorBufferObject;
//  glGenBuffers(ONE, &colorBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumColors() * sizeof(vec3), geometry->getColors(), GL_STATIC_DRAW);
//
//  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//
//  glEnableVertexAttribArray(3);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER colorBufferObject");
//
//  // buffer that holds the tangent data of the vertices
//  GLuint tangentBufferObject;
//  glGenBuffers(ONE, &tangentBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, tangentBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumTangent() * sizeof(vec3), geometry->getTangent(), GL_STATIC_DRAW);
//
//  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//
//  glEnableVertexAttribArray(4);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER tangentBufferObject");
//
//  // buffer that holds the bitangent data of the vertices
//  GLuint bitangentBufferObject;
//  glGenBuffers(ONE, &bitangentBufferObject);
//  glBindBuffer(GL_ARRAY_BUFFER, bitangentBufferObject);
//
//  glBufferData(GL_ARRAY_BUFFER, geometry->getNumBitangent()* sizeof(vec3), geometry->getBitangent(), GL_STATIC_DRAW);
//
//  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
//
//  glEnableVertexAttribArray(5);
//
//  checkGLErrors("MATERIAL::CompileShaders", "AFTER bitangentBufferObject");
//
//  // Clean up
//  glBindBuffer(GL_ARRAY_BUFFER, CLEAR);
//  glBindVertexArray(CLEAR);
//
//  glUseProgram(CLEAR);
//
//  checkGLErrors("MATERIAL::CompileShaders","END");
//}
//
//void Model::draw(GLuint frameBuffer, float _time, float _effect) {
//  //glDepthMask(GL_FALSE);
//  glUseProgram(material->id);
//
//  glUniform1f(glGetUniformLocation(material->id, "time"), _time);
//  glUniform1f(glGetUniformLocation(material->id, "effect"), _effect);
//
//  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//  glBindVertexArray(material->vertexArrayObject);
//
//  if (geometry->getNumIndices() > 0)
//	glDrawElements(geometry->getDrawMode(), geometry->getNumIndices(), GL_UNSIGNED_INT, 0);
//  else
//	glDrawArrays(geometry->getDrawMode(), 0, geometry->getNumVertices());
//
//  glBindVertexArray(CLEAR);
//  glUseProgram(CLEAR);
//
//  glBindTexture(GL_TEXTURE_2D, CLEAR);
//  glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);
//  //glDepthMask(GL_TRUE);
//}
//
//void Model::setData(){
//  glUseProgram(material->id);
//
//  // Bind the material as texture
//  glActiveTexture(GL_TEXTURE0);
//  glBindTexture(GL_TEXTURE_2D, material->texture);
//
//  // Link material texture attribute
//  glUniform1i(glGetUniformLocation(material->id, "textureSampler"), 0);
//
//  glUseProgram(CLEAR);
//}
//
//void Model::loadModel(string path){
//	Assimp::Importer importer;
//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
//		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
//		return;
//	}
//
//
//	Geometry* g = new Geometry();
//	vector<vec3> verticies;
//	vector<vec3> normals;
//	vector<vec2> textureCoordiantes;
//	vector<vec3> tangent;
//	vector <vec3> biTangent;
//	vector<GLuint> indices;
//
//	this->processNode(scene->mRootNode, scene, &verticies, &normals, &tangent,
//	&biTangent, &textureCoordiantes, &indices, g);
//
//	geometry = new Geometry(verticies, normals,tangent,biTangent, textureCoordiantes, indices);
//
//
//}
//
//void Model::processNode(aiNode* node, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
//vector<vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g){
//
//
//
//	// Process all the node's meshes (if any)
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		generateGeometry(mesh, scene,verticies,normals,tangent,biTangent,textureCoordiantes,indices,g);
//	}
//	// Then do the same for each of its children
//	for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		this->processNode(node->mChildren[i], scene, verticies, normals,tangent,biTangent, textureCoordiantes, indices, g);
//	}
//
//}
//
//// TODO: Refactor this and optmize Geometry to use strcts
//void Model::generateGeometry(aiMesh* mesh, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
//	vector <vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g){
//
//	//Process Verticies & Normals & Texture coordiantes
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		float x = mesh->mVertices[i].x; float y = mesh->mVertices[i].y; float z = mesh->mVertices[i].z;
//		vec3 vertex = vec3(x, y, z);
//		//std::cout << "x:" + std::to_string(x) + "y:" + std::to_string(y) + "z:" + std::to_string(z) << std::endl;
//		verticies->push_back(vertex);
//
//		if (mesh->mNormals != nullptr){
//			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//			normals->push_back(normal);
//		}
//
//		if (mesh->mTangents != nullptr){
//			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//			tangent->push_back(normal);
//		}
//
//		if (mesh->mBitangents != nullptr){
//			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//			biTangent->push_back(normal);
//		}
//
//
//		if (mesh->mTextureCoords) // Does the mesh contain texture coordinates?
//		{	
//			if (mesh->mTextureCoords[0]){
//				vec2 tc = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
//				textureCoordiantes->push_back(tc);
//			}
//
//		}
//
//	}
//
//	for (GLuint i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//			indices->push_back(face.mIndices[j]);
//	}
//
//	// parse imported mesh's material
//	if (mesh->mMaterialIndex >= 0)
//	{
//		aiMaterial* meshMat = scene->mMaterials[mesh->mMaterialIndex];
//		//vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
//		//	aiTextureType_DIFFUSE, "texture_diffuse");
//		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//		//vector<Texture> specularMaps = this->loadMaterialTextures(material,
//		//	aiTextureType_SPECULAR, "texture_specular");
//		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//		aiTextureType type = aiTextureType_DIFFUSE;
//		for (GLuint i = 0; i < meshMat->GetTextureCount(type); i++)
//		{
//			aiString str;
//			meshMat->GetTexture(type, i, &str);
//			string path = __DIR__ + string("textures/nanosuit/") + str.C_Str();
//			//material->texture = Material::loadTexture(path.c_str());
//		
//		}
//	}
//
//}