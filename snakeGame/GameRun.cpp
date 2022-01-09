#include "sgpch.h"
#include "GameRun.h"


GameRun::GameRun(uint8_t tiles)
{
	this->gameState = PLAYING;
	this->tiles = tiles;
	this->player = new Player(sf::Vector2i(5,5),&this->tiles);
	this -> applePosition = this->unocuppiedConstant;

	this->mainTickClock = new tickClock(this->startMaxTick);
	this->deathTickClock = new tickClock();
	backgroundMap.resize(tiles);
	for (int i = 0; i < tiles; i++) backgroundMap[i].resize(tiles);

	tileState.resize(tiles);
	for (int i = 0; i < tiles; i++) tileState[i].resize(tiles);

	this->score = 0;
	setBackground();

	this->appleSprite.setTexture(GameResources::appleTexture);
	this->setNextAppleTicks();

}
void GameRun::UpdateTileState()
{
	sf::Vector2i oldTailPosition = this->player->getOldTailPosition();
	assert(oldTailPosition.x >= 0 && oldTailPosition.x < tiles);
	assert(oldTailPosition.y>= 0 && oldTailPosition.y < tiles);
	this->tileState[oldTailPosition.x][oldTailPosition.y] = EMPTY;
	sf::Vector2i v = this->player->getHeadPosition();
	assert(v.x >= 0 && v.x < tiles);
	assert(v.y >= 0 && v.y < tiles);
	this->tileState[v.x][v.y] = SNAKE;
}
void GameRun::setBackground()
{
	for (int i = 0; i < this->tiles; i++)
	{
		for (int j = 0; j < this->tiles; j++)
		{
			sf::RectangleShape *square = new sf::RectangleShape();
			*square = GameResources::backgroundMapSquare;
			square->setPosition(sf::Vector2f(float(i * GameResources::tilePixelSize), float(j * GameResources::tilePixelSize)));
			square->move(this->mapRenderPosition);
			backgroundMap[i][j] = square;
		}
	}

}
void GameRun::update()
{
	switch (this->gameState)
	{
		case PLAYING:
		this->PlayGameLoop();
		break;
		case DIED:
		this->DeathGameLoop();
		break;
		case WAITINGFOR_END:
		this->DelayAfterForNewGame -= GameTime::deltaTime;
		if (this->DelayAfterForNewGame <= 0) gameState = END;
		break;
	}
	for (auto &particleSystem : segmentsDeathParticles)
	{
		particleSystem->update();
		if (particleSystem->toDestroy);
	}
}

void GameRun::render(sf::RenderWindow* window)
{

	float scale = GameResources::getScale();
	for (int i = 0; i < tiles; i++)
	{
		for (int j = 0; j < tiles; j++)
		{
			window->draw(*this->backgroundMap[i][j]);
		}
	}
	if (this->applePosition != this->unocuppiedConstant)
	{
		this->appleSprite.setScale(sf::Vector2f(scale, scale));
		appleSprite.setPosition(sf::Vector2f(GameResources::tilePixelSize * applePosition.x, GameResources::tilePixelSize * applePosition.y));
		appleSprite.move(this->mapRenderPosition);
		window->draw(appleSprite);
	}
	for (auto segment : player->getSegments())
	{
		segment.sprite.setScale(sf::Vector2f(scale, scale));
		segment.sprite.setPosition(player->getRenderedSegmentPosition(segment));
		segment.sprite.move(this->mapRenderPosition);
		window->draw(segment.sprite);
	}
	for(auto &particleSystem:segmentsDeathParticles)
	{
		particleSystem->render(window);
	}
	/*Draw Scoreboard*/
	//SCORE
	sf::Text text;
	text.setFont(GameResources::gameFont);
	text.setString("Score");
	text.setCharacterSize(20);
	text.setPosition(sf::Vector2f(10, 5));
	window->draw(text);
	//SCORE VALUE
	std::string score = std::to_string(this->score);
	text.setString(score);
	text.setPosition(sf::Vector2f(105, 5));
	window->draw(text);
	//SPEED
	text.setString("Speed");
	text.setPosition(sf::Vector2f(260, 5));
	window->draw(text);
	//SPEED VALUE
	std::string prc = std::to_string(getSpeedPercentage());
	text.setString(prc);
	text.setPosition(sf::Vector2f(365, 5));
	window->draw(text);
}

