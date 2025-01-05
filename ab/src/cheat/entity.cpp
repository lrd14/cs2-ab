#include "entity.hpp"
#include <iostream>

void Reader::ThreadLoop()
{
	while (!client) {
		Sleep(20);
		client = mem.GetBase("client.dll");
		std::cout << "client" << std::hex << client << std::endl;
	}

	int loops = 0;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (loops > 50) {
			FilterPlayers();
			loops = 0;
		}
		++loops;
	}
}

void Reader::FilterPlayers()
{
	playerList.clear();
	auto entityList = mem.Read<uintptr_t>(client + offset::dwEntityList);
	auto localPlayerPtr = mem.Read<uintptr_t>(client + offset::dwLocalPlayerPawn);

	for (int i = 0; i < 64; ++i)
	{
		uintptr_t list_entry1 = *(uintptr_t*)(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
		uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF));
		uint32_t playerPawn = *(uint32_t*)(playerController + offset::m_hPawn);
		uintptr_t list_entry2 = *(uintptr_t*)(entityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
		uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (playerPawn & 0x1FF));

		int health = mem.Read<int>(pCSPlayerPawnPtr + offset::m_iHealth);

		if (health <= 0 || health > 100)
			continue;

		int team = mem.Read<int>(pCSPlayerPawnPtr + offset::m_iTeamNum);

		if (team == mem.Read<int>(localPlayerPtr + offset::m_iTeamNum))
			continue;

		CCSPlayerPawn.pCSPlayerPawn = pCSPlayerPawnPtr;

		playerList.push_back(CCSPlayerPawn);
	}
}
