#pragma once

class TextureFromRender
{
public:
	GLuint FramebufferName;
	GLuint depthTexture;;

	GLuint quad_vertexbuffer;
	GLuint quad_programID;
	GLuint texID;
	GLuint timeID;

public:
	TextureFromRender();
	~TextureFromRender();

	void initialize();
	void update();
	void render();
	void release();

	void bindTexture();
	void freeTexture();
};

