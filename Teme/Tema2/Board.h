#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <vector>
#include <string>
#include <random>

class Board
{
	public:
		Board(float previousEnd);
		~Board();

		/* Getters */
		float GetSize();
		float GetCenter();
		float GetStart();
		float GetEnd();
		int GetColorCode();
		glm::vec3 GetColor();

		/* Setters */
		void SetCenter(float center);
		void SetStart(float start);
		void SetEnd(float end);
		void SetColor(glm::vec3 color);

		/* Platforma si-a schimbat culoarea in mov */
		bool isPurple = false;

	private:
		float size, center, start, end;
		int codeCurrentBoard;
		glm::vec3 color;
};
