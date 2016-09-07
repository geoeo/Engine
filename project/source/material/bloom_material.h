#include "material.h"

class BloomMaterial : public Material {

private:
	bool LoadCubeMapSide(GLuint* texture, GLenum sideTarget, const char * fileName);

	void CreateCubeMap(const char* front, const char* back, const char* top, const char*bottom, const char* left, const char*right, GLuint *tex_cube);

	GLuint cubeMapTexture;

public:
	void CompileAndLinkShaders(const char * vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource);

	void Draw();

	void SetUniformData(const mat4& model, const mat4& view, const mat4& projection, const GLuint * optional, const vec3* optional_vec);

	BloomMaterial(Geometry * geometry);
	~BloomMaterial();

};