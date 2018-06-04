#include "Scene.h"

/***********************
* Render: Render Scene
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CScene::Render()
{
	m_pBackgroundSprite->Draw();

	//remember to add bg first, with text being last
	for (unsigned int i = 0; i < m_pSpriteList.size(); ++i)
	{
		m_pSpriteList[i]->Draw();
	}


	for (unsigned int i = 0; i < m_pTextList.size(); ++i)
	{
		m_pTextList[i]->Render();
	}
}

/***********************
* Render: Update Scene
* @author: Vivian Ngo
* @date: 08/05/18
***********************/
void CScene::Update()
{

}

/***********************
* CreateBackground: Create Background for Scene
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: bg - background to create and set
***********************/
void CScene::CreateBackground(EImage bg)
{
	std::shared_ptr<CSprite> newBg(new CSprite(bg));
	m_pBackgroundSprite = newBg;
}

/***********************
* AddToSpriteList: Add sprite to the scene's spritelist
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _spr - sprite to add to sprite list
***********************/
void CScene::AddToSpriteList(std::shared_ptr<CSprite> _spr)
{
	m_pSpriteList.push_back(_spr);
}

/***********************
* AddToTextList: Add text to the scene's textlist
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _txt - txt to add to text list
***********************/
void CScene::AddToTextList(std::shared_ptr<CTextLabel> _txt)
{
	m_pTextList.push_back(_txt);
}

/***********************
* AddToEnemyList: Add enemy to the scene's enemyList
* @author: Vivian Ngo
* @date: 08/05/18
* @parameter: _ene - enemy to add to enemy list
***********************/
void CScene::AddToEnemyList(std::shared_ptr<CEnemy> _ene)
{
	m_pEnemyList.push_back(_ene);

}

/***********************
* GetLevelNum: Gets the current level number/scene
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_iLevelNumber - current level/scene
***********************/
int CScene::GetLevelNum()
{
	return m_iLevelNumber;
}

/***********************
* GetPlayer: Player of the scene
* @author: Vivian Ngo
* @date: 08/05/18
* @return: m_pPlayer - player of the scene
***********************/
std::shared_ptr<CPlayer> CScene::GetPlayer()
{
	return m_pPlayer;
}


