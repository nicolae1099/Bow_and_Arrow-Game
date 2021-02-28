#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;
	float lineLength = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;
	int numX = rand() % (resolution.x / 2);
	int numY = rand() % (resolution.y / 2);
	int distance_between = 100;
	
	for (int i = 0; i < num_ballons; i++) {
		numX = rand() % (resolution.x / 2);
		numY = rand() % (resolution.y / 2);
		ballons.push_back(Ballon((resolution.x / 2) + numX, numY + i * distance_between, i % 3));
	}

	for (int i = 0; i < num_shurikens; i++) {
		numX = rand() % (resolution.x - 50);
		numY = rand() % (resolution.y / 2);

		shurikens.push_back(Shuriken(numX, numY - 2 * i * distance_between));
	}

	bow = Bow(bow_line_posX, bow_line_posY, bow_circle_posY);
	arrow = Arrow(bow.line_posX, bow.line_posY + arc_line_length / 2);

	//for (int i = 0; i < num_ballons; i++) {
	//	cout << ballons[i].posX<<" "<<ballons[i].posY<<endl;
	//}
	Mesh* arrow_mesh = Object2D::CreateArrow("arrow_mesh", corner, arrow_line_length, glm::vec3(0, 0.5f, 0.5f), true);
	AddMeshToList(arrow_mesh);

	Mesh* arc_line = Object2D::CreateLine("arc_line", corner, arc_line_length, glm::vec3(0, 0.5f, 0.5f), true);
	AddMeshToList(arc_line);

	Mesh* arc_semi_circle = Object2D::CreateSemiCircle("arc_semi_circle", corner, arc_semi_circle_length, glm::vec3(0, 0.5f, 0.5f), true);
	AddMeshToList(arc_semi_circle);

	Mesh* ballon_ellipse_red = Object2D::CreateEllipse("ballon_ellipse_red", corner, ballons[0].radius, glm::vec3(0.5f, 0, 0), true);
	AddMeshToList(ballon_ellipse_red);

	Mesh* ballon_ellipse_yellow = Object2D::CreateEllipse("ballon_ellipse_yellow", corner, ballons[0].radius, glm::vec3(0.5f, 0.5f, 0), true);
	AddMeshToList(ballon_ellipse_yellow);

	Mesh* ballon_zig_zag = Object2D::CreateMultiLine("ballon_zig_zag", corner, ballon_zig_zag_length, glm::vec3(0.5f, 0.2f, 0), true);
	AddMeshToList(ballon_zig_zag);

	Mesh* shuriken = Object2D::CreateShuriken("shuriken", corner, shuriken_length, glm::vec3(0, 0.75f, 1), true);
	AddMeshToList(shuriken);

	Mesh* heart = Object2D::CreateHeart("heart", corner, heart_length, glm::vec3(0.5f, 0, 0), true);
	AddMeshToList(heart);

	Mesh* powerLine = Object2D::CreatePowerLine("powerLine");
	AddMeshToList(powerLine);

	Mesh* powerBar = Object2D::CreatePowerBar("powerBar", corner, powerbar_length, glm::vec3(0, 180, 0), true);
	AddMeshToList(powerBar);

	Mesh* triangle = Object2D::CreateTriangle("triangle");
	AddMeshToList(triangle);

	Mesh* circle = Object2D::CreateCircle("circle");
	AddMeshToList(circle);

	Mesh* scoreBar = Object2D::CreatePowerBar("scoreBar", corner, powerbar_length, glm::vec3(1.0, 0.9f, 0.6f), true);
	AddMeshToList(scoreBar);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	float angle;
	if (targetIsSet == false) {
		angle = teta_angle;
	}
	else {
		angle = arrow_angle;
	}
	// viteza setata de powerbar 
	if (targetIsSet == true) {

		arrow.posX += speedArrow * cos(angle);
		arrow.posY += speedArrow * sin(angle);
	}
	//daca sageata iese din ecran
	if (arrow.posX > resolution.x || arrow.posY > resolution.y || arrow.posY < 0) {
		arrow.posX = bow.line_posX;
		arrow.posY = bow.line_posY + arc_line_length / 2;
		targetIsSet = false;
	}

	arrowLineMatrix = glm::mat3(1);
	arrowLineMatrix *= Transform2D::Translate(arrow.posX, arrow.posY) * Transform2D::Rotate(angle);
	RenderMesh2D(meshes["arrow_mesh"], shaders["VertexColor"], arrowLineMatrix);

	arcLineMatrix = glm::mat3(1);
	arcLineMatrix *= Transform2D::Translate(bow.line_posX, bow.line_posY); 
	arcLineMatrix *= Transform2D::Rotate(angle90);
	RenderMesh2D(meshes["arc_line"], shaders["VertexColor"], arcLineMatrix);

	arcSemiCircleMatrix = glm::mat3(1);
	arcSemiCircleMatrix *= Transform2D::Translate(bow.line_posX, bow.circle_posY);
	arcSemiCircleMatrix *= Transform2D::Rotate(angle270);
	RenderMesh2D(meshes["arc_semi_circle"], shaders["VertexColor"], arcSemiCircleMatrix);

	// resetarea sagetii cand iese din ecran
	if (arrow.posX > resolution_x) {
		arrow.posX = 0;
		targetIsSet = false;
		arrowLineMatrix = glm::mat3(1);
		arrowLineMatrix *= Transform2D::Translate(100, 400);
	}

	// verifica coliziunea sageata balon si maresc scor
	for (int i = 0; i < num_ballons; i++) {
		float distX = ballons[i].posX - arrow.posX;
		float distY = ballons[i].posY - arrow.posY;
		float distance = sqrt(pow(distX, 2) + pow(distY, 2));
		if (distance <= ballons[i].radius*ballons[i].scaleY && ballons[i].spart == false) {
			ballons[i].spart = true;
	
			if (ballons[i].isColorRed == true) {
				score += 50;
			}
			else {
				score -= 25;
			}
			cout << "Your score is " << score << endl;
		
		}
	}

	// verific coliziunea shuriken player 
	for (int i = 0; i < num_shurikens; i++) {
		int dx = bow.line_posX - shurikens[i].posX;
		int dy = bow.circle_posY - shurikens[i].posY;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < arc_semi_circle_length + shuriken_length) {
			if (shurikens[i].killer == false) {
				livesCounts--;
				shurikens[i].killer = true;
			}
		}
	}

	for (int i = 0; i < livesCounts; ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(110 + i * 30, resolution.y - 20);
		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);
		
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(115 + i * 30, resolution.y - 20);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(125 + i * 30, resolution.y - 20);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

	}
	
	//verific coliziunea shuriken sageata
	for (int i = 0; i < num_shurikens; i++) {
		int dx = arrow.posX - shurikens[i].posX;
		int dy = arrow.posY - shurikens[i].posY;
		float distance = sqrt(dx * dx + dy * dy);
		if (distance < shuriken_length && shurikens[i].dead == false) {
			shurikens[i].dead = true;
			score += 50;
		}
		if (shurikens[i].dead == true) {
			shurikens[i].scaleX -= 0.03;
			shurikens[i].scaleY -= 0.03;
		}
	}
	level = ((int)score / 100) % 10;


	for (int i = 0; i < num_ballons; i++) {
		ballons[i].posY = (ballons[i].posY + 3 + level);
		// modific pozitia balonului
		if (ballons[i].posY > resolution_y) {
			int num = rand() % (resolution_x / 2);
			ballons[i].posX = (resolution_x / 2) + num;
			ballons[i].posY = 0;
			ballons[i].isColorRed = num % 2;
		}
		// animatia de scalare atunci cand e spart
		if (ballons[i].spart == true) {
			ballons[i].scaleX -= 0.03;
			ballons[i].scaleY -= 0.03;
		}
		// cand dispar de pe ecran, spawmez altele.
		if (ballons[i].scaleX < 0) {
			int num = rand() % (resolution_x / 2);
			ballons[i].posX = (resolution_x / 2) + num;
			ballons[i].posY = 0;
			ballons[i].isColorRed = num % 2;
			ballons[i].spart = false;
			ballons[i].scaleX = 1;
			ballons[i].scaleY = 1.3f;

		}

		ballonEllipseMatrix = glm::mat3(1);
		ballonEllipseMatrix = Transform2D::Translate(ballons[i].posX, ballons[i].posY);
		ballonEllipseMatrix *= Transform2D::Scale(ballons[i].scaleX, ballons[i].scaleY);
		if (ballons[i].isColorRed) {
			RenderMesh2D(meshes["ballon_ellipse_red"], shaders["VertexColor"], ballonEllipseMatrix);
		}
		else {
			RenderMesh2D(meshes["ballon_ellipse_yellow"], shaders["VertexColor"], ballonEllipseMatrix);
		}
		
		ballonZigZagMatrix = glm::mat3(1);
		ballonZigZagMatrix *= Transform2D::Translate(ballons[i].posX+7, ballons[i].posY-25);
		RenderMesh2D(meshes["ballon_zig_zag"], shaders["VertexColor"], ballonZigZagMatrix);
	}

	// afisare shurikene
	angularStep += deltaTimeSeconds;
	for (int i = 0; i < num_shurikens; i++) {
		
		shurikens[i].posX = (shurikens[i].posX - 4 -  level);
		if (shurikens[i].posX < 0 || shurikens[i].scaleX < 0) {
			int num_y = rand() % (resolution_y - 50);

			shurikens[i].posX = resolution_x;		
			shurikens[i].posY = num_y;
			shurikens[i].killer = false;
			shurikens[i].scaleX = 1;
			shurikens[i].scaleY = 1;
			shurikens[i].dead = false;
		}

		shurikenMatrix = glm::mat3(1);
		shurikenMatrix = Transform2D::Translate(shurikens[i].posX, shurikens[i].posY)
			* Transform2D::Scale(shurikens[i].scaleX, shurikens[i].scaleY);
		shurikenMatrix *= Transform2D::Rotate(angularStep) ;
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], shurikenMatrix);

	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(3, bow.circle_posY - 125);
	RenderMesh2D(meshes["powerLine"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);

	//randez power bar
	modelMatrix *= Transform2D::Translate(3, bow.circle_posY - 125)
		* Transform2D::Scale((power / maxPower), 1);

	RenderMesh2D(meshes["powerBar"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(3, 20)
		* Transform2D::Scale((25 * score / resolution.x), 2);

	RenderMesh2D(meshes["scoreBar"], shaders["VertexColor"], modelMatrix);

	/*char str[12];
	sprintf(str, "%d", score);
	string s = str;

	Text->RenderText("SCORE: " + s, 500.0f, 20.0f, 1.0f, glm::vec3(0.0, 0.0, 0.0));
	*/
	if (livesCounts == 0) {
		printf("Final score %f", score);
		exit(0);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event
	if (window->KeyHold(GLFW_KEY_W))
	{
		if (bow.line_posY < resolution.y - 2 * arc_semi_circle_length - 10) {
			bow.line_posY += 10;
			bow.circle_posY += 10;
			//arrow.posY += 10;
			if (targetIsSet == false) {
				arrow.posY += 10;
			}
		}
	}
	else if (window->KeyHold(GLFW_KEY_S))
	{
		if (bow.line_posY > 10) {
			bow.line_posY -= 10;
			bow.circle_posY -= 10;
			if (targetIsSet == false) {
				arrow.posY -= 10;
			}
		}
	} 
	else if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (targetIsSet == false) {
			if (power < maxPower) {
				power += 120.f * deltaTime;
				speedArrow += deltaTime * 50.f;
			}
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	//teta_angle = -(GLfloat)atan2(mouseY - arrow.posY, mouseX - arrow.posX);
	// add mouse move event
	teta_angle = atan(((resolution.y - mouseY) - arrow.posY) / mouseX);
	
	
	//cout << teta_angle << endl;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	
	if (targetIsSet == false) {
		power = 0;
		speedArrow = 4;
	}

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		targetIsSet = true;
		arrow_angle = teta_angle;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
