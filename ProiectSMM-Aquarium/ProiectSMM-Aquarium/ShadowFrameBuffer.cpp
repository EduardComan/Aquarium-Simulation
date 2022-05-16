#include "ShadowFrameBuffer.h"

ShadowFrameBuffer::ShadowFrameBuffer(unsigned int window_width, unsigned int window_height, unsigned int shadow_width, unsigned int shadow_height) :
	m_window_width(window_width), m_window_height(window_height), m_shadow_width(shadow_width), m_shadow_height(shadow_height)
{
	m_frame_buffer_id = CreateFrameBuffer();
	m_depth_buffer_id = CreateDepthBufferAttachment(m_shadow_width, m_shadow_height);
	m_depth_texture_id = CreateDepthTextureAttachment(m_shadow_width, m_shadow_height);
	UnbindFrameBuffer();
}

ShadowFrameBuffer::~ShadowFrameBuffer()
{
	glDeleteFramebuffers(1, &m_frame_buffer_id);
	glDeleteTextures(1, &m_depth_texture_id);
	glDeleteRenderbuffers(1, &m_depth_buffer_id);
}

void ShadowFrameBuffer::UnbindFrameBuffer()
{
	//glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_window_width, m_window_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int ShadowFrameBuffer::GetShadowDepthTextureID()
{
	return m_depth_texture_id;
}

unsigned int ShadowFrameBuffer::CreateFrameBuffer() const
{
	unsigned int frame_buffer_id;
	glCreateFramebuffers(1, &frame_buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frame_buffer_id;
}

unsigned int ShadowFrameBuffer::CreateDepthTextureAttachment(unsigned int width, unsigned int height) const
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_id, 0);

	return texture_id;
}

unsigned int ShadowFrameBuffer::CreateDepthBufferAttachment(unsigned int width, unsigned int height) const
{
	unsigned int depth_buffer_id;
	glGenRenderbuffers(1, &depth_buffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

	return depth_buffer_id;
}

void ShadowFrameBuffer::BindFrameBuffer()
{
	glViewport(0, 0, m_shadow_width, m_shadow_height);
	glBindTexture(GL_TEXTURE_2D, m_depth_texture_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id);
}
