#include "GameManager.h"
#include "Scene1.h"
#include "GameOver.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
    isRunning = true;
	currentScene = nullptr;
    gameOver = new GameOver(1);
}

bool GameManager::OnCreate() {
    // My display is 1920 x 1080 but the following seems to work best to fill the screen.
    //const int SCREEN_WIDTH = 1540;
    //const int SCREEN_HEIGHT = 860;

    // Use 1000x600 for less than full screen
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

    // select scene for specific assignment

    currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
    

    // need to create Player before validating scene
    if (!ValidateCurrentScene()) {
        OnDestroy();
        return false;
    }
           
	return true;
}


/// Here's the whole game loop
void GameManager::Run() {
    
	timer->Start();
    
	while (isRunning) {
        handleEvents();
		timer->UpdateFrameTicks();
        currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

void GameManager::handleEvents() 
{
    if (gameOver->isAlive(currentScene->getLives()) == false)
    {
        //LoadScene(1);
        currentScene->setLives(100);
        currentScene->setMoney(500);
    }

    SDL_Event event;

    // Let's add mouse movement and position
    // https://wiki.libsdl.org/SDL_GetMouseState

    SDL_PumpEvents();  // make sure we have the latest mouse state.

    //https://www.youtube.com/watch?v=SYrRMr4BaD4&list=PLM7LHX-clszBIGsrh7_3B2Pi74AhMpKhj&index=3

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                isRunning = false;
                break;
            case SDL_SCANCODE_Q:
                isRunning = false;
                break;
            case SDL_SCANCODE_DELETE:
                isRunning = false;
                break;
            case SDL_SCANCODE_1:
                LoadScene(1);
                break;
            default:
                break;
            }
        }
        currentScene->HandleEvents(event);
    }
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}

// This might be unfamiliar
float GameManager::getSceneHeight() { return currentScene->getyAxis(); }

// This might be unfamiliar
float GameManager::getSceneWidth() { return currentScene->getxAxis(); }

// This might be unfamiliar
Matrix4 GameManager::getProjectionMatrix()
{ return currentScene->getProjectionMatrix(); }

// This might be unfamiliar
SDL_Renderer* GameManager::getRenderer()
{
    // [TODO] might be missing some SDL error checking
    SDL_Window* window = currentScene->getWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    return renderer;
}

void GameManager::LoadScene( int i )
{
    // cleanup of current scene before loading another one
    currentScene->OnDestroy();
    delete currentScene;

    switch ( i )
    {
        case 1:
            currentScene = new Scene1( windowPtr->GetSDL_Window(), this);
            break;
        default:
            currentScene = new Scene1( windowPtr->GetSDL_Window(), this );
            break;
    }

    // using ValidateCurrentScene() to safely run OnCreate
    if (!ValidateCurrentScene())
    {
        isRunning = false;
    }
}

bool GameManager::ValidateCurrentScene()
{
    if (currentScene == nullptr) {
        return false;
    }
    if (currentScene->OnCreate() == false) {
        return false;
    }
    return true;
}

void GameManager::LoseLives(int damage)
{
    currentScene->LoseLives(damage);
}

void GameManager::AddMoney(int money)
{
    currentScene->AddMoney(money);
}
