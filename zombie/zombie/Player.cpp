#include "Player.h"

Player::Player()
{
	m_Speed = START_HLT;
	m_Health = START_HLT;
	m_MaxHealth = START_HLT;

	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	m_TileSize = tileSize;
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPD;
	m_Health = START_HLT;
	m_MaxHealth = START_HLT;
}

Time Player::getLastHitTime()
{
	return m_LastHit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation;
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (m_UpPressed) {
		m_Position.y -= m_Speed*elapsedTime;
	}
	if (m_DownPressed) {
		m_Position.y += m_Speed*elapsedTime;
	}
	if (m_RightPressed) {
		m_Position.x -= m_Speed*elapsedTime;
	}
	if (m_LeftPressed) {
		m_Position.x += m_Speed*elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	if (m_Position.x > m_Arena.width - m_TileSize){
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position.x < m_Arena.width + m_TileSize) {
		m_Position.x = m_Arena.width + m_TileSize;
	}

	if (m_Position.y > m_Arena.width - m_TileSize) {
		m_Position.y = m_Arena.width - m_TileSize;
	}
	if (m_Position.y < m_Arena.width + m_TileSize) {
		m_Position.y = m_Arena.width + m_TileSize;
	}

	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, 
		mousePosition.x - m_Resolution.x / 2) * 180) / 3.1415;
	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	m_Speed += (START_SPD*0.2);
}

void Player::upgradeHealth()
{
	m_Health += (START_HLT*0.2);
}

void Player::increaseHealth(int amount)
{
	if ((m_Health + amount) <= m_MaxHealth) {
		m_Health += amount;
	}
}

Player::~Player()
{
}