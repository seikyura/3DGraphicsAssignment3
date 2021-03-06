#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "PowerUp.h"
// Description	: PowerUp declaration file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#include "Player.h"
#include "Enemy.h"

//
//struct location
//{
//	float x;
//	float y;
//};

class CAIManager
{
public:
	static CAIManager* GetInstance();
	static void DestroyInstance();
	~CAIManager() {};

	void BouncyBall(std::shared_ptr<CEnemy> _enemy);
	void Seek(glm::vec3 _target, std::shared_ptr<CEnemy> _enemy);
	void Flee(glm::vec3 _target, std::shared_ptr<CEnemy>  _enemy);
	void Arrival(glm::vec3 _target, std::shared_ptr<CEnemy>  _enemy);
	void PathFollowing(std::vector<glm::vec3> _obstList, std::shared_ptr<CEnemy>  _enemy);
	void Wander(std::shared_ptr<CEnemy> _enemy);
	void Pursuit(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy);
	void Evade(std::shared_ptr<CPlayer> _target, std::shared_ptr<CEnemy> _enemy);
	void WallFollowing(std::vector<glm::vec3> points, std::shared_ptr<CEnemy>  _enemy);

	void CheckBoundaries(std::shared_ptr<CEnemy>  _enemy);
	int FindClosestPoint(std::vector<glm::vec3> _obstList, glm::vec3 _AI);
	float Distance(glm::vec3 _i, glm::vec3 _j);
	glm::vec3 randWander;

private:
	static CAIManager* s_pAIInstance;
	CAIManager() {};

	float m_maxVelocity = 0.6f;
	float m_maxforce = 1.0f;
	float m_mass = 100.0f;
	float m_radius = 50.0f;
	float m_pathRadius = 10.0f;
	float m_maxSeeAhead = 20.0f;
	float m_avoidanceForce = 1.0f;
	float m_maxAvoidanceForce = 5.0f;
	float m_wanderStart = 0.0f;
	float m_wanderEnd = 0.0f;
};

