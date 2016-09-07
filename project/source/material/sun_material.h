#include "material.h"

class SunMaterial : public Material {


public:
	void CompileAndLinkShaders(const char * vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource);

	void Draw();

	void SetUniformData(const mat4& model, const mat4& view, const mat4& projection, const GLuint * optional, const vec3* optional_vec);

	SunMaterial(Geometry * geometry);
	~SunMaterial();

};