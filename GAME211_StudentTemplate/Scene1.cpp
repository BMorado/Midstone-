#include "Scene1.h"
#include <VMath.h>
#include "WaveController.h"
#include "Enemy.h"
#include "EnemyCircle.h"
#include "EnemySquare.h"
#include "EnemyTriangle.h"
#include "EnemyDiamond.h"
#include "EnemyStar.h"
#include "EnemyHexagon.h"
#include "imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include <stdio.h>

// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	waveController = std::make_unique<WaveController>();
}

Scene1::~Scene1(){
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	grid = new Grid(game);
	grid->OnCreate(liveTowers);

	//call wave controller OnCreate
	waveController->OnCreate();

	 (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.WantCaptureMouse = true;

	printf("want mouse input ==  ");
	if (io.WantCaptureMouse)printf("true \n"); else printf("false \n");

	io.Fonts->AddFontDefault();
	font = io.Fonts->AddFontFromFileTTF("ProggyClean.ttf", 20.0f);
	font2 = io.Fonts->AddFontFromFileTTF("ProggyClean.ttf", 12.0f);
	IM_ASSERT(font != nullptr);
	IM_ASSERT(font2 != nullptr);
	
	std::shared_ptr<Enemy> prototype = std::make_shared<EnemyCircle>(1, 2, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);
	prototype = std::make_shared<EnemyTriangle>(2, 4, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);
	prototype = std::make_shared<EnemySquare>(3, 3, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);
	prototype = std::make_shared<EnemyHexagon>(4, 8, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);
	prototype = std::make_shared<EnemyStar>(5, 10, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);
	prototype = std::make_shared<EnemyDiamond>(6, 12, grid->GetPath(), game);
	waveController->AddWave(prototype, 10);



	return true;
}

void Scene1::OnDestroy() 
{
	delete grid;
	waveController->OnDestroy();
	for (int i = 0; i < liveTowers.size(); i++) {
		liveTowers[i]->OnDestroy();
	}
}

void Scene1::Update(const float deltaTime) {

	waveController->Update(deltaTime, liveEnemies);

	for (int i = 0; i < liveEnemies.size(); i++)
	{
		
			liveEnemies[i]->Update(deltaTime, liveEnemies, i);
		
		
	}
	for (int i = 0; i < liveTowers.size(); i++)
	{
		if(liveTowers[i] != nullptr)
			liveTowers[i]->update(deltaTime, liveEnemies, liveProjectiles);
	}
	
	for (int i = 0; i < liveProjectiles.size(); i++)
	{
		liveProjectiles[i]->Update(deltaTime, liveEnemies, liveProjectiles, i);
	}
}

void Scene1::Render() {

	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	grid->RenderGrid();

	
	// render the player
	//game->RenderPlayer(0.10f);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

	}




	for (int i = 0; i < liveEnemies.size(); i++)
	{
		liveEnemies[i]->Render(0.03f);
	}

	for (int i = 0; i < liveTowers.size(); i++)
	{
		if (liveTowers[i]!=nullptr)
		{
			liveTowers[i]->Render(0.03f);
		}
		
	}

	for (int i = 0; i < liveProjectiles.size(); i++)
	{
		liveProjectiles[i]->Render(0.05f);
	}


	renderGUI();

	ImGui::Render();
	SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		printf("click at x = %f, y - %f \n", mousePos.x, mousePos.y);
		if (towerSelect == false && towerCombination == false && (event.motion.x < 800 || event.motion.y < 550)) {
			mousePos = Vec2(event.motion.x, event.motion.y);
			clickPos = mousePos;
			if (clickPos.x > 800) {
				clickPos.x = 800;
			}
			if (clickPos.y > 500) {
				clickPos.y = 450;
			}
			if (grid->SelectedCell(mousePos.x, mousePos.y) < 10 && grid->SelectedCell(mousePos.x, mousePos.y) > 0) {

				towerCombination = true;
			}
			else {
				towerSelect = true;
			}
			}
		
		

		break;
	default:
		break;
	}
	
	// send event to grid script
	grid->HandleEvents(event, liveTowers);
}

int Scene1::getLives()
{
	return totalLives;
}

int Scene1::getMoney()
{
	return totalMoney;
}

void Scene1::setLives(int lives)
{
	totalLives = lives;
}

void Scene1::setMoney(int money)
{
	totalMoney = money;
}

void Scene1::LoseLives(int damage)
{
	totalLives -= damage;
}

void Scene1::AddMoney(int money)
{
	totalMoney += money;
}

