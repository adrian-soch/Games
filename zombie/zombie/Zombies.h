#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	const float BLOATER_SPD = 40;
	const float CHASER_SPD = 80;
	const float CRAWLER_SPD = 20;

	const float BLOATER_HLT = 5;
	const float CHASER_HLT = 1;
	const float CRAWLER_HLT = 3;

	const int MAX_VARIENCE = 30;
	const int OFFSET = 101 - MAX_VARIENCE;

	Vector2f m_Position;

	Sprite m_Sprite;
	float m_Speed;
	float m_Health;
	bool m_Alive;

public:
	bool hit();
	bool isAlive();

	void spawn(float startX, float startY, int type, int seed);

	FloatRect getPosition();

	Sprite getSprite();

	void update(float elapsedTime, Vector2f playerLocation);

};