#include <iostream>
#include <vector>
#include <string>

//#include "Optimization.hh"
#include "UserCostFunction.hh"
#include "SteepestCostFunction.hh"

#include "UserResidualBlockFunction.hh"
#include "PolyResidualBlockFunction.hh"

#include "UserOptimizationManager.hh"
#include "SteepestOptimizationManager.hh"


using namespace std;

void test1();
void test2();
void test3();

int main()
{
	cout<<"Hello "<<endl;

	test3();

	return 1;
}

void test1()
{
	int residualSize = 1;
	int varialbeSize = 3;
	UserCostFunction* costFunction = new SteepestCostFunction("test", 2, varialbeSize, residualSize);

	// observations
	int sizeObservations = 5;
	double observation_xs[5] = {0,1,2,-1,-2};
	double observation_ys[5] = {1,6,17,2,9};

	for(int i=0;i<sizeObservations;i++)
	{
		vector<double> observation_current;
		observation_current.push_back(observation_xs[i]);
		observation_current.push_back(observation_ys[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	costFunction->Show();

	// derivative
	vector<double> variables;
	variables.push_back(0);
	variables.push_back(2);
	variables.push_back(3);

	double derivative0;
	bool isDerivativeGood = costFunction->GetOneDerivative(0,variables,derivative0);

	if(isDerivativeGood)
	{
		cout<<"derivative0 "<<derivative0<<endl;
	}
	else
	{
		cout<<"Error happend in Derivative "<<endl;
	}

}

void test2()
{
	int residualSize = 1;
	int varialbeSize = 3;
	UserCostFunction* costFunction = new SteepestCostFunction("test", 2, varialbeSize, residualSize);

	// observations
	int sizeObservations = 5;
	double observation_xs[5] = {0,1,2,-1,-2};
	double observation_ys[5] = {1,6,17,2,9};

	for(int i=0;i<sizeObservations;i++)
	{
		vector<double> observation_current;
		observation_current.push_back(observation_xs[i]);
		observation_current.push_back(observation_ys[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	costFunction->Show();

	for(int i=0;i<10;i++)
	{
		cout<<"Variables(Plan) ID "<<i<<endl;
		double a0 = -4+i;
		double a1 = 2;
		double a2 = 3;

		// derivative
		vector<double> variables;
		variables.push_back(a0);
		variables.push_back(a1);
		variables.push_back(a2);

		vector<double> derivatives;
		bool isDerivativeGood = costFunction->GradientFunction(variables,derivatives);

		if(isDerivativeGood)
		{
			cout<<"derivative : "<<derivatives[0]<<", "<<derivatives[1]<<", "<<derivatives[2]<<endl;
		}
		else
		{
			cout<<"Error happend in Derivative "<<endl;
		}
		cout<<""<<endl;
	}

}

void test3()
{
	int observationsSize = 2;
	int residualSize = 1;
	int varialbeSize = 3;
	UserOptimizationManager * sd = new SteepestOptimizationManager("SteepestDecentMethod",observationsSize,varialbeSize,residualSize);

	// set variables
	vector<double> variables;
	variables.push_back(5);
	variables.push_back(6);
	variables.push_back(4);
	sd->SetUserInitialization(variables);

	// set cost function
	UserCostFunction* costFunction = new SteepestCostFunction("costFunction",observationsSize,varialbeSize,residualSize);

	int LengthObservations = 5;
	double observation_xs[5] = {0,1,2,-1,-2};
	double observation_ys[5] = {1,6,17,2,9};

	for(int i=0;i<LengthObservations;i++)
	{
		vector<double> observation_current;
		observation_current.push_back(observation_xs[i]);
		observation_current.push_back(observation_ys[i]);
		costFunction->AddResidualBlock(observation_current);
	}

	sd->SetUserInitialization(costFunction);


	// initialize
	sd->Initialize();
}
