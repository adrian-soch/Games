#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Zombies.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		//Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_Speed = 40;
		m_Health = 5;
		break;
	case 1:
		//Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_Speed = 70;
		m_Health = 1;
		break;
	case 2:
		//Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_Speed = 20;
		m_Health = 3;
		break;
	default:
		break;
	}

	srand((int)time(0) * seed);
	float modifier = (rand() % MAX_VARIENCE) + OFFSET;

	modifier /= 100;
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);

}

bool Zombie::hit() {
	m_Health--;
	if (m_Health < 0) {
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}
	return false;
}
bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
	return m_Sprite;
}
void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x + m_Speed*elapsedTime;
	}
	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y + m_Speed*elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x - m_Speed*elapsedTime;
	}
	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y - m_Speed*elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x) * 180) / 3.1415;
	m_Sprite.setRotation(angle);
}
{

}