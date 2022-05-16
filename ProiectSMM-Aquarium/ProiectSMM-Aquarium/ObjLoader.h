#pragma once

#include "Mesh.h"
#include <string>
#include <sstream>
#include <vector>

namespace ObjLoader
{	
	enum class LineType
	{
		NONE,
		POSITION,
		TEXTURE_COORD,
		NORMAL,
		FACE
	};

	void AddVertex(std::vector<float>& vertices, const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec2>& tex_coords, const std::vector<glm::vec3>& normals, const std::string& component_indices);
	LineType DetermineLineType(std::stringstream& line_ss);
	std::vector<float> Parse(const std::string& file_path);
}
