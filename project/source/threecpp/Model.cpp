#include "Model.h"

Model::Model(Geometry* _geometry, Material* _material,bool _shouldSetData) {
  Mesh* mesh = new Mesh(_geometry, _material);
  meshes.push_back(mesh);
  shouldSetDataVal = _shouldSetData;
}

Model::Model(string pathToMesh, bool _shouldSetData){
	//material = new Material(_simple_vshader, _simple_fshader, NULL);
	loadModel(pathToMesh);
	shouldSetDataVal = _shouldSetData;
}

Model::~Model() {
  for each (Mesh* mesh in meshes)
  {
	  mesh->~Mesh();
  }
}

void Model::draw(GLuint frameBuffer, float _time, float _effect) {
	for each (Mesh* mesh in meshes)
	{
		mesh->draw(frameBuffer,_time,_effect);
	}
}

void Model::setData(){

	for each (Mesh* mesh in meshes)
		mesh->setData();
	
}

void Model::loadModel(string path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}

	this->processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene){



	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(generateMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}

}

// TODO: Refactor this and optmize Geometry to use strcts
Mesh* Model::generateMesh(aiMesh* mesh, const aiScene* scene){

	vector<vec3> verticies;
	vector<vec3> normals;
	vector<vec2> textureCoordiantes;
	vector<vec3> tangents;
	vector <vec3> biTangents;
	vector<GLuint> indices;

	Material* material = new Material(_simple_vshader, _texture_2d_fshader, NULL);

	//Process Verticies & Normals & Texture coordiantes
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		float x = mesh->mVertices[i].x; float y = mesh->mVertices[i].y; float z = mesh->mVertices[i].z;
		vec3 vertex = vec3(x, y, z);
		//std::cout << "x:" + std::to_string(x) + "y:" + std::to_string(y) + "z:" + std::to_string(z) << std::endl;
		verticies.push_back(vertex);

		if (mesh->mNormals != nullptr){
			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			normals.push_back(normal);
		}

		if (mesh->mTangents != nullptr){
			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			tangents.push_back(normal);
		}

		if (mesh->mBitangents != nullptr){
			vec3 normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			biTangents.push_back(normal);
		}


		if (mesh->mTextureCoords) // Does the mesh contain texture coordinates?
		{	
			if (mesh->mTextureCoords[0]){
				vec2 tc = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				textureCoordiantes.push_back(tc);
			}

		}

	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// parse imported mesh's material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* meshMat = scene->mMaterials[mesh->mMaterialIndex];
		aiTextureType type = aiTextureType_DIFFUSE;
		//for (GLuint i = 0; i < meshMat->GetTextureCount(type); i++)
		//{
			aiString str;
			meshMat->GetTexture(type, 0, &str);
			string path = __DIR__ + string("resources/nanosuit/") + str.C_Str();
			material->textures[Material::DIFFUSE_TEXTURE_INDEX] = Material::loadTexture(path.c_str(), false, GL_REPEAT);
		
		//}

			type = aiTextureType_SPECULAR;
			meshMat->GetTexture(type, 0, &str);
			path = __DIR__ + string("resources/nanosuit/") + str.C_Str();
			material->textures[Material::SPECULAR_TEXTURE_INDEX] = Material::loadTexture(path.c_str(), false, GL_REPEAT);

			type = aiTextureType_NORMALS;
			meshMat->GetTexture(type, 0, &str);
			path = __DIR__ + string("resources/nanosuit/") + str.C_Str();
			material->textures[Material::NORMAL_TEXTURE_INDEX] = Material::loadTexture(path.c_str(), false, GL_REPEAT);
	}

	return new Mesh(new Geometry(verticies,normals,tangents,biTangents,textureCoordiantes,indices), material,true);
}