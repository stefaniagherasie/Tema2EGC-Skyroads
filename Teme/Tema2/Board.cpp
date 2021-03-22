#include "Board.h"


Board::Board(float previousEnd)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	/* Se genereaza random dimensiunea, delay-ul si culoarea placutei */
	std::uniform_int_distribution<int> sizeRand(10, 15);
	std::uniform_int_distribution<int> delayRand(0, 15);
	std::uniform_int_distribution<int> colorRand(0, 15);
	
	int delay;

	/* Pentru prima placuta generata, se seteaza o dimensiune mai mare, 
	   sa fie albastra si sa nu aiba delay */
	if (previousEnd == 0.0f) {
		size = 40;
		color = glm::vec3(0, 0, 1);
		codeCurrentBoard = 0;
		delay = 0;
	}

	/* Pentru celelalte placute se genereaza toti parametrii random */
	else {
		size = sizeRand(gen);
		delay = delayRand(gen);
		codeCurrentBoard = colorRand(gen);

		/* Delay-ul va fi in intervalul [5, 10], orice alte valori primite random
		   se fac 0 pentru a nu exista prea multe gropi intre placute */
		if (delay <= 5 || delay > 10)
			delay = 0;

		/* Codul de culoare va fi in intervalul [0, 4], orice alte valori primite random
		   se fac 0 pentru a ma asigura ca predomina culoarea albastra */
		if (codeCurrentBoard > 4)
			codeCurrentBoard = 0;

		if (codeCurrentBoard == 0)					// culoarea albastra
			color = glm::vec3(0, 0, 1);
		else if (codeCurrentBoard == 1)			// culoarea verde
			color = glm::vec3(0.1f, 1, 0.1f);
		else if (codeCurrentBoard == 2)			// culoarea galbena
			color = glm::vec3(0.9f, 1, 0.2f);
		else if (codeCurrentBoard == 3)			// culoarea portocalie
			color = glm::vec3(0.9f, 0.6f, 0.1f);
		else if (codeCurrentBoard == 4)			// culoarea rosie
			color = glm::vec3(0.9f, 0.1f, 0.2f);
	}


	
	center = previousEnd - size / 2 - delay;
	start = center + size / 2;
	end = center - size / 2;
}

Board::~Board()
{
}


/* Getters */
float Board::GetSize()
{
	return this->size;
}

float Board::GetCenter()
{
	return this->center;
}

float Board::GetStart()
{
	return this->start;
}

float Board::GetEnd()
{
	return this->end;
}

int Board::GetColorCode()
{
	return this->codeCurrentBoard;
}

glm::vec3 Board::GetColor()
{
	return this->color;
}


/* Setters */
void Board::SetCenter(float center)
{
	this->center = center;
}

void Board::SetStart(float start)
{
	this->start = start;
}

void Board::SetEnd(float end)
{
	this->end = end;
}

void Board::SetColor(glm::vec3 color)
{
	this->color = color;
}

