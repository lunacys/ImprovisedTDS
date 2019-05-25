#pragma once
#include <glad/glad.h>

// TODO: Texture2D class should contain only Color Data and Image Data (width, height, color type etc)
class Texture2D
{
public:
	Texture2D(int width, int height, unsigned char* data) 
		: glTexture_(0), width_(width), height_(height)
	{
		InitTexture2D();
		glBindTexture(GL_TEXTURE_2D, glTexture_);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	~Texture2D()
	{
		glDeleteTextures(1, &glTexture_);
	}

	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }

	void Bind() const { glBindTexture(GL_TEXTURE_2D, glTexture_); }
	void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
	void InitTexture2D()
	{
		glGenTextures(1, &glTexture_);

		glBindTexture(GL_TEXTURE_2D, glTexture_); // bind

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0); // unbind
	}

	GLuint glTexture_;

	int width_;
	int height_;
};
