#include "CRectangle.h"
#include "fstream"

CRectangle::CRectangle(CRectangle* R) : CFigure(R->FigGfxInfo) {
	this->Corner1 = R->Corner1;
	this->Corner2 = R->Corner2;
	FigType = RECTANGLE;
	this->L = R->L;
	this->W = R->W;
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	FigType = RECTANGLE;
	L = abs(P1.x - P2.x);
	W = abs(P1.y - P2.y);
	FitInsideDrawArea();
}

CRectangle::CRectangle(ifstream& InFile)
	: CFigure(InFile) // initializes ID and CFigure::selected = false
{
	Load(InFile);
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

void CRectangle::MoveFigure(int x, int y)
{
	//Sets point as new centroid of the rectangle and shifts all points accordingly
	Corner1.x = x + (L / 2);
	Corner1.y = y + (W / 2);
	Corner2.x = x - (L / 2);
	Corner2.y = y - (W / 2);
	FitInsideDrawArea();

}

FigureType CRectangle::GetFigType() const
{
	return FigType;
}

void CRectangle::PrintInfo(Output* pOut)
{
	string Message = "Rectangle   ID: " + to_string(ID) + " ,Corner 1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")" + " ,Corner 2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")";
	Message += ",Length: "+to_string(L)+",Width: "+to_string(W);
	pOut->PrintMessage(Message);
}

bool CRectangle::IsClicked(int x, int y)
{
	if (x >= Corner1.x && x <= Corner2.x || x <= Corner1.x && x >= Corner2.x) //Horizontal boundaries
		if (y >= Corner1.y && y <= Corner2.y || y <= Corner1.y && y >= Corner2.y)//Vertical boundaries
		return true;
	return false;
}

void CRectangle::Save(ofstream& OutFile)
{
	OutFile << "RECTANGLE" << "\t" << this->ID << "\t";
	OutFile << Corner1.x << "\t" << Corner1.y << "\t";
	OutFile << Corner2.x << "\t" << Corner2.y << "\t";
	OutFile << L << "\t" << W << "\t";
	CFigure::Save(OutFile);	//Saves Draw, Fill color
}

void CRectangle::Load(ifstream& InFile)
{
	char input[30] = {};
	InFile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y>>L>>W;
	FigType = RECTANGLE;
	CFigure::Load(InFile);	//Loades Draw, Fill Color
}

