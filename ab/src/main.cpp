#include "cheat/entity.hpp"
#include <string_view>

int main()
{
	printf("...");
	std::thread ReadThread(&Reader::ThreadLoop, &reader);
	ReadThread.detach();

	while (true)
	{
		Sleep(5);
		aimbot.doAimbot();
	}
}