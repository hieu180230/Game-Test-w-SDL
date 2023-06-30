#include "Collision.h"
#include "Entity&COmponent/Collider.h"
bool Collision::isCollide(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	return (rectA.x < rectB.x + rectB.w &&
		rectA.x + rectA.w > rectB.x &&
		rectA.y < rectB.y + rectB.h &&
		rectA.y + rectA.h > rectB.y);
}


bool Collision::isCollide(Collider& colA, const Collider& colB)
{
	if (isCollide(colA.collide, colB.collide))
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

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<Collider>().collide;

		// Check for collision in the x-axis
		SDL_Rect xCheckCollider = playerCollider;
		xCheckCollider.x += player.getComponent<TransformComponent>().velocity.x;

		if (Collision::isCollide(xCheckCollider, cCollider))
		{
			canMoveX = false;
			player.getComponent<TransformComponent>().position = PlayerPos;
		}

		// Check for collision in the y-axis
		SDL_Rect yCheckCollider = playerCollider;
		yCheckCollider.y += player.getComponent<TransformComponent>().velocity.y;

		if (Collision::isCollide(yCheckCollider, cCollider))
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
}

