#pragma once
#include <iostream>
#include"..\Figures\CFigure.h"
#include <cstdlib> 
#include "Action.h"

class FindByTypeAndColor : public Action{
private:
	int RightCount;
	int WrongCount;
	int RandNum;
	color SelectedColor;
	FigureType SelectedShape;
	CFigure* PickedFigure;
	Point Click;
	bool Exit;
	bool Restart;
public:
	void FindByTypeAndColor::GenRandColor();
	FindByTypeAndColor(ApplicationManager* pApp);

	void FindByTypeAndColor::ReadActionParameters();
	void FindByTypeAndColor::Execute();

	void FindByTypeAndColor::PickFigureAndColorAction();
};