#include "UserOptimizationManager.hh"

//-------------------------
// Constructor
//-------------------------
UserOptimizationManager::UserOptimizationManager(string name, int SizeObservations, int SizeVariables, int SizeResiduals)
:	name_(name),
	SizeObservations_(SizeObservations),
	SizeVariables_(SizeVariables),
	SizeResiduals_(SizeResiduals),
	costFunction_(NULL),
	IsInitializationCostFunctionSet_(false),
	IsInitializationVariablesSet_(false),
	alpha_stepLength_(0.001),
	TotalNumberIterations_(0),
	MaximumNumberIterations_(1000)
{}

//-------------------------
// Destructor
//-------------------------
UserOptimizationManager::~UserOptimizationManager()
{}


//-------------------------
// Public  
//-------------------------
void UserOptimizationManager::Initialize()
{
	// step 1 : set variables for initialization
	VariablesCurrent_ = initializationVariables_;

	// step 2 : loop
	for(int i=0;i<MaximumNumberIterations_;i++)
	{
		vector<double> VariablesPrevious = VariablesCurrent_;
		Loop(VariablesPrevious);

		// get errors
		vector<double> errors_costFunction;
		vector<double> costFunction_previous;
		vector<double> costFunction_current;
		bool isCostFuntionGood1 = costFunction_->CostFunction(VariablesPrevious_,costFunction_previous);
		bool isCostFuntionGood2 = costFunction_->CostFunction(VariablesCurrent_,costFunction_current);
		for(int i=0;i<SizeResiduals_;i++)
		{
			double error_current = costFunction_current[i] - costFunction_previous[i];
			errors_costFunction.push_back(error_current);
		}

		TotalNumberIterations_++;

		// debug
		cout<<"----------------------------------------"<<endl;
		cout<<"----"<<endl;
		cout<<"Class UserOptimizationManager::Initialize"<<endl;
		cout<<"Iteration Loops ID "<<TotalNumberIterations_<<", error : "<<endl;
		for(int errorID=0;errorID<SizeResiduals_;errorID++)
		{
			cout<<"    ErrorID "<<errorID<<": error "<<errors_costFunction[errorID]<<endl;
		}
		cout<<"----"<<endl;
		cout<<"----------------------------------------"<<endl;
	}
}

void UserOptimizationManager::Loop(vector<double> VariablesPrevious)
{
	vector<double> VariablesCurrent;
	VariablesCurrent.clear();

	// step 1 : set variables
	VariablesPrevious_ = VariablesPrevious;
	//VariablesPrevious_ = initializationVariables_;

	// step 2 : get derivatives
	vector<double> derivatives;
	bool isDerivativeGood = costFunction_->GradientFunction(VariablesPrevious_,derivatives);

	// step 3 : get step length
	// step 4 : get current variables
	stepLengths_.clear();
	for(int i=0;i<SizeVariables_;i++)
	{
		int variableID = i;
		double stepLength_currentID = alpha_stepLength_*(-1.)*derivatives[variableID];
		double variable_currentID = VariablesPrevious_[variableID] + stepLength_currentID;
		stepLengths_.push_back(stepLength_currentID);
		VariablesCurrent.push_back(variable_currentID);
	}

	VariablesCurrent_ = VariablesCurrent;


	// debug
	cout<<"----------------------------------------"<<endl;
	cout<<"----"<<endl;
	cout<<"derivatives of current variables : "<<endl;
	for(int i=0;i<SizeVariables_;i++)
	{
		int variableID = i;
		cout<<"    variableID "<<variableID<<": previous variable "<<VariablesPrevious_[i]<<", derivative "<<derivatives[i]<<", current variable "<<VariablesCurrent_[variableID]<<endl;
	}
	cout<<"----"<<endl;
	cout<<"----------------------------------------"<<endl;

	//
}
