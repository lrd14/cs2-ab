#include "../mem/memify.h"
#include "../math/math.hpp"

#include <vector>
#include <thread>

memify mem("cs2.exe");

namespace offset
{
	constexpr std::ptrdiff_t dwEntityList = 0x1A146E8;
	constexpr std::ptrdiff_t dwViewMatrix = 0x1A7F610;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1868CC8;

	constexpr std::ptrdiff_t m_hPawn = 0x5FC; // CHandle<C_BasePlayerPawn>

	constexpr std::ptrdiff_t m_iHealth = 0x324; // int32
	constexpr std::ptrdiff_t m_iTeamNum = 0x3C3; // uint8

	constexpr std::ptrdiff_t m_vOldOrigin = 0x1274; // Vector

	constexpr std::ptrdiff_t m_entitySpottedState = 0x10F8; // EntitySpottedState_t
}

class C_CSPlayerPawn
{
public:
	int health, team;

	Vector Position;

	uintptr_t pCSPlayerPawn;
};

inline C_CSPlayerPawn CCSPlayerPawn;

class Reader
{
public:
	uintptr_t client = 0;

	std::vector<C_CSPlayerPawn> playerList;

	void ThreadLoop();
private:
	void FilterPlayers();
};

inline Reader reader;

class Aimbot
{
public:
	void doAimbot();
private:
	Vector findClosest(const std::vector<Vector> playerPositions);
	void MoveMouseToPlayer(Vector position);
};

inline Aimbot aimbot;