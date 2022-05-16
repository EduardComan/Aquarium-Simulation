#pragma once
#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Texture& texture)
	:m_vertices{ vertices }, m_indices{ indices }, m_texture{ texture }, 
	m_vertex_buffer{VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float))},
	m_index_buffer{ IndexBuffer(m_indices.data(), m_indices.size()) }
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);

	m_vertex_array.AddBuffer(m_vertex_buffer, layout);
}

Mesh::Mesh(const Mesh& mesh)
	:Mesh(mesh.m_vertices, mesh.m_indices, mesh.m_texture) {}

void Mesh::SetTexture(const Texture& texture)
{
	this->m_texture = texture;
}

void Mesh::Draw(const Camera& camera, Shader& shader, const Renderer& renderer)
{
	m_texture.Bind();
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
	shader.SetUniform3f("u_CamPosition", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

	renderer.Draw(m_vertex_array, m_index_buffer, shader);
}