#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\SelectionAction.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFigure; //Pointer to the selected figure
	int SelectedFigCount;//(salem)
	int SelectedRects, SelectedSqrs, SelectedHexes, SelectedTris, SelectedCircs ;//selected
	int NumOfRect,NumOfSqr, NumOfHex, NumOfTri, NumOfCirc;//total;

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	CFigure* Clipboard;  //Pointer to copied/cut figure

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	// -- Figures Management Functions
	void AddFigure(CFigure*);         //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void RemoveFigure(CFigure*); //Salem
	void SwapFigure(int,int);//Salem for (send to back)

	CFigure* GetSelectedFigure() const;
	void SetSelectedFigure(CFigure*);
	int GetSelectedFigureCount()const;
	int GetSelectedFigureCountByType(FigureType)const;
	int GetFigureCount()const;
	// Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output

	void UpdateInterface() const;	//Redraws all the drawing window	
	void ClearAll();//(salem)
	void UpdateFigureData();
	void SaveAll(ofstream& OutFile) const; //ChecK TA Save Output changed ?? (figure name, 1 added tab) Faseeh
};

#endif