#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateSemiCircle(std::string name, glm::vec3 leftBottomCorner, float radius_length, glm::vec3 color, bool fill);
	Mesh* CreateEllipse(std::string name, glm::vec3 leftBottomCorner, float radius_length, glm::vec3 color, bool fill);
	Mesh* CreateMultiLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreatePowerBar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreatePowerLine(std::string name);
	Mesh* CreateTriangle(std::string name);
	Mesh* CreateCircle(std::string name);
	Mesh* CreateScoreBar(std::string name);
}

