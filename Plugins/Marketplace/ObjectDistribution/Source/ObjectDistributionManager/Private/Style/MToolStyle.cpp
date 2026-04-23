// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#include "Style/MToolStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"


FName FODToolStyle::ToolStyleName = FName("ODManagerStyle");
TSharedPtr<FSlateStyleSet> FODToolStyle::CreatedToolSlateStyleSet = nullptr;

void FODToolStyle::InitializeToolStyle()
{	
	if(!CreatedToolSlateStyleSet.IsValid())
	{
		CreatedToolSlateStyleSet = CreateToolSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*CreatedToolSlateStyleSet);
	}
}

TSharedRef<FSlateStyleSet> FODToolStyle::CreateToolSlateStyleSet()
{	
	TSharedRef<FSlateStyleSet> CustomStyleSet = MakeShareable(new FSlateStyleSet(ToolStyleName));

	const FString IconDirectory = 
	IPluginManager::Get().FindPlugin(TEXT("ObjectDistribution"))->GetBaseDir() /"Resources";
	
	CustomStyleSet->SetContentRoot(IconDirectory);

	const FVector2D Icon32x32 (32.f,32.f);
	
	CustomStyleSet->Set("LevelEditor.DistributionIcon",
	new FSlateImageBrush(IconDirectory/"Object_Distribution.png",Icon32x32));
	
	return CustomStyleSet;
}

void FODToolStyle::ShutDownStyle()
{
	if(CreatedToolSlateStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*CreatedToolSlateStyleSet);
		CreatedToolSlateStyleSet.Reset();
	}
}
