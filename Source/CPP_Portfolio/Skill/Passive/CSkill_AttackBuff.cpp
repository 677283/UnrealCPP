#include "CSkill_AttackBuff.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStatusComponent.h"


void UCSkill_AttackBuff::DoSkill()
{
	Super::DoSkill();

	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);



}