bool GameRun::gameHasEnded() { return gameState == END; }


void GameRun::playerInput()
{
	if (this->inputBlocked) return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player->getFacing() != RIGHT)player->setFacing(LEFT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player->getFacing() != DOWN)player->setFacing(UP);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player->getFacing() != UP)player->setFacing(DOWN);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player->getFacing() != LEFT)player->setFacing(RIGHT);
	else return;
	this->inputBlocked = true;
}
void GameRun::PlayGameLoop()
{
	this->playerInput();
	if (this->mainTickClock->isOnTick()) {
		eatAppleIfCan();
		this->player->Move();
		this->UpdateTileState();
		if (this->ticksForSpeed <= 0)
		{
			mainTickClock->setMaxTick(std::max(this->mainTickClock->getMaxTick() - 0.0001f, 0.025f));
			setNextTimeSpeedUpTicks();
		}
		if (this->ticksForApple > 0)--this->ticksForApple;
		--this->ticksForSpeed;
		this->inputBlocked = false;
		if (this->ticksForApple == 0)spawnApple();
		if (this->hasDied()) {
			this->deathTickClock->setMaxTick(this->deathAnimationTime / this->player->getSegments().size());
			this->gameState = DIED;
		}
		#ifdef  DEBUG


		for (int i = 0;i<tiles;i++)
		{
			for (int j = 0;j<tiles;j++)
			{
				if (j == player->getOldTailPosition().x && i == player->getOldTailPosition().y)std::cout << "T ";
				else
				std::cout << tileState[j][i] << " ";
			}
			std::cout << "\n";
		}
		//Sleep(100);
		system("cls");
		#endif 
	}
	this->mainTickClock->update();
}
void GameRun::DeathGameLoop()
{
	if (this->deathTickClock->isOnTick())
	{
		if (this->player->getSegments().size() > 0)
		{
			uint8_t particleNumber = GameResources::getRandomInt(100, 200);
			segmentsDeathParticles.push_back(new ParticleSystem(
				particleNumber,
				player->getRenderedSegmentPosition(player->getSegments()[0]) + this->mapRenderPosition,
				1.f
			)
			);
			this->player->popHeadSegment();
		}
		else
		{
			gameState = WAITINGFOR_END;
		}
	}
	this->deathTickClock->update();
}
const bool GameRun::hasDied()
{
	return player->hasCollidedWithSelf();
}
void GameRun::setNextAppleTicks()
{
	this->ticksForApple = GameResources::getRandomInt(10, 20);
}
void GameRun::setNextTimeSpeedUpTicks()
{
	this->ticksForSpeed = GameResources::getRandomInt(4, 10);
}
const int GameRun::getSpeedPercentage()
{
	return (int)(startMaxTick * 100 / this->mainTickClock->getMaxTick());
}
sf::Vector2i GameRun::getUnocuppiedPosition()
{
	int x = GameResources::getRandomInt(0, tiles - 1);
	int y = GameResources::getRandomInt(0, tiles- 1);
	for (int i = 0; i < tiles*tiles; i++)
	{
		if (tileState[x][y] == EMPTY)break;
		y = (y+(x + 1) / tiles)%tiles;
		x = (x + 1) % tiles;
	
	}
	assert(x >= 0 && x < tiles);
	assert(y >= 0 && y < tiles);
	return sf::Vector2i(x,y);
}
void GameRun::spawnApple()
{
	this->applePosition = getUnocuppiedPosition();
	tileState[this->applePosition.x][this->applePosition.y] = APPLE;
	this->ticksForApple = -1;

}

void GameRun::eatAppleIfCan()
{
	if (this->player->getHeadPosition() == this->applePosition)
	{
		this->score += getSpeedPercentage();
		this->applePosition = this->unocuppiedConstant;
		this->setNextAppleTicks();
		this->player->addSegment();
	}
}
GameRun::~GameRun()
{
	for (int i = 0; i < tiles; i++)
	{
		for (int j = 0; j < tiles; j++) delete backgroundMap[i][j];
	}
	delete player;
	for(auto &particle:segmentsDeathParticles)
	{
		delete particle;
	}
	segmentsDeathParticles.clear();
}
