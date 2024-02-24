#pragma once
#include "Player.h"
#include "Game.h"
#include <map>
#include <vector>
namespace mrsd
{
	struct Prediction
	{
		float t, x;
	};

	/**
	 * Controller class to control AI.
	 **/
	class Controller
	{
		public:
			Controller():p(0){}
			/**
			 * Control AI based on state of game. "t" time has passed since last update.
			 **/
			void control(const Game& g, float t);

			/*
			 * Construct Player and add to game.
			 */
			void createPlayer(Game& g);

		private:
			/*
			 * Player to control.
			*/
			Player* p;

			/*
			* Current time.
			*/
			float currentTime;

			/*
			 * Track projectile and determine where and when it will hit ground.
			 */
			Prediction trackProjectile(const Projectile& p, const Game& g);

			/*
			 * Determine safe spots at time t based on state of all observed projectiles.
			 */
			std::vector<bool> determineSafeSpots(const Game& g);

			/*
			 * Pick safe spot from determined safe spots.
			 */
			int pickSafeSpot(const Game& g);
	};
}
