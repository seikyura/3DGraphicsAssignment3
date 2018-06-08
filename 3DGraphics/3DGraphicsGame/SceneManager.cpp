//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "SceneManager.cpp"
// Description	: SceneManager implementation file
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "SceneManager.h"
#include "Level.h"

CSceneManager* CSceneManager::s_pSceneInstance = 0;

/***********************
* GetInstance: Gets scene manager Instance
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* return s_pSoundInstance - instance of sound manager
***********************/
CSceneManager* CSceneManager::GetInstance()
{
	if (s_pSceneInstance == 0)
	{
		s_pSceneInstance = new CSceneManager();
	}
	return s_pSceneInstance;
}

/***********************
* DestroyInstance: Destroys scene manager Instance
* @author: Vivian Ngo
* @date: 08 / 05 / 18
***********************/
void CSceneManager::DestroyInstance()
{
	if (s_pSceneInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pSceneInstance;
		s_pSceneInstance = nullptr;
	}
}

/***********************
* SetUpScenes: Set up scene items
* @author: Vivian Ngo
* @date: 08 / 05 / 18
***********************/
void CSceneManager::SetUpScenes()
{
	std::shared_ptr<CSprite> playerSprite = std::make_shared<CSprite>(BIRB1, CUBE, glm::vec3(0.0f, 0.0f, 0.0f));
	std::shared_ptr<CPlayer> playerWithSprite = std::make_shared<CPlayer>(playerSprite);
	std::shared_ptr<CScene> level1 = std::make_shared<CLevel>(1, BG, playerWithSprite);
	std::shared_ptr<CScene> level2 = std::make_shared<CLevel>(2, BG, playerWithSprite);
	std::shared_ptr<CScene> level3 = std::make_shared<CLevel>(3, BG, playerWithSprite);
	AddScene(level1);
	AddScene(level2);
	AddScene(level3);

	std::shared_ptr<CScene> startScreen = std::make_shared<CLevel>(10, STARTSCR, playerWithSprite);
	std::shared_ptr<CScene> instructions = std::make_shared<CLevel>(11, STARTSCR, playerWithSprite);
	std::shared_ptr<CScene> endScreen = std::make_shared<CLevel>(12, STARTSCR, playerWithSprite);
	AddScene(startScreen);
	AddScene(instructions);
	AddScene(endScreen);

	SwitchScene(10); //Start with start screen
}

/***********************
* AddScene: Add scene to scene manager
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to add
***********************/
void CSceneManager::AddScene(std::shared_ptr<CScene> scene)
{
	scenesList.push_back(scene);
}

/***********************
* RemoveScene: Remove scene from scene manager
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to add
***********************/
void CSceneManager::RemoveScene(int scene)
{
	std::shared_ptr<CScene> tempScene;
	for (unsigned int i = 0; i < scenesList.size(); ++i)
	{
		if (scene == scenesList[i]->GetLevelNum())
		{
			tempScene = scenesList[i];
			break;
		}
	}

	it = scenesList.begin();

	it = std::find(scenesList.begin(), scenesList.end(), tempScene);
	if (it != scenesList.end())
	{
		scenesList.erase(it);
		scenesList.shrink_to_fit();
	}
}

/***********************
* SwitchScene: Switch scene to the number specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: level - scene to change to
***********************/
void CSceneManager::SwitchScene(int level)
{
	for (unsigned int i = 0; i < scenesList.size(); ++i)
	{
		if (level == scenesList[i]->GetLevelNum())
		{
			currentScene = scenesList[i];
			break;
		}
	}
}

/***********************
* ResetLevels: Method resetting all levels of the game + player stats
* @author: Vivian Ngo
* @date: 08 / 05 / 18
***********************/
void CSceneManager::ResetLevels(std::shared_ptr<CPlayer> _player)
{
	RemoveScene(1);
	RemoveScene(2);
	RemoveScene(3);

	_player->ResetPlayerStats();

	std::shared_ptr<CScene> level1 = std::make_shared<CLevel>(1, BG, _player);
	std::shared_ptr<CScene> level2 = std::make_shared<CLevel>(2, BG, _player);
	std::shared_ptr<CScene> level3 = std::make_shared<CLevel>(3, BG, _player);
	AddScene(level1);
	AddScene(level2);
	AddScene(level3);
}

/***********************
* UpdateScene: Update the scene specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to update
***********************/
void CSceneManager::UpdateScene(std::shared_ptr<CScene> scene)
{
	scene->Update();
}

/***********************
* RenderScene: Render the scene specified
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @parameter: scene - scene to render
***********************/
void CSceneManager::RenderScene(std::shared_ptr<CScene> scene)
{
	scene->Render();
}

/***********************
* GetCurrentScene: Gets the current scene
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @return: currentScene - the current scene
***********************/
std::shared_ptr<CScene> CSceneManager::GetCurrentScene()
{
	return currentScene;
}

/***********************
* GetCurrentSceneNumber: Gets the current scene number
* @author: Vivian Ngo
* @date: 08 / 05 / 18
* @return: currentScene->GetLevelNum() - the current scene's level number
***********************/
int CSceneManager::GetCurrentSceneNumber()
{
	return currentScene->GetLevelNum();
}
