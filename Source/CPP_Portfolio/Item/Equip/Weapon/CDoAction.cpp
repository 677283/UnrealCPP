#include "CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/InputSettings.h"

/*
	좌클릭, 우클릭 콤보 혼합 시스템.
	입력되는 키를 ComboKey(String)로 누적 저장.
	모든 콤보를 Map에 저장하며 Key를 String으로 해두고 불러오기.
	Ex) "RRLRL" 등 다양한 콤보 저장 가능.
*/

UCDoAction::UCDoAction()
{
	bComboEnable = false;
}

void UCDoAction::BeginPlay(class ACharacter* InOwner)
{
	CheckNull(InOwner);

	OwnerCharacter = InOwner;
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
}

void UCDoAction::OnEquipActorCollision()
{
	HittedCharacters.Empty();
}