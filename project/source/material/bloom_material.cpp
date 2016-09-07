#include "bloom_material.h"

BloomMaterial::BloomMaterial(Geometry* geometry) : Material(geometry){

}

BloomMaterial::~BloomMaterial(){

}

void BloomMaterial::CompileAndLinkShaders(const char * vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource){
	// Clear error buffer
	checkGLErrors("BloomMaterial::CompileAndLinkShaders", "START");

	const char * vertexShader = readFile(vertexShaderSource);
	const char * fragmentShader = readFile(fragmentShaderSource);
	const char * geometryShader = NULL;
	if (geometryShaderSource != NULL)
		geometryShader = readFile(geometryShaderSource);


	programID = opengp::compile_shaders(vertexShader, fragmentShader, geometryShader);

	checkGLErrors("BloomMaterial::CompileAndLinkShaders", "AFTER COMPILATION");

	if (!programID) exit(EXIT_FAILURE);
	glUseProgram(programID);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	checkGLErrors("BloomMaterial::CompileAndLinkShaders", "AFTER VAO");

	// buffer that holds the vertex data of the geometry object
	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, geometry->getNumVertices() * sizeof(vec3), geometry->getVertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, DONT_NORMALIZE, 3 * sizeof(GLfloat), ZERO_BUFFER_OFFSET);
	glEnableVertexAttribArray(0);

	GLuint tbo;

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);

	glBufferData(GL_ARRAY_BUFFER, geometry->getNumVertices() * sizeof(vec2), geometry->getUVs(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, DONT_NORMALIZE, 2 * sizeof(GLfloat), ZERO_BUFFER_OFFSET);
	glEnableVertexAttribArray(1);


	checkGLErrors("BloomMaterial::CompileAndLinkShaders", "AFTER VBO");


	// Clean up
	glBindBuffer(GL_ARRAY_BUFFER, CLEAR);
	glBindVertexArray(CLEAR);

	glUseProgram(CLEAR);

	delete[] vertexShader;
	delete[] fragmentShader;
	delete[] geometryShader;

	checkGLErrors("BloomMaterial::CompileAndLinkShaders", "END");


}

//TODO add add option to render to frame buffer
void BloomMaterial::Draw(){
	glUseProgram(programID);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);

	glDrawArrays(geometry->getDrawMode(), 0, geometry->getNumVertices());

	glBindVertexArray(CLEAR);

	glUseProgram(CLEAR);
}

void BloomMaterial::SetUniformData(const mat4& model, const mat4& view, const mat4& projection, const GLuint * optional, const vec3* optional_vec){

	glUseProgram(programID);

	GLuint modelID = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(modelID, ONE, DONT_TRANSPOSE, model.data());

	GLuint projectionID = glGetUniformLocation(programID, "projection");
	glUniformMatrix4fv(projectionID, ONE, DONT_TRANSPOSE, projection.data());

	GLuint viewID = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(viewID, ONE, DONT_TRANSPOSE, view.data());

	glUseProgram(CLEAR);
}