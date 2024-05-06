
#pragma once
#include "Action.h"
#include "RandNum.h"
#include <iostream>
#include"..\Figures\CFigure.h"
#include <cstdlib> 


class FindByType : public Action{
private:
	int RightCount;
	int WrongCount;
	int RandNum;
	FigureType SelectedShape;
	Point Click;
	CFigure* PickedFigure;
	bool Exit;
	bool Restart;
public:
	FindByType(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	void GenRandShape();
	void PickFigureAction();
};