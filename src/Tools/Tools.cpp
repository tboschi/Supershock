#include "Tools.h"

//Kinematic factors
double Tools::Kine::ShrockFactor(double M_Meson, double M_Lepton, double M_Sterile) //Correct scaling of flux
{
	double dM_a = pow(M_Lepton/M_Meson, 2.0);
	double dM_i = pow(M_Sterile/M_Meson, 2.0);	

	if (M_Meson >= M_Lepton + M_Sterile)
		return ShrockRho(dM_a, dM_i)/(dM_a * pow(1-dM_a, 2.0));
	else return 0;
}

double Tools::Kine::ShrockRho(double X double Y)
{
	return ShrockFM(X, Y)*sqrt(ShrockLambda(1, X, Y));
}

double Tools::Kine::ShrockFM(double X, double Y)
{
	return X+Y - (X-Y)*(X-Y);
}

double Tools::Kine::ShrockLambda(double X, double Y, double Z)
{
	return X*X + Y*Y + Z*Z - 2*(X*Y + X*Z + Y*Z);
}

double Tools::Kine::I1_f(double t, double X, double Y, double Z)	//To be integrated
{
	return (t-X*X-Y*Y)*(1+Z*Z-t)*sqrt(ShrockLambda(t, X*X, Y*Y))*sqrt(shrockLambda(1, t, Z*Z)) / t;
}

double Tools::Kine::I1_xyx(double X, double Y, double Z)
{
	double A = (1-Z)*(1-Z);
	double B = (X+Y)*(X+Y);
	if (A > B)
	{
		double tmp = B;
		B = A;
		A = tmp;
	}
	double h = (B-A)/double(Sample);
	double Integral = 0;	//3/8 Simpson's method for integration
	for (double a = A; a <= B; a = b)
	{
		b = a + (B-A)/step;
		Integral = 0.125 * (I1_f(a, X, Y, Z) + 3*I1_f((a+2*b)/3.0, X, Y, Z) + 3*I1_f((2*a+b)/3.0, X, Y, Z) + I1_f(b, X, Y, Z));
	}	
	return 12.0 * Integral;
}

double Tools::Kine::I2_f(double t, double X, double Y, double Z)	//To be integrated
{
	return (1+X*X-t)*sqrt(ShrockLambda(t, Y*Y, Z*Z))*sqrt(shrockLambda(1, t, X*X)) / t;
}

double Tools::Kine::I2_xyz(double X, double Y, double Z)
{
	double A = (1-X)*(1-X);
	double B = (Y+Z)*(Y+Z);
	if (A > B)
	{
		double tmp = B;
		B = A;
		A = tmp;
	}
	double h = (B-A)/double(Sample);
	double Integral = 0;	//3/8 Simpson's method for integration
	for (double a = A; a <= B; a = b)
	{
		b = a + (B-A)/step;
		Integral = 0.125 * (I2_f(a, X, Y, Z) + 3*I2_f((a+2*b)/3.0, X, Y, Z) + 3*I2_f((2*a+b)/3.0, X, Y, Z) + I2_f(b, X, Y, Z));
	}	
	return 24.0*Y*Z * Integral;
}

double Tools::Kine::I2_xy(double X, double Y)
{
	return ((1+X-Y)*(1+X+2*Y) - 4*X) * sqrt(ShrockLambda(1, X, Y));
}

double Tools::Kine::I3_xy(double X, double Y)
{
	return (1+2*Y)(1-Y) * sqrt(ShrockLambda(1, X, Y));
}

double Tools::Kine::I1_3arg_e(double);
double Tools::Kine::I1_3arg_mue(double);
double Tools::Kine::I1_3arg_mu(double);
double Tools::Kine::I2_3arg_e(double);
double Tools::Kine::I2_3arg_mu(double);