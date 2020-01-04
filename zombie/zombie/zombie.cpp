// zombie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
	enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
	State state = State::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Default);
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;
	Time gameTimeTotal;
	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	Player player;
	IntRect arena;
	
	while (window.isOpen()) {
		//###################################
		// INPUT
		//###################################
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING)
				{

				}
			}
		} // End Events

		// Player Movement %%%%%%%%%%%%%%%%%%%%%%%%%%%%
		if (Keyboard::isKeyPressed(Keyboard::Escape)){window.close();}

		if (state == State::PLAYING)
		{
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.moveUp();
			}
			else {player.stopUp();}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.moveDown();
			}
			else { player.stopDown(); }

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.moveLeft();
			}
			else { player.stopLeft(); }

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.moveRight();
			}
			else { player.stopRight(); }
		} // End of WASD controls

		// Level Up %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		if (state == State::LEVELING_UP)
		{
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}

			if (state == State::PLAYING) {
				arena.width = 500;
				arena.height = 500;
				arena.top = 0;
				arena.left = 0;

				int tileSize = 50;
				player.spawn(arena, resolution, tileSize);
				clock.restart();

			}
		} // End Level Up
			
		// ################################
		// Frame Updating
		//#################################
		if (state == State::PLAYING)
		{
			Time dt = clock.restart();
			gameTimeTotal += dt;

			float dtSec = dt.asSeconds();

			mouseScreenPosition = Mouse::getPosition();
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			player.update(dtSec, Mouse::getPosition());
			Vector2f playerPosition(player.getCenter());
			mainView.setCenter(player.getCenter());

		} // End Update Frames

		// ##################################
		// Draw Scene
		// ##################################
		if (state == State::PLAYING)
		{
			window.clear();
			window.setView(mainView);

			window.draw(player.getSprite());
		}

		if (state == State::LEVELING_UP) {

		}

		if (state == State::PAUSED) {

		}

		if (state == State::GAME_OVER) {

		}

		window.display();

	} //End of while

    return 0;
}

