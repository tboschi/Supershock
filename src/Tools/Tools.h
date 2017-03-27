/*
 * Flux creator for Monte Carlo using published fluxes
 *
 * Author: Tommaso Boschi
 */

#ifndef fluxdriver_H
#define fluxdriver_H

#include <iostream>
#include <fstream>

//Boost lib include
#include "boost/random.h"

//ROOT include
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

//GENIE include
#include "GHepParticle.h"
#include "Constants.h"


//Kinematic functions
namespace Tools
{
	namespace Kine
	{
		double ShrockFactor(double M_Meson, double M_Lepton, double M_Sterile); 
		double ShrockRho(double X double Y);
		double ShrockFM(double X, double Y);
		double ShrockLambda(double X, double Y, double Z);
		double I1(double, double);
		double I2(double, double);
		double I1_3arg_e(double);
		double I1_3arg_mue(double);
		double I1_3arg_mu(double);
		double I2_3arg_e(double);
		double I2_3arg_mu(double);
	}
	
	//Constants
	namespace Const
	{
		//CKM entries
		double fV_ud = 0.97417;
		double fV_us = 0.2248;
		double fV_ub = 0.0409;
		double fV_cd = 0.220;
		double fV_cs = 0.995;
		double fV_cb = 0.0405;
		double fV_td = 0.0082;
		double fV_ts = 0.0400;
		double fV_tb = 1.009;

		//PMNS entries
		double fU_e1 = 0.81;
		double fU_e2 = 0.54;
		double fU_e3 = -0.15;
		double fU_m1 = -0.35;
		double fU_m2 = 0.70;
		double fU_m3 = 0.62;
		double fU_t1 = 0.44;
		double fU_t2 = -0.45;
		double fU_t3 = 0.77;


		//SM constant
		double fSin2W = 0.231;			//Sin weinberg squared
		double fFPion2 = pow(0.1302, 2.0);		//Decay constant
	}
}
