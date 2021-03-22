#include "FuelBar.h"


FuelBar::FuelBar()
{
	/* Se creeaza Mesh-urile pentru bara de combustibil */
	background = CreateRectangle("background", glm::vec3(0, 0, 0), 0.4f, 3, glm::vec3(1, 1, 1));
	fuel = CreateRectangle("normalFuel", glm::vec3(0.05f, 0.05f, 0), 0.3f, 2.9f, glm::vec3(0, 0, 1));
	currentFuel = MAX_FUEL;
}


FuelBar::~FuelBar()
{
	delete background;
	delete fuel;
}


/* Verifica daca mai este combustibil disponibil */
bool FuelBar::CheckFuel()
{
	if (currentFuel > 0.0f)
		return false;
	else
		return true;
}


/* Administreaza nivelul de combustibil in functie de tipul placutei curente */
void FuelBar::ManageFuel(int codeCurrentBoard)
{
	/* Placuta verde sau galbena - se modifica mai mult combustibilul */
	if (codeCurrentBoard == 1) {
		currentFuel += 0.1f;
		if (currentFuel > MAX_FUEL) {
			currentFuel = MAX_FUEL;
		}
	}
	else if (codeCurrentBoard == 2)
		currentFuel -= 0.1f;

	/* Alt timp de placuta - se scade incet combustibilul */
	else
		currentFuel -= 0.01f;
}


/* Getters */
Mesh* FuelBar::GetBackground()
{
	return background;
}

Mesh* FuelBar::GetFuel()
{
	return fuel;
}

float FuelBar::GetScaleFuel()
{
	/* Calculeaza factorul cu care se scaleaza bara de combustibil */
	return currentFuel / MAX_FUEL;
}



/* Creeaza un dreptunghi pornind de la corner, width, height */
Mesh* FuelBar::CreateRectangle(const GLchar* name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(height, 0, 0), color),
		VertexFormat(corner + glm::vec3(height, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	std::vector<unsigned short> indices = {	0, 1, 2,
											0, 2, 3 };

	Mesh* rectangle = CreateMesh(name, vertices, indices);
	return rectangle;
}


/* Creeza un Mesh cu vertecsi, indicii si numele dat */
Mesh* FuelBar::CreateMesh(const GLchar* name, const std::vector<VertexFormat>& vertices, const std::vector<GLushort>& indices)
{
	unsigned int VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);

	CheckOpenGLError();

	Mesh* mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<GLushort>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;

	return mesh;
}

