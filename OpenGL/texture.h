#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

using namespace std;
class Texture
{
private:

	GLuint m_texture;
public:
	Texture(const string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();
};
#endif