#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Board.h"
#include <vector>
#include <string>

#define NUM_BOARDS 5

class Road
{
	public:

		Road(float center);
		~Road();

		/* Getter */
		float GetCenterRoad();

		/* Actualizeaza toate placutele din Road cand se face o translatie */
		void TranslateRoad(float translateZ);

		/* Vector de placute din Road*/
		std::vector<Board*> roadBoards;

	private:

		/* Pozitia pe Ox a drumului */
		float center;
};