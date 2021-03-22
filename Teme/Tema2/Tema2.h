#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "LabCamera.h"
#include "Transform3D.h"
#include "Map.h"
#include "Player.h"
#include "FuelBar.h"

#include <vector>
#include <string>
#include <iostream>

#define MAX_HEIGHT 2.5f
#define SPEED_JUMP 4.0f
#define SPEED_FALL 3.0f


class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& objColor);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		/* Randarea obiectelor din joc */
		void RanderPlayer(float deltaTimeSeconds);
		void RanderMap(float deltaTimeSeconds);
		void RanderFuelBar();

		/* Se testeaza daca jocul s-a terminat */
		void CheckGameOver();

	protected:
		Tema::Camera *camera;
		glm::mat4 projectionMatrix;

	private:
		Map* map;
		Player* player;
		FuelBar* fuel;

		bool thirdPerson;
};
