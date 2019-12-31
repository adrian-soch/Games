// Author: Adrian Sochaniwsky
// Date: December 30, 2019
// From: Linkedin Learning Course: C++ Game Programming 1

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{
	VideoMode vm(1920, 1080); //Creating VideoMode object
	RenderWindow window(vm, "Timber", Style::Resize); //Creating window

	// Setting Background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Setting Tree
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Setting Bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(-100, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	// Setting Cloud
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud;
	spriteCloud.setTexture(textureCloud);
	spriteCloud.setPosition(-300, 0);
	bool cloudActive = false;
	float cloudSpeed = 0.0f;

	// Setting Cloud1
	Sprite spriteCloud1;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud1.setPosition(-300, 250);
	bool cloud1Active = false;
	float cloud1Speed = 0.0f;

	// Setting Cloud2
	Sprite spriteCloud2;
	spriteCloud2.setTexture(textureCloud);
	spriteCloud2.setPosition(-300, 500);
	bool cloud2Active = false;
	float cloud2Speed = 0.0f;

	int score = 0;
	Text message;
	Text scoreText;

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	message.setFont(font);
	scoreText.setFont(font);
	message.setString("Press Enter to start...");
	scoreText.setString("Score = 0");
	message.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	message.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = message.getLocalBounds();
	message.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	message.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	Clock clock;
	bool paused = true;

	RectangleShape timeBar;
	float timeBarStart = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStart, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStart / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidth = timeBarStart / timeRemaining;

	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;

	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deadBuffer;
	deadBuffer.loadFromFile("sound/death.wav");
	Sound dead;
	dead.setBuffer(deadBuffer);

	SoundBuffer outBuffer;
	outBuffer.loadFromFile("sound/out_of_time.wav");
	Sound out;
	out.setBuffer(outBuffer);

	updateBranches(1);
	updateBranches(22);
	updateBranches(333);
	updateBranches(4444);
	updateBranches(55555);

	while (window.isOpen()) {
		// ###########################################
		//		PLAYER INPUT
		// ###########################################
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = false;

			score = 0;
			timeRemaining = 5;

			for (int i = 0; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}
			spriteRIP.setPosition(675, 2000);

			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}

		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				chop.play(); // Sound Effect
				playerSide = side::RIGHT;
				score++;
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				chop.play(); // Sound Effect
				playerSide = side::LEFT;
				score++;
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;
				acceptInput = false;
			}
		}
		// ###########################################
		//		SCENE UPDATE
		// ###########################################
		if (!paused) {

			Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidth * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				paused = true;
				message.setString("Out of Time");

				FloatRect textRect = message.getLocalBounds();
				message.setOrigin(
					textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				message.setPosition(1920 / 2.0f, 1080 / 2.0f);

				out.play(); // Sound Effect
			}
			if (!beeActive) {
				srand((int)time(0) * 10);
				int rtime = rand();
				beeSpeed = (rtime % 200) + 200;

				float height = (rtime % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else {
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < -100) {
					beeActive = false;
				}
			}

			if (!cloudActive) {
				srand((int)time(0) * 11);
				int rtime = rand();
				cloudSpeed = (rtime % 200);

				float height = (rtime % 150);
				spriteCloud.setPosition(-300, height);
				cloudActive = true;
			}
			else {
				spriteCloud.setPosition(
					spriteCloud.getPosition().x + (cloudSpeed*dt.asSeconds()),
					spriteCloud.getPosition().y);
				if (spriteCloud.getPosition().x > 1920) {
					cloudActive = false;
				}
			}

			if (!cloud1Active) {
				srand((int)time(0) * 14);
				int rtime = rand();
				cloud1Speed = (rtime % 200);

				float height = (rtime % 300) - 150;
				spriteCloud1.setPosition(1920, height);
				cloud1Active = true;
			}
			else {
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x - (cloud1Speed*dt.asSeconds()),
					spriteCloud1.getPosition().y);
				if (spriteCloud1.getPosition().x <-300) {
					cloud1Active = false;
				}
			}

			if (!cloud2Active) {
				srand((int)time(0) * 8);
				int rtime = rand();
				cloud2Speed = (rtime % 200);

				float height = (rtime % 450) - 150;
				spriteCloud2.setPosition(-300, height);
				cloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed*dt.asSeconds()),
					spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(3000, height);
				}
			}

			if (logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX*dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY*dt.asSeconds()));
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}
			if (branchPositions[5] == playerSide) {
				paused = true;
				acceptInput = false;
				spritePlayer.setPosition(2000, 660);
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
				spriteRIP.setPosition(525, 760);
				message.setString("You died");
				FloatRect textRect = message.getLocalBounds();
				message.setOrigin(textRect.left + textRect.width / 2.0f, 
					textRect.top + textRect.height/2.0f);
				message.setPosition(1920 / 2.0f, 1080 / 2.0f);
				dead.play(); // Sound Effect
			}
		} // End if(!paused)
		// #############################################
		//		Draw Scene
		// #############################################
		window.clear(); // CLear screen

		window.draw(spriteBackground); // Must be first (i.e. behind)

		window.draw(spriteCloud);
		window.draw(spriteCloud1);		
		window.draw(spriteCloud2);

		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		window.draw(spriteTree);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);
		window.draw(spriteBee);

		window.draw(scoreText);

		window.draw(timeBar);
		if (paused) {
			window.draw(message);
		}
		window.display(); // Update Screen
	}
	return 0;
}

void updateBranches(int seed) {
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}

