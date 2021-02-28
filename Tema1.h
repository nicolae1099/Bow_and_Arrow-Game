#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Ballon.h"
#include "Shuriken.h"
#include "Bow.h"
#include "Arrow.h"

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::ivec2 resolution = window->GetResolution();
	glm::mat3 arrowLineMatrix;
	glm::mat3 arrowTriangleMatrix;
	glm::mat3 arcLineMatrix;
	glm::mat3 arcSemiCircleMatrix;

	glm::mat3 shurikenMatrix;

	glm::mat3 ballonEllipseMatrix;
	glm::mat3 ballonZigZagMatrix;

	glm::mat3 heartMatrix1;
	glm::mat3 heartMatrix2;
	glm::mat3 heartMatrix3;

	glm::mat3 modelMatrix;
	float translateX = 0, translateY = 0;
	float scaleX = 0, scaleY = 0;
	float angularStep = 0;
	bool direction = false;

	float arrow_rotation = 5.5;
	float arrow_triangle_length = 20;
	float arrow_line_length = 100;

	float arc_line_length = 200;
	float arc_semi_circle_length = 100;

	float ballon_zig_zag_length = 15;

	float shuriken_length = 50;

	float cosx = 0, cosy = 0;
	bool ok = false;
	bool targetIsSet = false;
	const int num_ballons = 5;
	const int num_shurikens = 4;

	const float angle90 = 1.57;
	const float angle180 = 3.14;
	const float angle270 = 4.71;
	const float angle15 = 0.26;
	const float angle30 = 0.52;
	const float angle45 = 0.78;
	const float angle60 = 1.04;
	const float angle75 = 1.3;

	const int resolution_y = 720;
	const int resolution_x = 1280;

	int bow_line_posX = 20;
	int bow_line_posY = 500;
	int bow_circle_posY = 600;

	int arrow_line_posX = 92;
	int arrow_line_posY = 500;
	float teta_angle = 0;
	float arrow_angle = 0;

	int livesCounts = 3;
	int heart_length = 10;
	int heart1_scale = 1;
	int heart2_scale = 1;
	float score;
	float speedArrow = 10;
	float power;
	float maxPower = 100;
	vector<Ballon> ballons;
	vector<Shuriken> shurikens;
	int powerbar_length = 100;
	float level = 0;
	//vector<Arrow> arrows;
	Bow bow;
	Arrow arrow;
};
