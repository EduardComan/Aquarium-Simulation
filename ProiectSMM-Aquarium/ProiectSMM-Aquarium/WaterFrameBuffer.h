#pragma once

#include <GL/glew.h>
#include <glm.hpp>

class WaterFrameBuffer
{
	//reflection frame buffer components
	unsigned int m_reflection_frame_buffer_id, 
		m_reflection_texture_id,
		m_reflection_depth_buffer_id;

	//refraction frame buffer components
	unsigned int m_refraction_frame_buffer_id,
		m_refraction_texture_id,
		m_refraction_depth_texture_id;

	unsigned int m_reflection_width, m_reflection_height,
		m_refraction_width, m_refraction_height;

	unsigned int m_window_width, m_window_height;//needed for unbinding
public:
	WaterFrameBuffer(unsigned int window_width, unsigned int window_height, 
		unsigned int reflection_width = 2000, unsigned int reflection_height = 2000,
		unsigned int refraction_width = 2000, unsigned int refraction_height = 2000);
	~WaterFrameBuffer();

	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();
	void UnbindFrameBuffer();

	unsigned int GetReflectionTextureID();
	unsigned int GetRefractionTextureID();
	unsigned int GetRefractionDepthTextureID();

private:
	//used by constructor
	void InitReflectionFrameBuffer();
	void InitRefractionFrameBuffer();

	//used to create the basic components needed for the frame buffer
	unsigned int CreateFrameBuffer() const;
	unsigned int CreateTextureAttachment(unsigned int width, unsigned int height) const;
	unsigned int CreateDepthTextureAttachment(unsigned int width, unsigned int height) const;
	unsigned int CreateDepthBufferAttachment(unsigned int width, unsigned int height) const;

	//binding
	void BindFrameBuffer(unsigned int frame_buffer_id, unsigned int width, unsigned int height);
	
};