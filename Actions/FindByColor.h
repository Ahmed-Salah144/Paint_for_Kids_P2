#pragma once
#include <iostream>
#include"..\Figures\CFigure.h"
#include <cstdlib> 
#include "Action.h"

class FindByColor : public Action {
private:
	int RightCount;
	int WrongCount;
	int RandNum;
	color SelectedColor;
	CFigure* PickedFigure;
	Point Click;
	bool Exit;
	bool Restart;
public:
	FindByColor(ApplicationManager* pApp);

	void FindByColor::ReadActionParameters();
	void FindByColor::Execute();

	void GenRandColor();
	void GenRandColor2();
	void PickColorAction();
};