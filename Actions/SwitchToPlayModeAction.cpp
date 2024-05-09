#include "SwitchToPlayModeAction.h"
#include"SaveAction.h"
#include"../ApplicationManager.h"
SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp):Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
}

void SwitchToPlayModeAction::Execute()
{
	SaveAction* pSave = new SaveAction(pManager, 1);
	pSave->Execute();
	delete pSave;
	pManager->GetOutput()->PrintMessage("Switched to Play Mode");
	pManager->GetOutput()->CreatePlayToolBar();
}
