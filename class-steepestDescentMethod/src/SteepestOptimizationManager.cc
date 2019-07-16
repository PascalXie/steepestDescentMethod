#include "SteepestOptimizationManager.hh"

//-------------------------
// Constructor
//-------------------------
SteepestOptimizationManager::SteepestOptimizationManager(string name, int ObservationsSize, int VariablesSize, int ResidualsSize)
:	UserOptimizationManager(name+"_baseClass",ObservationsSize,VariablesSize,ResidualsSize),
	name_(name)
{}

//-------------------------
// Destructor
//-------------------------
SteepestOptimizationManager::~SteepestOptimizationManager()
{}

//-------------------------
// Public
//-------------------------
void SteepestOptimizationManager::SetUserInitialization(UserCostFunction* costFunction)
{
	costFunction_ = costFunction;

	IsInitializationCostFunctionSet_ = true;

	cout<<"-----------------------------------------"<<endl;
	cout<<"----"<<endl;
	cout<<"Class SteepestOptimizationManager::SetUserInitialization "<<endl;
	cout<<"Cost Function set, with informations : "<<endl;
	costFunction_->Show();
	cout<<"----"<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<endl;
}

void SteepestOptimizationManager::SetUserInitialization(vector<double> variables)
{
	if(variables.size()!=SizeVariables_) 
	{
		cout<<"An error happend with class  SteepestOptimizationManager::SetUserInitialization"<<endl;
		return;
	}

	initializationVariables_ = variables;

	IsInitializationVariablesSet_ = true;

	// debug
	cout<<"-----------------------------------------"<<endl;
	cout<<"----"<<endl;
	cout<<"Class SteepestOptimizationManager::SetUserInitialization "<<endl;
	cout<<"Variables set for initialization, with informations : "<<endl;
	for(int i=0;i<SizeVariables_;i++)
		cout<<"variable ID "<<i<<", value "<<initializationVariables_[i]<<endl;
	cout<<"----"<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<endl;
}
