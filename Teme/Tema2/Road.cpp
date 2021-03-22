#include "Road.h"


Road::Road(float center)
{
	this->center = center;

	/* La initializare, prima placuta are start-ul in 0 */
	roadBoards.emplace_back(new Board(0));

	/* Restul placutelor sunt calculate dupa end-ul celei anterioare */
	for (int i = 1; i < NUM_BOARDS; i++) {
		float previousEnd = roadBoards[i - 1]->GetEnd();
		roadBoards.emplace_back(new Board(previousEnd));
	}
}

Road::~Road()
{
	for (int i = 0; i < NUM_BOARDS; i++) {
		delete roadBoards[i];
	}
}


/* Actualizeaza toate placutele din Road cand se face o translatie */
void Road::TranslateRoad(float translateZ)
{
	/* Se actualizeaza center, start si end dupa translatie */
	for (int i = 0; i < NUM_BOARDS; i++) {
		roadBoards[i]->SetCenter(translateZ + roadBoards[i]->GetCenter());
		roadBoards[i]->SetStart(translateZ + roadBoards[i]->GetStart());
		roadBoards[i]->SetEnd(translateZ + roadBoards[i]->GetEnd());
	}

	/* Daca prima placuta trece de jucator, aceasta este stearsa si se adauga 
	   o noua placuta dupa ultima din Road */
	if (roadBoards[0]->GetEnd() > 0) {
		roadBoards.erase(roadBoards.begin());

		Board* lastBoard = roadBoards[roadBoards.size() - 1];
		roadBoards.emplace_back(new Board(lastBoard->GetEnd()));
	}
}


/* Getter */
float Road::GetCenterRoad()
{
	return this->center;
}