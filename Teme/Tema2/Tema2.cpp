#include "Tema2.h"

using namespace std;


Tema2::Tema2()
{
	{
		map = new Map();
		player = new Player();
		fuel = new FuelBar();

		thirdPerson = true;
	}

	camera = new Tema::Camera();
	camera->Set(glm::vec3(0, 2, 5), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

Tema2::~Tema2()
{
	delete map;
	delete player;
	delete fuel;
}

void Tema2::Init()
{
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("ShaderBoard");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/BoardVertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/BoardFragment.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::FrameEnd()
{
	// DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}


/* Se testeaza daca jocul s-a terminat */
void Tema2::CheckGameOver()
{
	if (player->isFalling && player->pos.z < -MAX_HEIGHT) {
		printf("You fell.....GAME OVER!\n");
		window->Close();
	}

	else if (fuel->CheckFuel()) {
		printf("Out of fuel.....GAME OVER!\n");
		window->Close();
	}

	else if (map->codeCurrentBoard == 4) {
		printf("You stepped on a RED board.....GAME OVER!\n");
		window->Close();
	}
}


/* Randare jucator*/
void Tema2::RanderPlayer(float deltaTimeSeconds)
{
	/* Gaseste drumul pe care se afla jucatorul */
	player->FindPlayerRoad(map);

	/* Verifica daca jucatorul a iesit de pe harta */
	player->CheckPlayerFall(map);

	/* Face saritura sau animatia de cazatura, daca este cazul */
	if (player->isFalling) {
		player->MakePlayerFall(deltaTimeSeconds);
	}
	player->MakePlayerJump(deltaTimeSeconds);

	/* Rotirea jucatorului pentru a face miscarea mai dinamica */
	player->angularStep += map->speed * deltaTimeSeconds;

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player->pos.x, player->pos.y, player->pos.z));
		modelMatrix = glm::rotate(modelMatrix, player->angularStep, glm::vec3(-1, 0, 0));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
}


/* Randare harta */
void Tema2::RanderMap(float deltaTimeSeconds)
{
	/* Obtine codul platformei pe care se afla player-ul */
	map->FindCurrentBoardCode(player->road, (player->isJumping || player->isGoingDown));

	/* Blocheaza viteza la o valoare mare daca placuta curenta e portocalie */
	map->BlockSpeedIfOrange(deltaTimeSeconds);

	/* Actualizeaza toate placutele din harta cand se face o translatie */
	if (!player->isFalling) {
		map->TranslateMap(map->speed * deltaTimeSeconds);
	}


	for (int i = 0; i < NUM_ROADS; i++) {
		Road* road = map->roads[i];

		for (int j = 0; j < NUM_BOARDS; j++) {
			Board* board = road->roadBoards[j];

			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(road->GetCenterRoad(), 0, board->GetCenter()));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(SIZE_ROADS, 0.2f, board->GetSize()));

				if (board->isPurple) {
					RenderSimpleMesh(meshes["box"], shaders["ShaderBoard"], modelMatrix, glm::vec3(0.6f, 0.1f, 0.8f));
				}
				else
					RenderSimpleMesh(meshes["box"], shaders["ShaderBoard"], modelMatrix, board->GetColor());
			}
		}
	}
}


/* Randare combustibil in interfata cu utilizatorul */
void Tema2::RanderFuelBar()
{
	/* Administreaza nivelul de combustibil in functie de tipul placutei curente */
	fuel->ManageFuel(map->codeCurrentBoard);

	if (thirdPerson)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = Transform3D::Translate(2 + player->pos.x, 4.4f, 0) *
					  Transform3D::Scale(fuel->GetScaleFuel(), 1, 1);
		RenderMesh(fuel->GetFuel(), shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform3D::Translate(2 + player->pos.x, 4.4f, 0);
		RenderMesh(fuel->GetBackground(), shaders["VertexColor"], modelMatrix);
	}
	else
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = Transform3D::Translate(camera->position.x + 0.4f, camera->position.y + 0.48f, camera->position.z - 1) *
			Transform3D::Scale(fuel->GetScaleFuel() * 0.2f, 0.2f, 0.2f);
		RenderMesh(fuel->GetFuel(), shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform3D::Translate(camera->position.x + 0.4f, camera->position.y + 0.48f, camera->position.z - 1) *
			Transform3D::Scale(0.2f, 0.2f, 0.2f);
		RenderMesh(fuel->GetBackground(), shaders["VertexColor"], modelMatrix);
	}
}



void Tema2::Update(float deltaTimeSeconds)
{
	CheckGameOver();

	RanderPlayer(deltaTimeSeconds);
	RanderMap(deltaTimeSeconds);
	RanderFuelBar();

	if(!thirdPerson)
		camera->MoveFirstInJumpOrFall(player, deltaTimeSeconds);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	/* Se mareste sau micsoreaza viteza de deplasare */
	if (window->KeyHold(GLFW_KEY_W) && !map->isBlocked) {
		if (map->speed < 15.0f)
			map->speed += 0.05f;
	}
	else if (window->KeyHold(GLFW_KEY_S) && !map->isBlocked) {
		if (map->speed > 8.0f)
			map->speed -= 0.05f;
	}

	/* Se misca stanga-dreapta jucatorul si camera */
	if (window->KeyHold(GLFW_KEY_D)) {
		camera->TranslateRight(deltaTime * 5);
		player->pos.x += deltaTime * 5;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		camera->TranslateRight(-deltaTime * 5);
		player->pos.x -= deltaTime * 5;
	}

	/* Se face saritura */
	if (window->KeyHold(GLFW_KEY_SPACE) && !player->isJumping && !player->isGoingDown && !player->isFalling) {
		player->isJumping = true;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	/* Se oscileaza intre modurile de joc First si Third Person Camera */
	if (key == GLFW_KEY_C)
	{
		if (thirdPerson)
		{
			camera->Set(glm::vec3(0, 1, -0.5f), glm::vec3(0, 1, -1), glm::vec3(0, 1, 0));
			camera->TranslateRight(player->pos.x);
			camera->TranslateUpword(player->pos.y);
		}
		else {
			camera->Set(glm::vec3(0, 2, 5), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
			camera->TranslateRight(player->pos.x);
		}

		thirdPerson = !thirdPerson;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
