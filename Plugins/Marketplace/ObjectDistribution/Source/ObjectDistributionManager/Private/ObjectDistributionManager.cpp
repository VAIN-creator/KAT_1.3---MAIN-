// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#include "ObjectDistributionManager.h"
#include "Editor.h"
#include "EditorUtilitySubsystem.h" 
#include "EditorUtilityWidgetBlueprint.h"
#include "LevelEditor.h"
#include "MToolAssetData.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Style/MToolStyle.h"

#define LOCTEXT_NAMESPACE "FObjectDistributionManagerModule"

void FObjectDistributionManagerModule::StartupModule()
{
	FODToolStyle::InitializeToolStyle();
	SetupPluginToolbarEntry();
}

void FObjectDistributionManagerModule::SetupPluginToolbarEntry()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> Extenders = LevelEditorModule.GetToolBarExtensibilityManager()->GetAllExtenders();

	const TSharedPtr<FExtender> MyExtender = MakeShareable(new FExtender);
	MyExtender->AddToolBarExtension("Play", EExtensionHook::After, NULL, FToolBarExtensionDelegate::CreateRaw(this, &FObjectDistributionManagerModule::AddToolbarExtension));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MyExtender);
}

void FObjectDistributionManagerModule::AddToolbarExtension(FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.AddToolBarButton
	(
	FUIAction(
		FExecuteAction::CreateRaw(this, &FObjectDistributionManagerModule::ToolbarButtonClicked)),
		NAME_None,
		FText::FromString(TEXT("Object Distribution")), //Title text
		FText::FromString(TEXT("Object Distribution")), // Tooltip  text
		FSlateIcon(FODToolStyle::GetToolStyleName(),"LevelEditor.DistributionIcon")
	);
	
}

void FObjectDistributionManagerModule::ToolbarButtonClicked()
{
	if (!GEditor){return;}

	if(	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>())
	{
		if(EditorUtilitySubsystem->DoesTabExist(ToolTabID))
		{
			EditorUtilitySubsystem->CloseTabByID(ToolTabID);
		}
		else
		{
			if(UObject* ToolWindowObject = MTToolAssetData::ODToolWindowPath.TryLoad())
			{
				if(const auto ToolWindowBlueprint = Cast<UEditorUtilityWidgetBlueprint>(ToolWindowObject))
				{
					EditorUtilitySubsystem->SpawnAndRegisterTabAndGetID(ToolWindowBlueprint,ToolTabID);
					//Set Tab Icon
					const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
					const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
					if (const TSharedPtr<SDockTab> FoundTab = LevelEditorTabManager->FindExistingLiveTab(ToolTabID))
					{
						FoundTab->SetTabIcon(FSlateIcon(FODToolStyle::GetToolStyleName(),"LevelEditor.DistributionIcon").GetIcon());
					}
				}
			}
		}
	}
}

void FObjectDistributionManagerModule::ShutdownModule()
{
	FODToolStyle::ShutDownStyle();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FObjectDistributionManagerModule, ObjectDistributionManager)