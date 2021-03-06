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
#include "Time.h"

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
void CAIManager::BouncyBall(std::shared_ptr<CEnemy> _enemy)
{
	_enemy->SetXPos(_enemy->GetXPos() + _enemy->GetSprite()->GetVel().x);
	_enemy->SetZPos(_enemy->GetZPos() + _enemy->GetSprite()->GetVel().z);

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);
}

/***********************
* Seek: AI that seeks the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Seek(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	//Calculate a desire velocity so enemy knows not to directly travel to the player
	glm::vec3 desiredVelocity = _target - enS->GetPos();

	//Make sure desiredVelocity is not at 0 or normalize will break it
	if (glm::length(desiredVelocity) != 0.0f)
	{
		desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);
	}
	else
	{
		//Set as 0 instead of normalizing it
		desiredVelocity = glm::vec3();
	}

	//Calculate a steer which will allow the AI to decrease 
	//the angle/distance slowly instead of heading straight towards the target
	glm::vec3 steer = desiredVelocity - enS->GetVel();
	steer /= m_mass;

	//Calculate final velocity by adding the steer to the current velocity
	glm::vec3 finalVelocity = enS->GetVel() + steer;

	//Make sure velocity does not exceed maximum velocity
	if (glm::length(finalVelocity) > m_maxVelocity)
	{
		finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
	}

	enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);

	//Apply to enemy
	enS->Translate(enS->GetPos() + enS->GetVel());
}

/***********************
* Flee: AI that flees the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Flee(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();
	
	glm::vec3 desiredVelocity = enS->GetPos() - _target;

	//If the player is within the radius of the enemy, evade
	if (glm::length(desiredVelocity) < m_radius)
	{
		//Calculate a desired velocity so enemy knows not to directly travel to the player
		if (glm::length(desiredVelocity) != 0.0f)
		{
			desiredVelocity = (glm::normalize(desiredVelocity) * m_maxVelocity);
		}
		else
		{
			//Set as 0 instead of normalizing it
			desiredVelocity = glm::vec3();
		}

		//Calculate a steer which will allow the AI to decrease 
		//the angle/distance slowly instead of heading straight away from the target
		glm::vec3 steer = desiredVelocity - enS->GetVel();
		steer /= m_mass;

		//Calculate final velocity by adding the steer to the current velocity
		glm::vec3 finalVelocity = enS->GetVel() + steer;

		//Make sure velocity does not exceed maximum velocity
		if (glm::length(finalVelocity) > m_maxVelocity)
		{
			finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
		}

		enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

		//Calculate boundaries so enemy does not leave the game space
		CheckBoundaries(_enemy);

		//Apply to enemy
		enS->Translate(enS->GetPos() + enS->GetVel());
	}
	else
	{
		//If enemy is outside the evade zone, seek (so enemy doesnt stay still)
		Seek(_target, _enemy);
	}
}

/***********************
* Arrival: AI that slows down as it arrives at a destination
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Arrival(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	//Calculate a desired velocity so enemy knows not to directly travel to the player
	glm::vec3 desiredVelocity = _target - enS->GetPos();

	//Calculate a desire velocity so enemy knows not to directly travel away from the player
	if (glm::length(desiredVelocity) != 0.0f)
	{
		if (glm::length(desiredVelocity) < m_radius)
		{
			//Slow down gradually so AI arrives at player perfectly without overshooting
			desiredVelocity = glm::normalize(desiredVelocity) * m_maxVelocity 
						   * (glm::length(desiredVelocity) / m_radius);
		}
		else
		{
			//Speed to target at max speed if distance is higher than radius of target
			desiredVelocity = glm::normalize(desiredVelocity) * m_maxVelocity;
		}
	}
	else
	{
		//Set as 0 instead of normalizing it
		desiredVelocity = glm::vec3();
	}

	//Calculate a steer which will allow the AI to decrease 
	//the angle/distance slowly instead of heading straight towards the target
	glm::vec3 steer = desiredVelocity - enS->GetVel();
	steer /= m_mass;

	glm::vec3 finalVelocity = glm::vec3();

	//Calculate final velocity by adding the steer to the current velocity
 	finalVelocity = enS->GetVel() + steer;

	//Make sure velocity does not exceed maximum velocity
	if (glm::length(finalVelocity) > m_maxVelocity)
	{
		finalVelocity = glm::normalize(finalVelocity) * m_maxVelocity;
	}
	enS->SetVel(finalVelocity); //Set final velocity to the AI's velocity

	//Calculate boundaries so enemy does not leave the game space
	CheckBoundaries(_enemy);

	enS->Translate(enS->GetPos() + enS->GetVel());	//Apply to enemy
}

void CAIManager::PathFollowing(std::vector<glm::vec3> _obstList, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	glm::vec3 target = _obstList[_enemy->targetListNum];

	if (Distance(enS->GetPos(), target) <= m_pathRadius) {
		_enemy->targetListNum += 1;

		if (_enemy->targetListNum >= _obstList.size()) {
			_enemy->targetListNum = 0;
		}
	}
	Seek(target, _enemy);
}

/***********************
* Wander: AI that Wanders
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _player - player to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Wander(std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	m_wanderEnd = CTime::GetCurTimeSecs();
	//m_wanderStart = CTime::GetCurTimeSecs();

	if (m_wanderEnd - m_wanderStart > 1.0f)
	{
		int x = (int)_enemy->GetXPos();
		int z = (int)_enemy->GetZPos();

		x = rand() % (int)SCR_RIGHT;
		z = rand() % (int)SCR_BOT;

		int r = rand() % 2;
		int r2 = rand() % 2;

		if (r == 1)
			x *= -1;

		if (r2 == 1)
			z *= -1;

		randWander = { x, 0.0f, z };

		m_wanderStart = CTime::GetCurTimeSecs();
	}
	Seek(randWander, _enemy);
}

/***********************
* Pursuit: AI that Pursuits the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _target - _target to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Pursuit(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy)
{
	glm::vec3 dist = _target->GetSprite()->GetPos() - _enemy->GetSprite()->GetPos();
	float ahead = glm::length(dist) / m_maxVelocity;
	glm::vec3 futurePos = _target->GetSprite()->GetPos() + (_target->GetSprite()->GetVel() * ahead);
	Seek(futurePos, _enemy);
}

/***********************
* Evade: AI that Evades the player
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _target - _target to search
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::Evade(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy)
{
	glm::vec3 dist = _target->GetSprite()->GetPos() - _enemy->GetSprite()->GetPos();
	float l = glm::length(dist);
	float ahead = l / m_maxVelocity;
	glm::vec3 futurePos = _target->GetSprite()->GetPos() + (_target->GetSprite()->GetVel() * ahead);
	Flee(futurePos, _enemy);
}

void CAIManager::WallFollowing(std::vector<glm::vec3> points, std::shared_ptr<CEnemy> _enemy)
{
	std::shared_ptr<CSprite> enS = _enemy->GetSprite();

	glm::vec3 target = points[_enemy->targetListNum];

	if (Distance(enS->GetPos(), target) <= m_pathRadius) 
	{
		_enemy->targetListNum += 1;

		if (_enemy->targetListNum >= points.size()) 
		{
			_enemy->targetListNum = 0;
		}
	}
	Seek(target, _enemy);
}

/***********************
* CheckBoundaries: Checks the boundaries of the AI
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _enemy - enemy to apply AI to
***********************/
void CAIManager::CheckBoundaries(std::shared_ptr<CEnemy> _enemy)
{
	//If AI is horizontally out of boundaries, reverse the velocity (simulate bounce back)
	if ((_enemy->GetXPos() >= SCR_RIGHT) || (_enemy->GetXPos() <= SCR_LEFT))
	{
		if (_enemy->GetXPos() <= SCR_LEFT)
		{
			_enemy->SetXPos(SCR_LEFT);
		}

		if (_enemy->GetXPos() >= SCR_RIGHT)
		{
			_enemy->SetXPos(SCR_RIGHT);
		}

		_enemy->GetSprite()->SetVel(glm::vec3(
			_enemy->GetSprite()->GetVel().x * -1,
			_enemy->GetSprite()->GetVel().y,
			_enemy->GetSprite()->GetVel().z)
		);
	}

	//If AI is vertically out of boundaries, reverse the velocity (simulate bounce back)
	if ((_enemy->GetZPos() >= SCR_BOT) || (_enemy->GetZPos() <= SCR_TOP))
	{
		if (_enemy->GetZPos() <= SCR_TOP)
		{
			_enemy->SetZPos(SCR_TOP);
		}

		if (_enemy->GetZPos() >= SCR_BOT)
		{
			_enemy->SetZPos(SCR_BOT);
		}
		_enemy->GetSprite()->SetVel(glm::vec3(
			_enemy->GetSprite()->GetVel().x,
			_enemy->GetSprite()->GetVel().y,
			_enemy->GetSprite()->GetVel().z * -1)
		);
	}
}

/***********************
* FindClosestPoint: Finds the vector that is closest to the given position
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08 / 05 / 18
* @parameter: _enemy - enemy to apply AI to
***********************/
int CAIManager::FindClosestPoint(std::vector<glm::vec3> _obstList, glm::vec3 _AI)
{
	int lowest = 100;
	for (unsigned int i = 0; i < _obstList.size(); ++i)
	{
		if (glm::distance(_obstList[i], _AI) < lowest)
		{
			lowest = i;
		}
	}
	return lowest;
}

float CAIManager::Distance(glm::vec3 a, glm::vec3 b)
{
	return glm::sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z));;
}