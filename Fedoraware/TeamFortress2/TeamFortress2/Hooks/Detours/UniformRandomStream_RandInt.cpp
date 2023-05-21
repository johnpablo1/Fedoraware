#include "../Hooks.h"

MAKE_HOOK(UniformRandomStream_RandInt, Utils::GetVFuncPtr(I::UniformRandomStream, 2), int, __fastcall,
		  void* ecx, void* edx, int iMinVal, int iMaxVal)
{
	if (Vars::Misc::MedalFlip.Value && I::EngineVGui->IsGameUIVisible())
	{
		if (iMinVal == 0 && iMaxVal == 9)
		{
			return 0;
		}
	}

	return Hook.Original<FN>()(ecx, edx, iMinVal, iMaxVal);
}