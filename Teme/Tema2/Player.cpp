#include "Player.h"

Player::Player()
{
	pos = glm::vec3(0, 0.5f, 0);
	road = 0;
	angularStep = 0;
	isJumping = false;
	isGoingDown = false;
	isFalling = false;
}

Player::~Player()
{
}


/* Verifica daca jucatorul a iesit de pe harta */
void Player::CheckPlayerFall(Map* map)
{
	/* Daca nu se afla pe niciun drum */
	if (road == -1) {
		isFalling = true;
	}

	/* Daca cade intr-o groapa */
	else if ((!isJumping && !isGoingDown)) {
		if (map->CheckCollision(road) == false) {
			isFalling = true;
		}
	}
}

/* Gaseste Road-ul pe care se afla jucatorul */
void Player::FindPlayerRoad(Map* map)
{
	for (int i = 0; i < NUM_ROADS; i++) {
		float leftEdge = map->roads[i]->GetCenterRoad() - SIZE_ROADS / 2;
		float rightEgde = map->roads[i]->GetCenterRoad() + SIZE_ROADS / 2;

		if (pos.x >= leftEdge && pos.x <= rightEgde) {
			road = i;
			return;
		}
	}

	/* Jucatorul nu se afla pe niciun drum */
	road = -1;
}

/* Se face saritura daca este cazul */
void Player::MakePlayerJump(float deltaTimeSeconds)
{
	if (isJumping == true) {
		if (pos.y < MAX_HEIGHT) {
			pos.y += 4.0f * deltaTimeSeconds;
			/* if (!thirdPerson)
				camera->TranslateUpword(4.0f * deltaTimeSeconds);
			*/
		}
		/* A urcat pana la pozitia dorita, acum revine pe harta */
		else if (pos.y > MAX_HEIGHT) {
			isJumping = false;
			isGoingDown = true;
		}

	}
	else if (isGoingDown == true) {
		if (pos.y > 0.5f) {
			pos.y -= 4.0f * deltaTimeSeconds;
		}
		/* A terminat saritura */
		else {
			pos.y = 0.5f;
			isGoingDown = false;
		}
	}
}

/* Se animeaza cazatura jucatorului daca este cazul */
void Player::MakePlayerFall(float deltaTimeSeconds)
{
	if (isFalling) {
		pos.y -= 3.0f * deltaTimeSeconds;
		pos.z -= 3.0f * deltaTimeSeconds;
	}
}