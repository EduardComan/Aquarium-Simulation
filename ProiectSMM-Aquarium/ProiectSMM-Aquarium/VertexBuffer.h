#pragma once

class VertexBuffer
{
	unsigned int m_renderer_id;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};