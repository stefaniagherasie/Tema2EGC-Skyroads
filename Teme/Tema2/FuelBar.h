#pragma once

#include <string>

#include <include/glm.h>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

#define MAX_FUEL 100.0f

class FuelBar
{
	public:
		FuelBar();
		~FuelBar();

		/* Creeaza un dreptunghi pornind de la corner, width, height */
		Mesh* CreateRectangle(const GLchar* name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color);
		/* Creeza un Mesh cu vertecsi, indicii si numele dat */
		static Mesh* CreateMesh(const GLchar* name, const std::vector<VertexFormat>& vertices, const std::vector<GLushort>& indices);
		
		/* Getters */
		Mesh* GetBackground();
		Mesh* GetFuel();
		float GetScaleFuel();
		

		/* Administreaza nivelul de combustibil in functie de tipul placutei curente */
		void ManageFuel(int codeCurrentBoard);
		/* Verifica daca mai este combustibil ramas */
		bool CheckFuel();
		

	private:
		Mesh* background;
		Mesh* fuel;
		float currentFuel;
};

