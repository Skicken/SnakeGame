#include "sgpch.h"
#include "Player.h"

float extern DirectionToAngle(direction dir)
{
	return (uint8_t)dir * 90.f;
}
sf::Vector2i extern DirectionToPoint(direction dir)
{
	switch (dir)
	{
	case UP:
		return sf::Vector2i(0, -1);
		break;
	case DOWN:
		return sf::Vector2i{ 0,1 };
		break;
	case LEFT:
		return sf::Vector2i{ -1,0 };
		break;
	case RIGHT:
		return sf::Vector2i{ 1,0 };
		break;
	default:
		return sf::Vector2i{ 0,0 };
	}
}
const bool Player::hasCollidedWithSelf()
{
	for (int i = 1;i<snake.size();i++)
	{
		if (snake[i].position == snake.front().position) return true;
	}
	return false;
}

Player::Player(sf::Vector2i startingPos, uint8_t *tiles,uint8_t segments)
{
	this->tiles = tiles;
	this->facing = RIGHT;
	this->snake.push_back(Segment{sf::Sprite(GameResources::headTexture),this->facing,startingPos});
	for (int i = 1; i < segments-1; i++)
	{		
		this->snake.push_back(Segment{ 
			 sf::Sprite(GameResources::segmentTexture),
			this->facing,
			sf::Vector2i(this->snake.front().position.x-i,this->snake[0].position.y)
			});
		
	}
	this->snake.push_back(Segment{
		sf::Sprite(GameResources::tailTexture),
		this->facing,
		sf::Vector2i(this->snake.front().position.x - segments + 1,this->snake[0].position.y) 
		});
	this->setOrigin();
	this->oldTailPosition = this->getTailPosition();

}

void Player::setFacing(direction dir)
{
	this->facing = dir;
}

direction Player::getFacing()
{
	return this->facing;
}

sf::Vector2i Player::getHeadPosition() {
	return snake.front().position;
}

sf::Vector2i Player::getTailPosition()
{
	return snake.back().position;
}



std::vector<Segment>& Player::getSegments()
{
	return snake;
}

void Player::Move()
{
	this->setOrigin();
	this->oldTailPosition = this->getTailPosition();
	for (size_t i = snake.size()-1; i >0; i--)
	{
		this->snake[i].position = this->snake[i-1].position;	
		this->snake[i].spriteDirection = this->snake[i - 1].spriteDirection;

	}
	this->snake.front().spriteDirection = this->facing;
	this->snake.front().sprite.setRotation(DirectionToAngle(this->facing));
	this->snake.front().position += DirectionToPoint(this->facing);
	this->snake[snake.size() - 1].sprite.setRotation(DirectionToAngle(this->snake[snake.size() - 2].spriteDirection));
	for (unsigned int i = snake.size() - 2; i > 0; i--)
	{
		if (this->snake[i - 1].spriteDirection != this->snake[i].spriteDirection)
		{
			this->snake[i].sprite.setTexture(GameResources::cornerTexture);
			float cornerRot = getCornerRotation(this->snake[i].spriteDirection, this->snake[i - 1].spriteDirection);
			this->snake[i].sprite.setRotation(cornerRot);
		}
		else 
		{
			this->snake[i].sprite.setTexture(GameResources::segmentTexture);
			this->snake[i].sprite.setRotation(DirectionToAngle(this->snake[i].spriteDirection));
		}
	}
	this->passBorderPosition(this->snake.front().position);
}

void Player::setOrigin()
{
	for (auto& segment : snake) {
		float height = segment.sprite.getGlobalBounds().height / 2;
		float width = segment.sprite.getGlobalBounds().width / 2;
		segment.sprite.setOrigin(sf::Vector2f(width, height));
	}
}
float Player::getCornerRotation(direction from, direction to)
{
	
	float A = DirectionToAngle(from);
	float B = DirectionToAngle(to);
	float cornerRotation = 0.f;
	if ((A <= B || (B - A) == -270) && A - B != -270) cornerRotation = B;
	else cornerRotation = B-90;
	return cornerRotation;
}

const float Player::getSpriteOffsetWidth() { return snake.front().sprite.getGlobalBounds().width; }

const float Player::getSpriteOffsetHeight() { return snake.front().sprite.getGlobalBounds().height; }


void Player::popHeadSegment() {

	snake.erase(snake.begin());
}

sf::Vector2f Player::getRenderedSegmentPosition(Segment &segment)
{
	float scale = GameResources::getScale();
	float xPos = segment.position.x * GameResources::tilePixelSize + this->getSpriteOffsetHeight() / 2 * scale;
	float yPos = segment.position.y * GameResources::tilePixelSize + this->getSpriteOffsetWidth() / 2 * scale;

	return sf::Vector2f(xPos,yPos);
}

void Player::addSegment()
{
	sf::Vector2i segmentPosition = this->snake.back().position + DirectionToPoint(this->snake.back
	().spriteDirection);
	this->passBorderPosition(segmentPosition);
	this->snake.back().sprite.setTexture(GameResources::segmentTexture);
	this->snake.push_back(Segment{
		 sf::Sprite(GameResources::tailTexture),
		this->snake.back().spriteDirection,
		segmentPosition
		});
}

void Player::passBorderPosition(sf::Vector2i& position)
{
	if (position.x >= *tiles) position.x = 0;
	if (position.x < 0) position.x = *tiles - 1;
	if (position.y < 0) position.y = *tiles - 1;
	if (position.y >= *tiles) position.y = 0;
}


