#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Texture2D.hpp"
#include "glad/glad.h"

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void Begin(glm::mat4 view, Shader* shader = nullptr);
	void End();
	void Draw(Texture2D* texture, glm::vec2 position) const;
	void Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color) const;
	void Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin) const;
	void Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin, glm::vec2 size) const;
	void Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin, glm::vec2 size, GLfloat angle) const;

	Shader* GetCurrentShaderUsing() const;

private:
	GLuint quadVao_;
	bool isBegun_ = false;
	Shader* currentShaderUsing_ = nullptr;
	Shader* defaultShader_ = nullptr;
};

inline SpriteBatch::SpriteBatch()
{
	GLuint vbo;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVao_);
	glBindVertexArray(this->quadVao_);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_DYNAMIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string vert = 
		std::string("#version 330 core\n") +
		std::string("layout(location = 0) in vec4 vertex;\n") +
		std::string("out vec2 TexCoords;\n") +
		std::string("uniform mat4 model;\n") +
		std::string("uniform mat4 view;\n") +
		std::string("uniform mat4 projection;\n") +
		std::string("void main()\n") +
		std::string("{\n") +
		std::string("TexCoords = vertex.zw;\n") +
		std::string("gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);\n") +
		std::string("}\n");

	std::string frag =
		std::string("#version 330 core\n") +
		std::string("in vec2 TexCoords;\n") +
		std::string("out vec4 color;\n") +
		std::string("uniform sampler2D image;\n") +
		std::string("uniform vec3 spriteColor;\n") +
		std::string("void main()\n") +
		std::string("{\n") +
		std::string("color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n") +
		std::string("}\n");
	defaultShader_ = new Shader(vert, frag);
}

inline SpriteBatch::~SpriteBatch()
{
	delete currentShaderUsing_;
	delete defaultShader_;
	glDeleteVertexArrays(1, &quadVao_);
}

inline void SpriteBatch::Begin(glm::mat4 view, Shader* shader)
{
	if (isBegun_)
	{
		std::cerr << "Begin was already called somewhere" << std::endl;
		return;
	}

	isBegun_ = true;

	if (!currentShaderUsing_)
	{
		if (shader)
		{
			currentShaderUsing_ = shader;
		}
		else
		{
			std::cout << "> No shader in, using default shader" << std::endl;
			currentShaderUsing_ = defaultShader_;
		}
	}

	glm::mat4 projection = glm::ortho(
		0.0f,
		static_cast<GLfloat>(800),
		static_cast<GLfloat>(600),
		0.0f,
		-1.0f,
		1.0f);

	currentShaderUsing_->Use();
	currentShaderUsing_->SetUniform("projection", projection);

	currentShaderUsing_->SetUniform("view", view);

	currentShaderUsing_->Use();

}

inline void SpriteBatch::End()
{
	isBegun_ = false;
	//currentShaderUsing_ = nullptr;
}

inline void SpriteBatch::Draw(Texture2D* texture, glm::vec2 position) const
{
	int w = texture->GetWidth();
	int h = texture->GetHeight();

	Draw(texture, position, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(w/2, h/2), glm::vec2(w, h), 0.0f);
}

inline void SpriteBatch::Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color) const
{
	int w = texture->GetWidth();
	int h = texture->GetHeight();

	Draw(texture, position, color, glm::vec2(w / 2, h / 2), glm::vec2(w, h), 0.0f);
}

inline void SpriteBatch::Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin) const
{
	int w = texture->GetWidth();
	int h = texture->GetHeight();

	Draw(texture, position, color, origin, glm::vec2(w, h), 0.0f);
}

inline void SpriteBatch::Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin, glm::vec2 size) const
{
	Draw(texture, position, glm::vec3(1.0f, 1.0f, 1.0f), origin, size, 0.0f);
}

inline void SpriteBatch::Draw(Texture2D* texture, glm::vec2 position, glm::vec3 color, glm::vec2 origin, glm::vec2 size, GLfloat angle) const
{
	if (!isBegun_)
	{
		std::cerr << "PLS USE BEGIN!" << std::endl;
		return;
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	//glm::vec2 offset(origin.x / size.x, origin.y / size.y);
	model = glm::translate(model, glm::vec3(origin.x, origin.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	currentShaderUsing_->Use();
	currentShaderUsing_->SetUniform("model", model);
	currentShaderUsing_->SetUniform("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	glBindVertexArray(quadVao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	texture->Unbind();
}

inline Shader* SpriteBatch::GetCurrentShaderUsing() const
{
	return currentShaderUsing_;
}
