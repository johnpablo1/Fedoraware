#pragma once
#include "../../SDK/SDK.h"

class CFedworking
{
private:
	void ConsoleLog(const std::string& pMessage);

public:
	void HandleMessage(const char* pMessage);
	void SendMarker(const Vec3& pPos, int pPlayerIdx);
	void SendESP(CBaseEntity* pPlayer);
	void SendPong(const std::string& pData);
	void SendMessage(const std::string& pData);
	void Run();
};

ADD_FEATURE(CFedworking, Fedworking)