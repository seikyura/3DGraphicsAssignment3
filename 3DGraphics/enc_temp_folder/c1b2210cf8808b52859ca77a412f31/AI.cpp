//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "AI.cpp"
// Description	: AI declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "AI.h"

//Initialise instance
CAIManager* CAIManager::s_pAIInstance = 0;

/***********************
* GetInstance: Gets the instance of the Singleton AI class
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @return: s_pAIInstance - Instance of the AI singleton class
***********************/
CAIManager * CAIManager::GetInstance()
{
	if (s_pAIInstance == 0)
	{
		s_pAIInstance = new CAIManager();
	}
	return s_pAIInstance;
}

/***********************
* DestroyInstance: Destroys AI manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
***********************/
void CAIManager::DestroyInstance()
{
	if (s_pAIInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pAIInstance;
		s_pAIInstance = nullptr;
	}
}

/*
seek arrival pathfinding obstacle avoidance
*/

/***********************
* Seek: AI that seeks the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::BouncyBall(std::shared_ptr<CEnemy> _en)
{
	_en->m_pos->x = _en->m_pos->x + _en->m_vel->x;
	_en->m_pos->z = _en->m_pos->z + _en->m_vel->z;

	_en->Update();


	if ((_en->GetXPos() > SCR_RIGHT) || (_en->GetXPos() < SCR_LEFT))
	{
		_en->m_vel->x *= -1;
	}
	if ((_en->GetZPos() > SCR_BOT) || (_en->GetZPos() < SCR_TOP))
	{
		_en->m_vel->z *= -1;
	}
}

/***********************
* Seek: AI that seeks the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Seek(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	glm::vec3 desiredVelocity = _player->GetSprite()->GetPos() - enS->GetPos();
	desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);

	glm::vec3 steer = desiredVelocity - enS->GetVel();
	steer /= m_mass;

	glm::vec3 finalVelocity = enS->GetVel() + steer;
	enS->SetVel(finalVelocity);
	enS->Translate(enS->GetPos() + enS->GetVel());
}

/***********************
* Flee: AI that flees the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Flee(std::shared_ptr<CPlayer> _player, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	if (glm::distance(_player->GetSprite()->GetPos(), enS->GetPos()) < 70.0f)
	{
		glm::vec3 desiredVelocity = enS->GetPos() - _player->GetSprite()->GetPos();
		desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);

		glm::vec3 steer = desiredVelocity - enS->GetVel();
		steer /= m_mass;

		glm::vec3 finalVelocity = enS->GetVel() + steer;
		enS->SetVel(finalVelocity);

		if ((_enemy->GetXPos() > SCR_RIGHT) || (_enemy->GetXPos() < SCR_LEFT))
		{
			enS->SetVel(glm::vec3(enS->GetVel().x * -1, enS->GetVel().y, enS->GetVel().z));
		}
		if ((_enemy->GetZPos() > SCR_BOT) || (_enemy->GetZPos() < SCR_TOP))
		{
			enS->SetVel(glm::vec3(enS->GetVel().x, enS->GetVel().y, enS->GetVel().z * -1));
		}

		enS->Translate(enS->GetPos() + enS->GetVel());
	}
	else
	{
		Seek(_player, _enemy);
	}

	
}