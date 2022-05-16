#pragma once
#include <GL/glew.h>
#include <glm.hpp>

class ShadowFrameBuffer
{
public:
	unsigned int m_frame_buffer_id, m_depth_texture_id, m_depth_buffer_id;
	unsigned int m_shadow_width, m_shadow_height;
	unsigned int m_window_width, m_window_height;

public:
	ShadowFrameBuffer(unsigned int window_width, unsigned int window_height,
		unsigned int shadow_width = 4096, unsigned int shadow_height = 4096);
	~ShadowFrameBuffer();

	void BindFrameBuffer();
	void UnbindFrameBuffer();

	unsigned int GetShadowDepthTextureID();

private:
	unsigned int CreateFrameBuffer() const;
	unsigned int CreateDepthTextureAttachment(unsigned int width, unsigned int height) const;
	unsigned int CreateDepthBufferAttachment(unsigned int width, unsigned int height) const;


};

