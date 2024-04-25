#include "CFigure.h"

int CFigure::CreatedFigCount = 0;

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID =++CreatedFigCount;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::IsTheSame(CFigure* pFig) const
{
	if (pFig == NULL)
		return false;
	if (pFig->ID == this->ID)
		return true;
	return false;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

color CFigure::GetDrawClr()
{
	return FigGfxInfo.DrawClr;
}

color CFigure::GetFillClr()
{
	return FigGfxInfo.FillClr;
}

void CFigure::SetID(int id)
{
	ID = id;
}


