#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Board.h"
#include "Road.h"
#include <vector>
#include <string>

#define NUM_ROADS 4
#define SIZE_ROADS 3.0f
#define BLOCKED_SPEED 25.0f


class Map
{
	public:

		Map();
		~Map();

		/* Actualizeaza toate placutele din harta cand se face o translatie */
		void TranslateMap(float translateZ);
		/* Blocheaza viteza la o valoare mare daca placuta curenta e portocalie */
		void BlockSpeedIfOrange(float deltaTimeSeconds);
		/* Verifica coliziunea jucatorului cu harta (false inseamna ca a nimerit o groapa) */
		bool CheckCollision(int playerRoad);
		/* Obtine codul platformei pe care se afla player-ul */
		void FindCurrentBoardCode(int playerRoad, bool isJumping);
		
		
		/* Vector de drumuri din harta */
		std::vector<Road*> roads;

		float speed;
		bool isBlocked;
		int codeCurrentBoard;

	private:

		float blockedSpeedSeconds;

};