void Scene1::renderGUI()
{

	ImGui::Begin("Top Hub Bar", &topMenuBar, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	ImGui::SetWindowSize(ImVec2(500, 15));
	ImGui::SetWindowPos(ImVec2(275, 10));

	ImGui::PushFont(font);
	ImGui::Text("Lives = %d", totalLives);
	ImGui::SameLine();
	ImGui::Text("     Money = %d$", totalMoney);
	ImGui::PopFont();

	ImGui::End();

	renderSkipWave();

	if (towerSelect) {
		renderTowerSelect();
	}

	if (towerCombination) {
		renderTowerCombination();
	}

}

void Scene1::renderTowerSelect()
{
	

	ImGui::Begin("Tower Selection", &towerSelect, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	ImGui::SetWindowPos(ImVec2(clickPos.x, clickPos.y));

	ImGui::SetWindowSize(ImVec2(500, 500));

	ImGui::PushFont(font2);
	ImGui::Text("Select a Tower to place");


	if (totalMoney >= CircleTowerCost) {
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 1.0f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 1.0f, 1.0f));

		if (ImGui::Button("Circle Tower = 100$")) {
			//insert code to place tower here
			grid->ValidTile(mousePos.x, mousePos.y);
			
			if (grid->valid_Tile == true && !grid->tower_Combo ) {
				grid->selected_Tower = 1;
				grid->SelectedCell(mousePos.x, mousePos.y, liveTowers);
				totalMoney -= CircleTowerCost;
				towerSelect = false;
			}
			
			
		}
	}
	else
	{
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::Button("Circle Tower = 100$");
	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();

	//triangle tower button
	if (totalMoney >= TriangleTowerCost) {
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.2f, 1.0f, 1.0f));

		if (ImGui::Button("Triangle Tower = 150$")) {

			grid->ValidTile(mousePos.x, mousePos.y);
			if (grid->valid_Tile && !grid->tower_Combo ) {
				totalMoney -= TriangleTowerCost;
				towerSelect = false;
				grid->selected_Tower = 2;
				grid->SelectedCell(mousePos.x, mousePos.y, liveTowers); 
			}
			
		}
	}
	else
	{
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::Button("Triangle Tower = 150$");
	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();




	//add more towers here



	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 1.0f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1.0f, 1.0f, 0.80f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1.0f, 1.0f, 1.0f));
	if (ImGui::Button("Close Tower Selection Window")) {
		towerSelect = false;
	}
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	ImGui::PopFont();
	ImGui::End();


}

void Scene1::renderTowerCombination()
{
	//towerConbination menu
	

	ImGui::Begin("Tower Combination", &towerSelect, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	ImGui::SetWindowPos(ImVec2(clickPos.x, clickPos.y));

	ImGui::SetWindowSize(ImVec2(500, 500));

	ImGui::PushFont(font2);
	ImGui::Text("Select a Tower to combine tower with");


	if (totalMoney >= CircleTowerCombinationCost) {
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 1.0f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 1.0f, 1.0f));

		if (ImGui::Button("Combine with Circle Tower = 100$"))
		 {
			grid->ValidTile(mousePos.x, mousePos.y);
			if (grid->valid_Tile && grid->tower_Combo) {
				//insert code to place tower here
				
				totalMoney -= CircleTowerCombinationCost;
				towerCombination = false;
				selectedTowerType = circle;
				ChosenTower();
				grid->SelectedCell(mousePos.x, mousePos.y, liveTowers);
				
			}
			
		}
	}
	else
	{
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::Button("Combine with Circle Tower = 100$");
	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();

	//triangle tower button
	if (totalMoney >= TriangleTowerCombinationCost) {
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.2f, 1.0f, 1.0f));

		if (ImGui::Button("Combine with Triangle Tower = 150$")) {

			
			grid->ValidTile(mousePos.x, mousePos.y);
			if (grid->valid_Tile && grid->tower_Combo) {
				selectedTowerType = triangle;
				ChosenTower();
				totalMoney -= TriangleTowerCombinationCost;
				towerCombination = false;
				grid->SelectedCell(mousePos.x, mousePos.y, liveTowers);
				
			}
			
		}
	}
	else
	{
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::Button("Combine with Triangle Tower = 150$");
	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();




	//add more towers here



	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 1.0f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1.0f, 1.0f, 0.80f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1.0f, 1.0f, 1.0f));
	if (ImGui::Button("Close Tower Combination Window")) {
		towerCombination = false;
	}
	ImGui::PopStyleColor(3);
	ImGui::PopID();
	ImGui::PopFont();
	ImGui::End();
	

}
void Scene1::ChosenTower() {
	switch (selectedTowerType)
	{
	case Scene1::none:
		printf("forgot to inizilize selected tower type \n");
		break;
	case Scene1::circle:
		grid->selected_Tower = circle;
		break;
	case Scene1::triangle:
		grid->selected_Tower = triangle;
		break;
	case Scene1::square:
		grid->selected_Tower = square;
		break;
	case Scene1::hexagon:
		grid->selected_Tower = hexagon;
		break;
	case Scene1::octogon:
		grid->selected_Tower = octogon;
		break;
	case Scene1::star:
		grid->selected_Tower = star;
		break;
	case Scene1::diamond:
		grid->selected_Tower = diamond;
		break;
	default:
		printf("this should be imposible how have you done this \n");
		break;
	}
	
	
}
void Scene1::renderSkipWave()
{
	ImGui::Begin("Skip_wave_gui", &SkipWaveGUI, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	ImGui::SetWindowPos(ImVec2(800, 550));

	ImGui::SetWindowSize(ImVec2(200, 200));

	ImGui::PushFont(font);

	WaveActive = liveEnemies.size() > 0 || waveController->isSpawnerSpawning();

	if (WaveActive) {
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.1f, 0.0f, 0.6f));
		ImGui::Button("Start Next Wave");

	}
	else
	{
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.2f, 1.0f, 0.80f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.2f, 1.0f, 1.0f));
		
		if (ImGui::Button("Start Next Wave")) {
			//code that skips the wait between waves
			waveController->skipBreak();
		}

	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();
	ImGui::PopFont();
	ImGui::End();
}
