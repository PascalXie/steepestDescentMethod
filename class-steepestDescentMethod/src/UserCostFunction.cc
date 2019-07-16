#include "UserCostFunction.hh"

//-------------------------
// Constructor
//-------------------------
UserCostFunction::UserCostFunction(string name, int SizeObservations, int SizeVariables, int SizeResiduals)
:	name_(name),
	SizeObservations_(SizeObservations),
	SizeVariables_(SizeVariables),
    SizeResiduals_(SizeResiduals)
{
	//cout<<"UserCostFunction "<<name_<<endl;
}

//-------------------------
// Destructor
//-------------------------
UserCostFunction::~UserCostFunction()
{}

//-------------------------
// Public
//-------------------------
bool UserCostFunction::GradientFunction(vector<double> variables, vector<double> &theDerivatives)
{
	// calculate all derivatives
	vector<double> derivatives;
	derivatives.clear();

	// debug
	if(variables.size()!=SizeVariables_)
	{
		cout<<"An Error happend in Class UserCostFunction::GradientFunction "<<endl;
		return false;
	}

	// step 1 : get derivatives one by one
	for(int i=0;i<SizeVariables_;i++)
	{
		/*
		// debug
		cout<<"Debug varialbeID "<<i<<endl;
		cout<<"Debug SizeVariables_ "<<SizeVariables_<<endl;
		*/

		int varialbeID = i;
		double derivative_current = 666;
		bool isDerivativeGood = GetOneDerivative(varialbeID,variables,derivative_current);
		derivatives.push_back(derivative_current);
	}

	// step 2 : output derivatives
	theDerivatives = derivatives;

	return true;
}
