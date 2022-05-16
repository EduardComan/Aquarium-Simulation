#pragma once

#include "Renderer.h"

class Texture
{
	unsigned m_renderer_id;
	std::string m_file_path;
	unsigned char* m_local_buffer;
	int m_width, m_height, m_BPP;

public:
	Texture();
	Texture(unsigned int texture_id);
	Texture(const std::string& path);
	Texture(const Texture& texture);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
