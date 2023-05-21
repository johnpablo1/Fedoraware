#include "../Hooks.h"

int iCurPlayer;
unsigned char _color[4];

MAKE_HOOK(C_TFPlayer_Resource_GetPlayerConnectionState, g_Pattern.Find(L"client.dll", L"55 8B EC 8B 45 ? 85 C0 74 ? 83 F8 ? 7F"), MM_PlayerConnectionState_t, __fastcall,
    void* ecx, void* edx, int iIndex)
{
    const auto result = Hook.Original<FN>()(ecx, edx, iIndex);

    if (result != MM_WAITING_FOR_PLAYER)
    {
        auto retaddr = reinterpret_cast<DWORD>(_ReturnAddress());
        static auto call = g_Pattern.Find(L"client.dll", L"33 C9 89 45 ? 89 4D ? 85 C0 75");
        if (retaddr != call)
        {
            return result;
        }

        iCurPlayer = iIndex;
    }
    else
    {
        iCurPlayer = 0;
    }

    return result;
}

MAKE_HOOK(C_PlayerResource_GetTeamColor, g_Pattern.Find(L"client.dll", L"55 8B EC 8B 45 08 83 F8 1F"), unsigned char*, __fastcall,
    void* ecx, void* edx, int index)
{
    if (index < 0 || index > 31 || !iCurPlayer || !Vars::Visuals::ScoreboardColours.Value ||
        Vars::Visuals::CleanScreenshots.Value && I::EngineClient->IsTakingScreenshot()) {
        return Hook.Original<FN>()(ecx, edx, index);
    }

    CBaseEntity* ent = I::ClientEntityList->GetClientEntity(iCurPlayer);
    if (!ent || !ent->IsAlive() || !ent->IsPlayer()) { return Hook.Original<FN>()(ecx, edx, index); }

    const Color_t cReturn = Utils::GetEntityDrawColor(ent, Vars::ESP::Main::EnableTeamEnemyColors.Value);

    _color[0] = cReturn.r; _color[1] = cReturn.g; _color[2] = cReturn.b; _color[3] = 255;    //  force alpha
    return _color;
}