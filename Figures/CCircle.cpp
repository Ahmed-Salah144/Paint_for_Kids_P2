#include"CCircle.h"
#include <fstream>

CCircle::CCircle(CCircle* C) : CFigure(C->FigGfxInfo) {
	this->Center = C->Center;
	this->OuterPoint = C->OuterPoint;
	this->Radius = C->Radius;
	FigType = CIRCLE; 
} 
CCircle::CCircle(Point P1,Point P2, GfxInfo CircleGfxInfo) :
	CFigure(CircleGfxInfo)
{
	Center = P1;
	OuterPoint = P2;
	FigType = CIRCLE;
	Radius = sqrt((P1.x - P2.x)* (P1.x - P2.x) + (P1.y - P2.y)* (P1.y - P2.y));
	FitInsideDrawArea();
}

CCircle::CCircle(ifstream& InFile)
	: CFigure (InFile)
{
	Load(InFile);
}


void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center,OuterPoint,FigGfxInfo, Selected);
}

void CCircle::MoveFigure(int x, int y)
{
	Center.x = x;
	Center.y = y;
	OuterPoint.x = x + Radius;
	OuterPoint.y = y;
	FitInsideDrawArea();
}

void CCircle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Circle   ID: " + to_string(ID) + " ,Center : (" + to_string(Center.x) + "," + to_string(Center.y) + "),Radius : " + to_string(Radius));
}

bool CCircle::IsClicked(int x, int y)
{
	int distance= sqrt((Center.x - x)* (Center.x - x) + (Center.y - y)* (Center.y - y));
	if (distance <= Radius)
		return true;
	return false;
}

FigureType CCircle::GetFigType()
{
	return FigType;
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "CIRCLE" << "\t" << "\t" << this->ID << "\t";	//extra tab to make file more readable for user
	OutFile << Center.x << "\t" << Center.y << "\t";
	OutFile << OuterPoint.x << "\t" << OuterPoint.y << "\t";
	OutFile << Radius << "\t";
	CFigure::Save(OutFile);
}

void CCircle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Center.x >> Center.y >> OuterPoint.x >> OuterPoint.y >> Radius;
	FigType = CIRCLE;
	CFigure::Load(InFile);
}

void CCircle::FitInsideDrawArea()
{
	while (Radius > (UI.height - 100) / 2)
	{
		HalfSize();
	}

	if (Center.y + Radius > (UI.height-100 - UI.StatusBarHeight)) //Bottomside Validation(Salem)
	{
		OuterPoint.y -= (Center.y + Radius - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Outer Point Inside
		Center.y -= (Center.y + Radius - UI.height + 100  - UI.StatusBarHeight - 5); //Pushing Center Inside
	}
	if (Center.y - Radius < UI.ToolBarHeight)//Topside Validation(Salem)
	{
		OuterPoint.y += (-Center.y + Radius + UI.ToolBarHeight + 5); //Pushing Outer Point Inside
		Center.y += (-Center.y + Radius + UI.ToolBarHeight + 5);//Pushing Center Inside
	}
	if (Center.x + Radius > UI.width-25) //Rightside Validation(Salem)
	{
		OuterPoint.x -= (Center.x + Radius - UI.width +25 - 5); //Pushing Outer Point Inside
		Center.x -= (Center.x + Radius - UI.width+25  - 5);//Pushing Center Inside
	}
	if (Center.x - Radius < 0) //Leftside Validation(Salem)
	{
		OuterPoint.x += (-Center.x + Radius + 5); //Pushing Outer Point Inside
		Center.x += (-Center.x + Radius + 5);//Pushing Center Inside
	}
}

bool CCircle::DoubleSize()
{
	if (Radius*2 > ((UI.height - 150) / 2))
	{
		return false;
	}
	Radius *= 2;
	OuterPoint.x = Center.x + Radius;
	OuterPoint.y = Center.y;
	FitInsideDrawArea();
	return true;
}

bool CCircle::HalfSize()
{
	if (Radius < 10)
	{
		return false;
	}
	Radius *= 0.5;
	OuterPoint.x = Center.x + Radius;
	OuterPoint.y = Center.y;
	FitInsideDrawArea();
	return true;
}
