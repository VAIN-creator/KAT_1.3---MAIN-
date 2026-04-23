// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FObjectDistributionManagerModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FName ToolTabID;

	void SetupPluginToolbarEntry();
	void AddToolbarExtension(class FToolBarBuilder& ToolBarBuilder);

public:
	void ToolbarButtonClicked();
};

