#include "CWidget_Slot_QuickSlot.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"

void UCWidget_Slot_QuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	//UMaterialInstanceConstant* mat = Cast<UMaterialInstanceConstant>(IconWidget->Brush.GetResourceObject());

	UMaterialInstanceConstant* mat;

	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&mat, "MaterialInstanceConstant'/Game/__ProjectFile/Materials/Mat_QuickSlot_Inst.Mat_QuickSlot_Inst'");

	Mat = UMaterialInstanceDynamic::Create(mat, this);

	IconWidget->SetBrushFromMaterial(Mat);

	/*UTexture2D* texture;
	CHelpers::GetAssetDynamic(&texture, "Texture2D'/Game/__ProjectFile/Textures/SkillIcon/Icons8_31.Icons8_31'");
	Mat->SetTextureParameterValue("Tex", texture);*/
}

