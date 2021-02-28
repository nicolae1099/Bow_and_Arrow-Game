#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length/5, 0, 0), color),
		VertexFormat(corner + glm::vec3(length/5, length/10, 0), color),
		VertexFormat(corner + glm::vec3(length/3, -length/40, 0), color),
		VertexFormat(corner + glm::vec3(-length / 5, -length / 6.6, 0), color),
		VertexFormat(corner + glm::vec3(length / 5, -length / 20, 0), color),
		VertexFormat(corner + glm::vec3(0, -length / 20, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);

	return square;
}

Mesh* Object2D::CreateLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
	};

	std::vector<unsigned short> indices = { 0, 1 };

	Mesh* line = new Mesh(name);
	line->SetDrawMode(GL_LINES);
	line->InitFromData(vertices, indices);

	return line;
}

Mesh* Object2D::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(14 * length/20, length / 20, 0), color),
		VertexFormat(corner + glm::vec3(14 * length / 20, length / 8, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(14 * length / 20, - length / 8, 0), color),
		VertexFormat(corner + glm::vec3(14 * length / 20, - length / 20, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,3,4,5,6};

	triangle->SetDrawMode(GL_LINE_LOOP);
	triangle->InitFromData(vertices, indices);

	return triangle;
}

Mesh* Object2D::CreateSemiCircle(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color, bool fill)
{
	

	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	int num_triangles = 1000;

	for (GLushort i = 0; i < num_triangles; ++i)
	{
		float arg = 2.0f * (GLfloat)(M_PI * i / 2) / num_triangles;

		vertices.emplace_back(
			glm::vec3(cos(arg) * radius, sin(arg) * radius, 0), color);
		indices.push_back(i);
	}

	Mesh* semiCircle = new Mesh(name);
	semiCircle->InitFromData(vertices, indices);
	semiCircle->SetDrawMode(GL_LINE_LOOP);

	return semiCircle;
}

Mesh* Object2D::CreateEllipse(std::string name, glm::vec3 leftBottomCorner, float radius_length, glm::vec3 color, bool fill) {
	

	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	int num_triangles = 100;


	for (GLushort i = 0; i < num_triangles; ++i)
	{
		float arg = 2.0f * (GLfloat)M_PI * i / num_triangles;

		vertices.emplace_back(
			glm::vec3(cos(arg) * radius_length, sin(arg) * radius_length, 0),
			color);
		indices.push_back(i);
	}

	Mesh* ellipse = new Mesh(name);
	ellipse->InitFromData(vertices, indices);
	ellipse->SetDrawMode(GL_TRIANGLE_FAN);

	return ellipse;
}

Mesh* Object2D::CreateMultiLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length, -length, 0), color),
		VertexFormat(corner + glm::vec3(0, -2 * length, 0), color),
		VertexFormat(corner + glm::vec3(-length , -3 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, -4 * length, 0), color),
		VertexFormat(corner + glm::vec3(-length , -5 * length, 0), color),
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5 };

	Mesh* multiLine = new Mesh(name);
	multiLine->SetDrawMode(GL_LINE_STRIP);
	multiLine->InitFromData(vertices, indices);

	return multiLine;
}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length, -length/2, 0), color),
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(-length / 2, length, 0), color),

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, length / 2, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),
		VertexFormat(corner + glm::vec3(length/2, -length, 0), color),
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	Mesh* shuriken = new Mesh(name);
	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);

	return shuriken;
}

Mesh* Object2D::CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices = 
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(2* length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, -4 * length, 0), color),
		VertexFormat(corner + glm::vec3(-2*length, length, 0), color),
		VertexFormat(corner + glm::vec3(-length, length, 0), color),
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5};

	Mesh* heart = new Mesh(name);
	heart->SetDrawMode(GL_TRIANGLE_FAN);
	heart->InitFromData(vertices, indices);
	return heart;
}

//power bar
Mesh* Object2D::CreatePowerBar(std::string name, glm::vec3 corner, float length, glm::vec3 color, bool fill) {

	float width = 10;

	std::vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0 , 0), color),
		VertexFormat(corner + glm::vec3(length, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	std::vector<unsigned short> indices{ 0, 1, 2, 3, 0, 2 };
	Mesh* bar = new Mesh(name);
	bar->InitFromData(vertices, indices);
	return bar;
}

//power line
Mesh* Object2D::CreatePowerLine(std::string name) {

	float length = 101;
	float width = 10;
	glm::vec3 color = glm::vec3(0, 128, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0 , 0), color),
		VertexFormat(glm::vec3(length, width, 0), color),
		VertexFormat(glm::vec3(0, width, 0), color)
	};

	std::vector<unsigned short> indices{ 0, 1, 2, 3 };
	Mesh* line = new Mesh(name);
	line->SetDrawMode(GL_LINE_LOOP);
	line->InitFromData(vertices, indices);
	return line;
}

// cerc pt inima
Mesh* Object2D::CreateCircle(std::string name) {
	float radius = 5;
	int indice = 0;
	glm::vec3 color = glm::vec3(1, 0, 0);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.emplace_back(glm::vec3(0, 0, 0), color);

	for (short i = 0; i < 181; ++i)
	{
		float angle = 2.0f * (float)M_PI * i / 360;
		float rx = cos(angle) * radius;
		float ry = sin(angle) * radius;

		vertices.emplace_back(glm::vec3(rx, ry, 0), color);
		indices.push_back(indice);
		indice++;
	}

	Mesh* circle = new Mesh(name);
	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);

	return circle;

}

//triunghi pt inima
Mesh* Object2D::CreateTriangle(std::string name) {
	float length = 20;
	glm::vec3 color = glm::vec3(1, 0, 0);
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length / 2 , -length + 6, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 0 };

	triangle->InitFromData(vertices, indices);
	return triangle;
}

