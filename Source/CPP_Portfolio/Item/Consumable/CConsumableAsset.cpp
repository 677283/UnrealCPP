//#include "CConsumableAsset.h"
//#include "Global.h"
//#include "CConditionEffect.h"
//#include "GameFramework/Character.h"
//#include "Components/CStatusComponent.h"
//
//UCConsumableAsset::UCConsumableAsset()
//{
//	
//}
//
//void UCConsumableAsset::BeginPlay(class ACharacter* InOwner)
//{
//	Super::BeginPlay(InOwner);
//
//	for (FSpecialCondition conditionClass : SpecialConditionClasses)
//	{
//		UCConditionEffect* condition = NewObject<UCConditionEffect>(this, conditionClass.Condition);
//		SpecialConditions.Add(condition);
//	}
//
//	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
//}
//
//void UCConsumableAsset::UseItem()
//{
//	Super::UseItem();
//	
//	for (FCondition condition : Conditions)
//	{
//		switch (condition.Type)
//		{
//		case EConditionType::Healing:
//			Healing(condition.Value);
//			break;
//		case EConditionType::ChargeEnergy:
//			ChargeEnergy(condition.Value);
//			break;
//		}
//	}
//
//	for (int32 i=0; i<SpecialConditions.Num(); i++)
//	{
//		SpecialConditions[i]->AddCondition(OwnerCharacter, SpecialConditionClasses[i].Value);
//	}
//	
//}
//
//void UCConsumableAsset::Healing(float InValue)
//{
//
//}
//
//void UCConsumableAsset::ChargeEnergy(float InValue)
//{
//
//}