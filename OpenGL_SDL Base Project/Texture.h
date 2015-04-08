#pragma once
#include <Windows.h>
#include <gl\GLU.h>

class Texture
{
private:
	GLuint _ID;
	int _width, _height;

public:
	Texture();
	~Texture();
	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};

