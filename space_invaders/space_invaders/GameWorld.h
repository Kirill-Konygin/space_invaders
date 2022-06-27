#pragma once

#include "Sprite.h"
#include "Image.h"

#include "Shader.h"

#include <filesystem>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <vector>
#include "GraphicsComponent.h"

#include "Player.h"

#include <cstdlib>

#include "GameObject.h"

#include "InvandersGroup.h"
#include "Projectiles.h"
#include "EventSystem.h"
#include "CollisionSystem.h"
#include "TextDrawer.h"
#include  <string>

#include "Configuration.h"




class GameWorld
{
public:

	GameWorld(const Configuration& config, Commands& commands);

	void render();
	void update();	
	
	bool gameEnd();
private:

	void reset();
	void createField(int width, int height, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);	
	

	void invandersShootingSytstem();
	
	Shader shader;

	Sprite backgroundSprite;
	
	Sprite invandersProjectileSprite;	
	Sprite playerProjectileSprite;

	Sprite PlayerSprite;
	std::vector<std::pair<Sprite,Sprite>> invanderSprites;

	CollisionSystem collisionSystem;

	float leftBorder, rightBorder, bottomBorder, topBorder;	

	double currentTime;
	double accumulator;
	double S_PER_UPDATE;

	Player player;
	InvandersGroup invanders;
	Projectiles invandersProjectiles;
	Projectiles playerProjectiles;

	GameObject background;	
	
	Commands& m_commands;

	

	const Configuration& m_config;

	TextDrawer score;
	TextDrawer life;

	bool m_gameEnd=false;

	
};
