#pragma once
#include <glad/glad.h>
#include <iostream>

// TODO: Texture2D class should contain only Color Data and Image Data (width, height, color type etc)
class Texture2D
{
public:
	Texture2D(int width, int height, int comp, unsigned char* data) 
		: glTexture_(0), width_(width), height_(height), comp_(comp), data_(data)
	{
		std::cout << glGetError() << std::endl;

		InitTexture2D();
		//glBindTexture(GL_TEXTURE_2D, glTexture_);

		

		//glBindTexture(GL_TEXTURE_2D, 0);
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
		std::cout << glGetError() << std::endl;

		glGenTextures(1, &glTexture_);

		std::cout << glGetError() << std::endl;

		glBindTexture(GL_TEXTURE_2D, glTexture_); // bind

		std::cout << glGetError() << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (comp_ == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
		else if (comp_ == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);

		glGenerateMipmap(GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, 0); // unbind
	}

	GLuint glTexture_;

	int width_;
	int height_;
	int comp_;
	unsigned char* data_;
};
