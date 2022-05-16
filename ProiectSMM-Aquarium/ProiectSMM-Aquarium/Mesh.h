#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm.hpp>

#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"


class Mesh
{
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	Texture m_texture;

	VertexArray m_vertex_array;
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;
public:
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Texture& texture = Texture());
	Mesh(const Mesh& mesh);

	void SetTexture(const Texture& texture);

	//draws the mesh
	void Draw(const Camera& camera, Shader& shader, const Renderer& renderer);
};