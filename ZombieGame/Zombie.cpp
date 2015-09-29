#include "Zombie.h"

#include <GTEngine/ResourceManager.h>

Zombie::Zombie(int x, int y)
{
	_position.x = x;
	_position.y = y;
}


Zombie::~Zombie()
{
}

bool Zombie::update(World& world, std::vector<Bullet>& bullets, std::vector<Human>& humans) {
	// Check if the human should die
	for (int i = 0; i < bullets.size(); i++) {
		int bufferZone = 38;
		//std::cout << glm::to_string(bullets[i].getPosition()) << " == " << glm::to_string(_position) << std::endl;
		if ((bullets[i].getPosition().x < _position.x + bufferZone) &&
			(bullets[i].getPosition().x > _position.x - bufferZone) &&
			(bullets[i].getPosition().y < _position.y + bufferZone) &&
			(bullets[i].getPosition().y > _position.y - bufferZone)) {
			return true;
		}
	}

	// Initialise variables
	int bufferSpace = 49;
	int minBufferSpace = 1;
	float moveSpeed = 2;
	int direction = rand() % 4 + 0;

	// Chase the humans (chase the closest human)
	float min = 100000;
	int indexOfTheClosestZombie = 0;
	for (int i = 0; i < humans.size(); i++) {
		float temp = sqrt(pow(humans[i].getPosition().x - _position.x, 2) - pow(humans[i].getPosition().y - _position.y, 2));
		if ( temp < min) {
			min = temp;
			indexOfTheClosestZombie = i;
		}
	}

	if (min != 100000) {
		glm::vec2 directionVector = humans[indexOfTheClosestZombie].getPosition() - _position;
		directionVector = glm::normalize(directionVector);

		_position += directionVector * moveSpeed;
		bool legalAction = world.collision(_position.x + 49, _position.y - 49);
		int bufferSpace = 49;
		int minBufferSpace = 1;
		if (legalAction == false) {
			_position -= directionVector * moveSpeed;
			if (direction == 0 && world.collision(_position.x + bufferSpace, _position.y)) {
				_position.x += moveSpeed;
			}
			else if (direction == 1 && world.collision(_position.x - minBufferSpace, _position.y)) {
				_position.x -= moveSpeed;
			}
			else if (direction == 2 && world.collision(_position.x, _position.y + bufferSpace)) {
				_position.y += moveSpeed;
			}
			else if (direction == 3 && world.collision(_position.x, _position.y - minBufferSpace)) {
				_position.y -= moveSpeed;
			}
		}
	}
	else {
		if (direction == 0 && world.collision(_position.x + bufferSpace, _position.y)) {
			_position.x += moveSpeed;
		}
		else if (direction == 1 && world.collision(_position.x - minBufferSpace, _position.y)) {
			_position.x -= moveSpeed;
		}
		else if (direction == 2 && world.collision(_position.x, _position.y + bufferSpace)) {
			_position.y += moveSpeed;
		}
		else if (direction == 3 && world.collision(_position.x, _position.y - minBufferSpace)) {
			_position.y -= moveSpeed;
		}
	}
	return false;
}

void Zombie::draw(GTEngine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GTEngine::GLTexture texture = GTEngine::ResourceManager::getTexture("Textures/circle.png");

	GTEngine::Color color;
	color.r = 1;
	color.g = 255;
	color.b = 50;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 45, 45);

	// Draw the sprite
	spriteBatch.draw(posAndSize, uv, texture.id, color, 0.0f);
}