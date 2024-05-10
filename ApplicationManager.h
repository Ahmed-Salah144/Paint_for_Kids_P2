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

	int SelectedFigCount;//Number of Selected Figures

	int SelectedRects, SelectedSqrs, SelectedHexes, SelectedTris, SelectedCircs ;//Number of selected figures of each type

	int NumOfRect,NumOfSqr, NumOfHex, NumOfTri, NumOfCirc;//Number of Figures of each type;\

	int NumOfBlack, NumOfYellow,NumOfOrange,NumOfRed,NumOfGreen,NumOfBlue; //Num of Figures of each color

	int CutFigureID; //ID of the figure in clipboard if it was cut


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

	CFigure* GetFigureByColor(color)const; //Search for a figure given a color

	CFigure* GetRandomFigure(bool=false)const; //Search for a random figure

	CFigure* GetFigureByID(int)const; //Search for a figure given its ID

	CFigure* CheckTypeAndColor(color c, FigureType b)const;//Search for a figure given its type and color

	CFigure* GetSelectedFigure() const;//returns the selected Figure

	void RemoveFigure(int); //Remove a figure from figure List given its ID

	void SwapFigure(int,int);//Swap to figures in the figure List given their indecies


	int GetSelectedFigureCount()const; //Returns total number of selected figures

	int GetFigureCountByType(FigureType);//returns number of figures of a specific type

	int GetSelectedFigureCountByType(FigureType)const;//returns number of selected figures of a specific type

	int GetFigureCount()const;//returns total figure count

	void SetClipboard(CFigure*);  //Adds a figure to the clipboard

	CFigure* GetClipboard();	 //returns pointer to figure in clipboard

	void SetCutFigureID(int);   //Setter for the figure's ID in clipboard

	int GetCutFigureID();	   //returns ID of Cut Figure in clipboard

	void ClearAll();    //Resets all Application Manager Data

	void ClearClipboard();//Clears any figures in clipboard

	void UpdateFigureData();//Updates all Data in Application Manager

	// Interface Management Functions

	Input *GetInput() const; //Return pointer to the input

	Output *GetOutput() const; //Return pointer to the output


	void UpdateInterface() const;	//Redraws all the drawing window

	void SaveAll(ofstream& OutFile) const; //Saves All Application Manager Data


};

#endif