#include "WaterFrameBuffer.h"
#include <iostream>

WaterFrameBuffer::WaterFrameBuffer(unsigned int window_width, unsigned int window_height,
	unsigned int reflection_width, unsigned int reflection_height,
	unsigned int refraction_width, unsigned int refraction_height)
	:m_window_width{ window_width }, m_window_height{ window_height }, 
	m_reflection_width{ reflection_width }, m_reflection_height{ reflection_height },
	m_refraction_width{ refraction_width }, m_refraction_height{ reflection_height }
{
	InitReflectionFrameBuffer();
	InitRefractionFrameBuffer();
}
WaterFrameBuffer::~WaterFrameBuffer()
{
	glDeleteFramebuffers(1, &m_reflection_frame_buffer_id);
	glDeleteTextures(1, &m_reflection_texture_id);
	glDeleteRenderbuffers(1, &m_reflection_depth_buffer_id);
	glDeleteFramebuffers(1, &m_refraction_frame_buffer_id);
	glDeleteTextures(1, &m_refraction_texture_id);
	glDeleteTextures(1, &m_refraction_depth_texture_id);
}


void WaterFrameBuffer::BindReflectionFrameBuffer()
{
	BindFrameBuffer(m_reflection_frame_buffer_id, m_reflection_width, m_reflection_height);
}
void WaterFrameBuffer::BindRefractionFrameBuffer()
{
	BindFrameBuffer(m_refraction_frame_buffer_id, m_refraction_width, m_refraction_height);
}


unsigned int WaterFrameBuffer::GetReflectionTextureID()
{
	return m_reflection_texture_id;
}
unsigned int WaterFrameBuffer::GetRefractionTextureID()
{
	return m_refraction_texture_id;
}
unsigned int WaterFrameBuffer::GetRefractionDepthTextureID()
{
	return m_refraction_depth_texture_id;
}


void WaterFrameBuffer::InitReflectionFrameBuffer()
{
	m_reflection_frame_buffer_id = CreateFrameBuffer();
	m_reflection_texture_id = CreateTextureAttachment(m_reflection_width, m_reflection_height);
	m_reflection_depth_buffer_id = CreateDepthBufferAttachment(m_reflection_width, m_reflection_height);
	UnbindFrameBuffer();
}
void WaterFrameBuffer::InitRefractionFrameBuffer()
{
	m_refraction_frame_buffer_id = CreateFrameBuffer();
	m_refraction_texture_id = CreateTextureAttachment(m_refraction_width, m_refraction_height);
	m_refraction_depth_texture_id = CreateDepthTextureAttachment(m_refraction_width, m_refraction_height);
	UnbindFrameBuffer();
}


unsigned int WaterFrameBuffer::CreateFrameBuffer()const
{
	unsigned int frame_buffer_id;
	glCreateFramebuffers(1, &frame_buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frame_buffer_id;
}
unsigned int WaterFrameBuffer::CreateTextureAttachment(unsigned int width, unsigned int height)const
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);

	return texture_id;
}
unsigned int WaterFrameBuffer::CreateDepthTextureAttachment(unsigned int width, unsigned int height)const
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_id, 0);

	return texture_id;
}
unsigned int WaterFrameBuffer::CreateDepthBufferAttachment(unsigned int width, unsigned int height)const
{
	unsigned int depth_buffer_id;
	glGenRenderbuffers(1, &depth_buffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);
	
	return depth_buffer_id;
}


void WaterFrameBuffer::BindFrameBuffer(unsigned int frame_buffer_id, unsigned int width, unsigned int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
	glViewport(0, 0, width, height);
}
void WaterFrameBuffer::UnbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_window_width, m_window_height);
}