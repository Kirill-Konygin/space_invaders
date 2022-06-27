#pragma once
#include "GameWorld.h"
#include <GLFW/glfw3.h>


GameWorld::GameWorld(const Configuration& config,  Commands& commands) :
	

	m_commands(commands),

	shader(std::experimental::filesystem::path("../shaders/VS/shader.txt").string().c_str(),
		   std::experimental::filesystem::path("../shaders/FS/shader.txt").string().c_str()),

	backgroundSprite(Image(std::experimental::filesystem::path("../images/background.png").string().c_str())),	

	invandersProjectileSprite(Image(std::experimental::filesystem::path("../images/invandersProjectile.png").string().c_str())),
	playerProjectileSprite(Image(std::experimental::filesystem::path("../images/playerProjectile.png").string().c_str())),

	PlayerSprite(Image(std::experimental::filesystem::path("../images/Player.png").string().c_str())),

	invandersProjectiles(config,glm::vec2(0.f,-1.f)),

	playerProjectiles(config, glm::vec2(0.f, 1.f)),

	invanders(config),	

	score(config.SCR_WIDTH,config.SCR_HEIGHT),

	life(config.SCR_WIDTH, config.SCR_HEIGHT),

	m_config(config),	

	player(commands,config)

{	
	
	invanderSprites.emplace_back(std::pair<Sprite, Sprite>(Image(std::experimental::filesystem::path("../images/invander1_state1.png").string().c_str()),
		                                                   Image(std::experimental::filesystem::path("../images/invander1_state2.png").string().c_str())));
	invanderSprites.emplace_back(std::pair<Sprite, Sprite>(Image(std::experimental::filesystem::path("../images/invander2_state1.png").string().c_str()),
		                                                   Image(std::experimental::filesystem::path("../images/invander2_state2.png").string().c_str())));
	invanderSprites.emplace_back(std::pair<Sprite, Sprite>(Image(std::experimental::filesystem::path("../images/invander3_state1.png").string().c_str()),
		                                                   Image(std::experimental::filesystem::path("../images/invander3_state2.png").string().c_str())));

	invandersProjectiles.setSprite(invandersProjectileSprite);
	playerProjectiles.setSprite(playerProjectileSprite);
	

	score.setColor(glm::vec3(1.f, 1.f, 0.f));
	score.setSize(1.f);
	score.setPosition(glm::vec2(0, 0));

	life.setColor(glm::vec3(0.f, 1.f, 1.f));
	life.setSize(1.f);
	life.setPosition(glm::vec2(config.SCR_WIDTH - 130, 0));

	GraphicsComponent graphic;
	graphic.addSprite(backgroundSprite);
	background.setGraphicComponent(std::move(graphic));
	background.setPosition(glm::vec2(0.f, 0.f));

	

	player.set(PlayerSprite, glm::vec2(0.f, -config.height / 2 + 1));

	
	invanders.setInvanders(invanderSprites, config.invandersCount);
	
	currentTime = glfwGetTime();
	accumulator = 0.0;	

	std::srand(static_cast<int>(currentTime));	

	shader.use();

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-(float)config.SCR_WIDTH / 2.f, (float)config.SCR_WIDTH / 2.f, -(float)config.SCR_HEIGHT / 2.f, (float)config.SCR_HEIGHT / 2.f, 0.1f, 1.f);
	shader.setMat4("projection", projection);

	createField(config.width, config.height, config.SCR_WIDTH, config.SCR_HEIGHT);

	invanders.setProjectile(&invandersProjectiles);
	
	player.setProjectile(&playerProjectiles);

}

void GameWorld::render()
{	

	background.render();
	invanders.render();
	invandersProjectiles.render();
	playerProjectiles.render();	
	player.render();
	shader.use();
	backgroundSprite.render();

	
	for(auto& elem : invanderSprites)
	{
		elem.first.render();
		elem.second.render();
	}
	playerProjectileSprite.render();
	invandersProjectileSprite.render();
	PlayerSprite.render();
	score.renderText("Score: " + std::to_string(invanders.getScore()));
	life.renderText("Life: " + std::to_string(player.getLifes()));

}

void GameWorld::update()
{
	
	
	double newTime = glfwGetTime();
	double frameTime = newTime - currentTime;
	currentTime = newTime;

	invanders.update(frameTime);
	player.update(frameTime);

	invandersProjectiles.update(frameTime);
	playerProjectiles.update(frameTime);


	collisionSystem.addGameObjects(playerProjectiles,1);
	collisionSystem.addGameObjects(invandersProjectiles,2);
	collisionSystem.addGameObjects(invanders,2);
	collisionSystem.addGameObjects(player,1);

	collisionSystem.calculate();

	playerProjectiles.processCollision();
	invandersProjectiles.processCollision();
	invanders.processCollision();
	player.processCollision();

	if(player.getLifes()==0 || invanders.getBottomBorder()==bottomBorder)
	{
		m_gameEnd = true;
		return;
	}

	if (invanders.empty())
	{
		reset();
	}
	
}

void GameWorld::createField(int width, int height, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
	float coefficient;
	if (width > height)
	{
		coefficient = static_cast<float>(SCR_WIDTH / width);

	}
	else
	{
		coefficient = static_cast<float>(SCR_HEIGHT / height);

	}

	leftBorder = -width / 2.f;
	rightBorder = width / 2.f;
	bottomBorder = -height / 2.f;
	topBorder = height / 2.f;
	

	shader.setMat4("scale", glm::scale(glm::mat4(1.f), glm::vec3(coefficient, coefficient, 1.f)));
	
	
	background.setSize(glm::vec2(width, height));

}



void GameWorld::invandersShootingSytstem()
{
	std::vector<glm::vec2> attackPos(invanders.getAttackPositions());

	for(auto pos : attackPos)
	{
		if(std::rand()%50+1==1)
		{
			invandersProjectiles.addProjectile(pos);
		}
	}

}

void GameWorld::reset()
{
	invanders.setInvanders(invanderSprites, m_config.invandersCount);	
}

bool GameWorld::gameEnd()
{
	return m_gameEnd;
}