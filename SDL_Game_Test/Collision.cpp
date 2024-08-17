#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB, SDL_Rect& res)
{
	return SDL_IntersectRect(&rectA, &rectB, &res);
}

bool Collision::isCollide(Collider& colA, const Collider& colB)
{
	SDL_Rect res;
	if (isCollide(colA.collide, colB.collide, res))
	{
		cout << colA.tag << "hit: " << colB.tag << endl;
		return true;
	}
	return false;
}

void Collision::collisionResolve(Entity& player, vector<Entity*> colliders)
{
	SDL_Rect playerCollider = player.getComponent<Collider>().collide;
	Vector2D PlayerPos = player.getComponent<TransformComponent>().position;

	bool canMoveX = true;
	bool canMoveY = true;

	// Store the original velocity
	Vector2D originalVelocity = player.getComponent<TransformComponent>().velocity;

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<Collider>().collide;
		SDL_Rect res = { 0,0,0,0 };
		// Check for collision in the x-axis
		SDL_Rect xCheckCollider = playerCollider;
		xCheckCollider.x += player.getComponent<TransformComponent>().velocity.x;

		if (Collision::isCollide(xCheckCollider, cCollider, res))
		{
			canMoveX = false;
			player.getComponent<TransformComponent>().position.x = PlayerPos.x;
		}

		// Check for collision in the y-axis
		SDL_Rect yCheckCollider = playerCollider;
		yCheckCollider.y += player.getComponent<TransformComponent>().velocity.y;

		if (Collision::isCollide(yCheckCollider, cCollider, res))
		{
			player.getComponent<TransformComponent>().position = PlayerPos;
			canMoveY = false;
		}

		// If both axes have collision, exit the loop
		if (!canMoveX && !canMoveY)
		{
			break;
		}
	}

	if (!canMoveX) player.getComponent<TransformComponent>().velocity.x = 0;
	if (!canMoveY) player.getComponent<TransformComponent>().velocity.y = 0;

	if (canMoveX && canMoveY)
	{
		player.getComponent<TransformComponent>().velocity = originalVelocity;
	}
}

