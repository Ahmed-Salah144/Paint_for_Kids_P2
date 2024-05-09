#include "SwitchToDrawModeAction.h"
#include"LoadAction.h"
#include"../ApplicationManager.h"
SwitchToDrawModeAction::SwitchToDrawModeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SwitchToDrawModeAction::ReadActionParameters()
{
}

void SwitchToDrawModeAction::Execute()
{
	LoadAction* pLoad = new LoadAction(pManager, 1);
	pLoad->Execute();
	delete pLoad;
	pManager->GetOutput()->PrintMessage("Switched to Play Mode");
	pManager->GetOutput()->CreateDrawToolBar();
}
