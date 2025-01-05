#include "entity.hpp"

void Aimbot::doAimbot()
{

}

Vector Aimbot::findClosest(const std::vector<Vector> playerPositions)
{
	if (playerPositions.empty())
	{
		printf("playerpositions vector was empty.\n");
		return { 0.0f, 0.0f, 0.0f };
	}

	Vector center_of_screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1), 0.0f };

	float lowestDistance = 99999;
	int index = -1;

	for (int i = 0; i < playerPositions.size(); ++i)
	{
		float distance(std::pow(playerPositions[i].x - center_of_screen.x, 2) + std::pow(playerPositions[i].y - center_of_screen.y, 2));

		if (distance < lowestDistance) {
			lowestDistance = distance;
			index = i;
		}
	}
	
	return (playerPositions[index].x, playerPositions[index].y, 0.0f);
}

void Aimbot::MoveMouseToPlayer(Vector position)
{
	if (position.x == 0.0 && position.y == 0.0 && position.z == 0.0)
		return;

	Vector center_of_screen{ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1), 0.0f };

	auto new_x = position.x - center_of_screen.x;
	auto new_y = position.y - center_of_screen.y;

	mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
}