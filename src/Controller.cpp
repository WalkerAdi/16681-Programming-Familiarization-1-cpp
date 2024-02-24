#include "Controller.h"
#include <cmath>
#include <iostream>

// // Comment these and their respective uses out after debugging
// #include <chrono>
// #include <thread>
namespace mrsd
{
	// This function will control the AI based on the state of the game
	void Controller::control(const mrsd::Game& g, float t)
	{
		// Debug Section: Comment out after debugging
		// std::cout << "Start of Control Function" << std::endl;
		// Get the current projectiles
		const std::list<Projectile>& projectiles = g.getProjectiles();
		// Get the predicted impact times and locations of each projectile
		const size_t numProjectiles = projectiles.size();
		std::vector<Prediction> allPreds(numProjectiles);
		int i = 0;
		for (std::list<Projectile>::const_iterator it = projectiles.begin();
				it != projectiles.end(); ++it)
		{
			// Track the projectile
			allPreds[i] = trackProjectile(*it, g);
			++i;
		}

		// // Determine if there are any projectiles
		// if(projectiles.empty())
		// {
		// 	// If there are no projectiles state so
		// 	std::cout << "No projectiles!" << std::endl;
		// }

		// // DONE: Check if the results make sense through observing the console
		// for (int i = 0; i < allPreds.size(); ++i)
		// {
		// 	Prediction pred = allPreds[i];
		// 	if (pred.x < 0 || pred.x > g.getWidth())
		// 	{
		// 		std::cout << "Projectile " << i << " will land outside of the map" << std::endl;
		// 	}
		// 	else
		// 	{
		// 		std::cout << "Projectile " << i << " will hit ground at time " << (pred.t + std::round(g.getGameTime() * 10)/10) << " and x = " << pred.x << std::endl;
		// 	}
		// }

		// Control the player
		// Check if there is a player:
		if(p != 0)
		{
			// If there is a player, move it to a safe spot
			int direction = pickSafeSpot(g);
			p->x = p->x + direction * g.playerSpeed;
		}
		// else
		// {
		// 	// If there is no player, state so
		// 	std::cout << "No Player!" << std::endl;
		// }

	}


	// This function will create a player and add it to the game
	void Controller::createPlayer(Game& g)
	{
		if(p == 0)
		{
			p = new Player();
			p->dead = true;
		}
		if(p->dead)
		{
			p->dead = false;
			p->x = g.getWidth()/2;
			g.newPlayer(p);
		}
	}


	// This function will track the projectile and determine where and when it will hit the ground
	Prediction Controller::trackProjectile(const Projectile& p, const Game& g)
	{
		// Get the projectile properties
		float x = p.x;
		float y = p.y;
		float vx = p.vx;
		float vy = p.vy;
		float gravity = g.getGravity();

		// Predict time of flight:
		float flightTime = (-vy - sqrt(vy*vy - 2*gravity*y))/gravity;

		// Predict x position at time of impact:
		float xImpact = x + vx*flightTime;

		Prediction pred;
		pred.t = flightTime;
		pred.x = std::round(xImpact);
		//std::cout << "Projectile will hit ground at time " << pred.t << " and x = " << pred.x << std::endl;

		return pred;
	}


	// This function will determine the safe spots at time t based on the state of all observed projectiles
	std::vector<bool> Controller::determineSafeSpots(const Game& g)
	{
		// Get the current projectiles and explosions
		std::list<Projectile> projectiles = g.getProjectiles();
		std::list<Explosion> explosions = g.getExplosions();

		// Get the number of projectiles
		const size_t numProjectiles = projectiles.size();
		// Get the number of explosions
		// const size_t numExplosions = explosions.size();

		// Get the width of the map
		const size_t mapLength = g.getWidth();

		// Get the size of the explosions
		const float explosionSize = g.explosionSize;

		// Create the SafeSpots map
		std::vector<bool> safeSpots(mapLength, true);

		// Predict all projectile impacts
		std::vector<Prediction> allPreds(numProjectiles);
		int j = 0;
		for (std::list<Projectile>::const_iterator it = projectiles.begin();
				it != projectiles.end(); ++it)
		{
			// Track the projectile
			allPreds[j] = trackProjectile(*it, g);
			++j;
		}

		// Overlay all projectiles on the SafeSpots map
		for (size_t i = 0; i < numProjectiles; ++i)
		{
			Prediction pred = allPreds[i];
			size_t start = std::floor(pred.x - 1.2 * explosionSize);
			size_t end = std::ceil(pred.x + 1.2 * explosionSize);
			for (size_t j = start; j <= end; ++j)
			{
				if (j >= 0 && j < mapLength)
				{
					safeSpots[j] = false;
				}
			}
		}

		// Overlay all explosions on the SafeSpots map
		for (const Explosion& explosion : explosions)
		{
			const size_t start = std::floor(explosion.x - 1.2 * explosionSize);
			const size_t end = std::ceil(explosion.x + 1.2 * explosionSize);
			for (size_t i = start; i <= end; ++i)
			{
				if (i >= 0 && i < mapLength)
				{
					safeSpots[i] = false;
				}
			}
		}

		return safeSpots;
	}


	int Controller::pickSafeSpot(const Game& g)
	{
		// Get the safe spots
		std::vector<bool> safeSpots = determineSafeSpots(g);

		// Get the width of the map
		const int mapLength = g.getWidth();

		// Get the current position of the player
		int left = p->x;
		std::cout << "Player x: " << left << std::endl;
		int right = p->x;
		std::cout << "Player x: " << right << std::endl;

		int moveLeft = 0;
		int moveRight = 0;
		int stepl = 0;
		int stepr = 0;

		// Check if the player is at a safe spot
		if (safeSpots.at(left) == true)
		{
			return 0;
		}

		// find the closest safe spot
		while (left >= 0 && right < (mapLength))
		{
			if ((left > 15 && safeSpots.at(left+stepl) == false))
			{
				++moveLeft;
				--stepl;

			}
			if (right < (mapLength - 15) && safeSpots.at(right+stepr) == false)
			{
				++moveRight;
				++stepr;
			}
			--left;
			++right;
		}

		if (moveLeft > moveRight)
		{
			return -1;
		}
		else
		{
			return +1;
		}
	}
}
