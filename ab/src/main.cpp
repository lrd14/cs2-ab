#include "cheat/entity.hpp"
#include <string_view>

int main()
{
	printf("...");
	std::thread ReadThread(&Reader::ThreadLoop, &reader);
	ReadThread.detach();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		aimbot.doAimbot();
	}
}