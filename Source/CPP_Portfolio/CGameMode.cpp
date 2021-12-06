#include "CGameMode.h"
#include "Global.h"
#include "Player/CPlayer.h"

ACGameMode::ACGameMode()
{
	//CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/__ProjectFile/Horse/BP_CHorse.BP_CHorse_C'");
	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/__ProjectFile/Player/BP_CPlayer.BP_CPlayer_C'");
}