#include "CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/InputSettings.h"

/*
	��Ŭ��, ��Ŭ�� �޺� ȥ�� �ý���.
	�ԷµǴ� Ű�� ComboKey(String)�� ���� ����.
	��� �޺��� Map�� �����ϸ� Key�� String���� �صΰ� �ҷ�����.
	Ex) "RRLRL" �� �پ��� �޺� ���� ����.
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