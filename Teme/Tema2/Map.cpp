#include "Map.h"


Map::Map()
{
	/* Daca numarul de drumuri e par */
	if (NUM_ROADS % 2 == 0) {
		for (int i = -NUM_ROADS / 2; i < NUM_ROADS / 2; i++) {
			roads.emplace_back(new Road(i * SIZE_ROADS));
		}
	}

	/* Daca numarul de drumuri e par */
	else {
		for (int i = -NUM_ROADS / 2; i <= NUM_ROADS / 2; i++) {
			roads.emplace_back(new Road(i * SIZE_ROADS));
		}
	}

	speed = 10.0f,
	codeCurrentBoard = -1;

	isBlocked = false;
	blockedSpeedSeconds = 5;
}


Map::~Map()
{
	for (int i = 0; i < NUM_ROADS; i++) {
		delete roads[i];
	}
}


/* Actualizeaza toate placutele din harta cand se face o translatie */
void Map::TranslateMap(float offset)
{
	for (int i = 0; i < NUM_ROADS; i++) {
		roads[i]->TranslateRoad(offset);
	}
}


/* Blocheaza viteza la o valoare mare daca placuta curenta e portocalie */
void Map::BlockSpeedIfOrange(float deltaTimeSeconds)
{
	/* Daca e prima oara cand atingem placa portocalie se fixeaza viteza */
	if (codeCurrentBoard == 3 && !isBlocked) {
		speed = BLOCKED_SPEED;
		isBlocked = true;
	}
	/* Daca se atinge din nou placa se reseteaza numarul de secunde */
	else if (codeCurrentBoard == 3 && isBlocked) {
		blockedSpeedSeconds = 5;
	}


	/* Daca se scurg secundele se revine la viteza normala */
	if (blockedSpeedSeconds < 0 && isBlocked) {
		speed = 12.0f;
		blockedSpeedSeconds = 5;
		isBlocked = false;
	}
	/* Se scurge timpul pana ajunge la 0 */
	else if (isBlocked) {
		blockedSpeedSeconds -= deltaTimeSeconds;
	}
}


/* Verifica coliziunea jucatorului cu harta */
bool Map::CheckCollision(int playerRoad)
{
	/* Se gaseste prima placa de pe drumul pe care e jucatorul */
	Road* road = roads[playerRoad];
	Board* firstBoard = road->roadBoards[0];

	/* Daca jucatorul este pe placa se face mov si se face coliziunea */
	if (firstBoard->GetStart() >= 0 && firstBoard->GetEnd() <= 0) {
		firstBoard->isPurple = true;
		return true;
	}

	/* Gasim groapa */
	return false;
}


/* Obtine codul platformei pe care se afla player-ul */
void Map::FindCurrentBoardCode(int playerRoad, bool isJumping)
{
	/* Codul este -1 daca jucatorul nu e pe vreun drum, 
	   este in saritura sau in groapa */
	if (playerRoad == -1 || isJumping) {
		codeCurrentBoard = -1;
		return;
	}

	Board* currentBoard = roads[playerRoad]->roadBoards[0];
	if (currentBoard->GetStart() < 0) {
		codeCurrentBoard = -1;
		return;
	}
	
	codeCurrentBoard = currentBoard->GetColorCode();
}