void CRectangle::FitInsideDrawArea()
{
	//We have to Validate that both corners are inside the draw area from all 4 sides
	
	//First Corner

	if (Corner1.y> (UI.height - 100 - UI.StatusBarHeight)) //Bottomside Validation
	{
		Corner2.y -= (Corner1.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
		Corner1.y -= (Corner1.y - UI.height + 100 - UI.StatusBarHeight - 5); //Pushing Corner 1 Inside
	}
	if (Corner1.y < UI.ToolBarHeight)//Topside Validation
	{
		Corner2.y += (-Corner1.y + UI.ToolBarHeight + 5);//Pushing Corner 2 Inside
		Corner1.y += (-Corner1.y + UI.ToolBarHeight + 5);//Pushing Corner 1 Inside
	}
	if (Corner1.x > UI.width - 25) //Rightside Validation
	{
		Corner2.x -= (Corner1.x - UI.width + 25 - 5);//Pushing Corner 2 Inside
		Corner1.x -= (Corner1.x - UI.width + 25 - 5);//Pushing Corner 1 Inside
	}
	if (Corner1.x < 0) //Leftside Validation
	{
		Corner2.x += (-Corner1.x + 5);//Pushing Corner 2 Inside
		Corner1.x += (-Corner1.x + 5);//Pushing Corner 1 Inside
	}
	//Second Corner
	if (Corner2.y > (UI.height - UI.StatusBarHeight)) //Bottomside Validation
	{
		Corner1.y -= (Corner2.y - UI.height - UI.StatusBarHeight - 5); //Pushing Corner 1 Inside
		Corner2.y -= (Corner2.y - UI.height - UI.StatusBarHeight - 5); //Pushing Corner 2 Inside
	}
	if (Corner2.y < UI.ToolBarHeight)//Topside Validation
	{
		Corner1.y += (-Corner2.y + UI.ToolBarHeight + 5);//Pushing Corner 1 Inside
		Corner2.y += (-Corner2.y + UI.ToolBarHeight + 5);//Pushing Corner 2 Inside
	}
	if (Corner2.x > UI.width - 25) //Rightside Validation
	{
		Corner1.x -= (Corner2.x - UI.width + 25 - 5);//Pushing Corner 1 Inside
		Corner2.x -= (Corner2.x - UI.width + 25 - 5);//Pushing Corner 2 Inside
	}
	if (Corner2.x < 0) //Leftside Validation
	{
		Corner1.x += (-Corner2.x + 5);//Pushing Corner 1 Inside
		Corner2.x += (-Corner2.x + 5);//Pushing Corner 2 Inside
	}
}

bool CRectangle::DoubleSize()
{
	if (2*L > UI.width) //if length will be too big
		return false;
	if (2*W > UI.height- UI.ToolBarHeight - UI.StatusBarHeight - 50)//if width will be too big
		return false;
	Point Center{}; //Defining a center in order to stretch the rectangle around it
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;
	//Corner 1
	if (Corner1.x > Center.x)//Corner 1 is to the right of the center
		Corner1.x +=(Corner1.x - Center.x);
	if (Corner1.x < Center.x)//Corner 1 is to the left of the center
		Corner1.x -=(Center.x - Corner1.x);
	if (Corner1.y > Center.y)//Corner 1 is below of the center
		Corner1.y +=(Corner1.y - Center.y);
	if (Corner1.y < Center.y)//Corner 1 is above of the center
		Corner1.y -=(Center.y - Corner1.y);

	//Corner 2
	if (Corner2.x > Center.x)//Corner 2 is to the right of the center
		Corner2.x += (Corner2.x - Center.x);
	if (Corner2.x < Center.x)//Corner 2 is to the left of the center
		Corner2.x -=(Center.x - Corner2.x);
	if (Corner2.y > Center.y)//Corner 2 is below of the center
		Corner2.y +=(Corner2.y - Center.y);
	if (Corner2.y < Center.y)//Corner 2 is above of the center
		Corner2.y -=( Center.y - Corner2.y);

	L = abs(Corner1.x - Corner2.x); //Updating new length and width values
	W = abs(Corner1.y - Corner2.y);
	FitInsideDrawArea();
	return true;
}

bool CRectangle::HalfSize()
{
	if (0.5*L*W < 200) //if size will be too small
		return false;
	Point Center{}; //Defining a center in order to shrink the rectangle around it
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;

	//Corner 1
	if (Corner1.x > Center.x)//Corner 1 is to the right of the center
		Corner1.x -= 0.5 * (Corner1.x - Center.x);
	if (Corner1.x < Center.x)//Corner 1 is to the left of the center
		Corner1.x += 0.5 * (Center.x - Corner1.x);
	if (Corner1.y > Center.y)//Corner 1 is below of the center
		Corner1.y -= 0.5 * (Corner1.y - Center.y);
	if (Corner1.y < Center.y)//Corner 1 is above of the center
		Corner1.y += 0.5 * (Center.y - Corner1.y);
	//Corner 2

	if (Corner2.x > Center.x)//Corner 2 is to the right of the center
		Corner2.x -= 0.5 * (Corner2.x - Center.x);
	if (Corner2.x < Center.x)//Corner 2 is to the left of the center
		Corner2.x += 0.5 * (Center.x - Corner2.x);
	if (Corner2.y > Center.y)//Corner 2 is below of the center
		Corner2.y -= 0.5 * (Corner2.y - Center.y);
	if (Corner2.y < Center.y)//Corner 2 is above of the center
		Corner2.y += 0.5 * (Center.y - Corner2.y);

	L = abs(Corner1.x - Corner2.x);//Updating Length and Width Values
	W = abs(Corner1.y - Corner2.y);

	FitInsideDrawArea();
	return true;
}
