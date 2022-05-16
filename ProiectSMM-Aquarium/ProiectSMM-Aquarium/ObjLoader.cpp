#include "ObjLoader.h"

#include <fstream>
#include <iostream>

void ObjLoader::AddVertex(std::vector<float>& vertices, const std::vector<glm::vec3>& positions,
	const std::vector<glm::vec2>& tex_coords, const std::vector<glm::vec3>& normals, const std::string& component_indices)
{
	std::stringstream component_indices_ss(component_indices);
	unsigned int position_index, texture_index, normal_index;

	component_indices_ss >> position_index;//reading position index
	component_indices_ss.ignore(1, '/');

	component_indices_ss >> texture_index;//reading texture coordinate index
	component_indices_ss.ignore(1, '/');

	component_indices_ss >> normal_index;//reading normal index

	//adding the vertex position to the vertex buffer
	vertices.push_back(positions[position_index - 1].x);
	vertices.push_back(positions[position_index - 1].y);
	vertices.push_back(positions[position_index - 1].z);

	//adding vertex texture coordinates to the vertex buffer
	vertices.push_back(tex_coords[texture_index - 1].x);
	vertices.push_back(tex_coords[texture_index - 1].y);

	//adding vertex normals to the vertex buffer
	vertices.push_back(normals[normal_index - 1].x);
	vertices.push_back(normals[normal_index - 1].y);
	vertices.push_back(normals[normal_index - 1].z);
}

ObjLoader::LineType ObjLoader::DetermineLineType(std::stringstream& line_ss)
{
	std::string line_type_character;
	line_ss >> line_type_character;

	if (line_type_character == "v")
		return ObjLoader::LineType::POSITION;
	else if (line_type_character == "vt")
		return ObjLoader::LineType::TEXTURE_COORD;
	else if (line_type_character == "vn")
		return ObjLoader::LineType::NORMAL;
	else if (line_type_character == "f")
		return ObjLoader::LineType::FACE;

	return ObjLoader::LineType::NONE;
}

std::vector<float> ObjLoader::Parse(const std::string& file_path)
{
	std::ifstream fin(file_path);
	std::string line;
	std::stringstream line_ss;

	std::vector<glm::vec3> vertex_positions;
	std::vector<glm::vec2> texture_positions;
	std::vector<glm::vec3> normals;
	std::vector<float> result_verices;

	while (std::getline(fin, line))
	{
		line_ss = std::stringstream(line);
		ObjLoader::LineType line_type = ObjLoader::DetermineLineType(line_ss);
		
		switch (line_type)
		{
		case ObjLoader::LineType::POSITION:
		{
			glm::vec3 position;
			line_ss >> position.x >> position.y >> position.z;
			vertex_positions.emplace_back(position);
			break;
		}
		case ObjLoader::LineType::TEXTURE_COORD:
		{
			glm::vec2 tex_coord;
			line_ss >> tex_coord.x >> tex_coord.y;
			texture_positions.emplace_back(tex_coord);
			break;
		}
		case ObjLoader::LineType::NORMAL:
		{
			glm::vec3 normal;
			line_ss >> normal.x >> normal.y >> normal.z;
			normals.emplace_back(normal);
			break;
		}
		case ObjLoader::LineType::FACE:
		{
			std::string component_indices;
			while (line_ss >> component_indices)
				AddVertex(result_verices, vertex_positions, texture_positions, normals, component_indices);

			break;
		}
		}
	}

	/*for(auto& position : vertex_positions)
		std::cout << position.x << " " << position.y << " " << position.z << "\n";
	for (auto& tex_coord : texture_positions)
		std::cout << tex_coord.x << " " << tex_coord.y << "\n";
	for (auto& normal : normals)
		std::cout << normal.x << " " << normal.y << " " << normal.z << "\n";

	for (unsigned int i = 0; i < result_verices.size(); i++)
	{
		if (i % 8 == 0)
			std::cout<<"\n";
		std::cout << result_verices[i] << " ";
	}
	*/
	fin.close();
	return result_verices;
}