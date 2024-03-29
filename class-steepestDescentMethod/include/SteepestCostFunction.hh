#ifndef STEEPESTCOSTFUNCTION_HH
#define STEEPESTCOSTFUNCTION_HH

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "UserCostFunction.hh"

#include "UserResidualBlockFunction.hh"
#include "PolyResidualBlockFunction.hh"

using namespace std;

class SteepestCostFunction : virtual public UserCostFunction
{
    public:
		SteepestCostFunction(string name, int SizeObservations, int SizeVariables, int SizeResiduals);
		~SteepestCostFunction();
	
    public:
		void SetStepLength(double delta);
		void Show();

    public:
		virtual void AddResidualBlock(vector<double> observations);
		virtual bool CostFunction(vector<double> variables, vector<double> &CostFunctionValues);

    public:
		virtual bool GetOneDerivative(int VarialbleID, vector<double> variables, double &theDerivativeValue);

	protected:
		// for derivative calculation
		double delta_;

    private:
		string name_;
};
#endif
