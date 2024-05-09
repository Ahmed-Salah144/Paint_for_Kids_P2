#include "CopyAction.h"
#include "..\Figures\CFigure.h"

#include "..\ApplicationManager.h"
#include "SelectionAction.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

CopyAction::CopyAction(ApplicationManager* pApp) :Action(pApp)
{
}

void CopyAction::ReadActionParameters()
{	
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Selected Fig Copied");
	SelectedFig = pManager->GetSelectedFigure();
}

void CopyAction::Execute()
{
	ReadActionParameters();
	CFigure* CopiedFig = NULL;
	switch (SelectedFig->GetFigType()) { 
	case HEXAGON: CopiedFig = new CHexagon((CHexagon *)SelectedFig); break;
	case CIRCLE: CopiedFig = new CCircle((CCircle*)SelectedFig); break;
	case TRIANGLE: CopiedFig = new CTriangle((CTriangle*)SelectedFig); break;
	case SQUARE: CopiedFig = new CSquare((CSquare*)SelectedFig); break;
	case RECTANGLE: CopiedFig = new CRectangle((CRectangle*)SelectedFig); break;

	}
	if (pManager->GetCutFigureID() != -1)
	{
		CFigure* PreviouslyCutFigure = pManager->GetFigureByID(pManager->GetCutFigureID());
		CFigure* Clipboard = pManager->GetClipboard();
		PreviouslyCutFigure->ChngDrawClr(Clipboard->GetDrawClr());
		if (Clipboard->IsFilled())
			PreviouslyCutFigure->ChngFillClr(Clipboard->GetFillClr());
		else
			PreviouslyCutFigure->UnFill();
		if (SelectedFig->GetID() == PreviouslyCutFigure->GetID())
		{
			CopiedFig->ChngDrawClr(Clipboard->GetDrawClr());
			if (Clipboard->IsFilled())
				CopiedFig->ChngFillClr(Clipboard->GetFillClr());
			else
				CopiedFig->UnFill();
		}
	}
	pManager->ClearClipboard();
	pManager->SetClipboard(CopiedFig);
}