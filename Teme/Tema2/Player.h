#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Map.h"

#define MAX_HEIGHT 2.5f

class Player
{
	public:
		Player();
		~Player();

		/* Verifica daca jucatorul a iesit de pe harta */
		void CheckPlayerFall(Map* map);

		/* Gaseste Road-ul pe care se afla jucatorul */
		void FindPlayerRoad(Map* map);

		/* Fac jucatorul sa sara sau sa cada */
		void MakePlayerJump(float deltaTimeSeconds);
		void MakePlayerFall(float deltaTimeSeconds);

		bool isJumping, isGoingDown, isFalling;
		float angularStep;
		int road;
		glm::vec3 pos;
		
};