#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <getopt.h>

#include "Tools.h"

int main(int argc, char** argv)
{

	const struct option longopts[] = 
	{
		{"output", 	required_argument, 	0, 'o'},
		{"help", 	no_argument,	 	0, 'h'},
		{0,	0, 	0,	0},
	};

	int index; 
	int iarg = 0;
	opterr = 1;
	
	std::ofstream OutFile;
	
//Initialize variables
	
	while((iarg = getopt_long(argc,argv, "o:h", longopts, &index)) != -1)	
	{
		switch(iarg)
		{
			case 'o':
				OutFile.open(optarg);
				if (!OutFile.is_open())
				{
					std::cout << "Wrong input!" << std::endl;
					return 1;
				}
				break;
			case 'h':
				std::cout << "Compute Shrock factors" << std::endl;
				std::cout << "Usage : " << std::endl;
				std::cout << "decayplot [OPTIONS]" << std::endl;
				std::cout <<"\n  -o,  --output" << std::endl;
				std::cout << "\t\tOutput file to save plot" << std::endl;
				std::cout <<"\n  -h,  --help" << std::endl;
				std::cout << "\t\tPrint this message and exit" << std::endl;
				return 1;
			default:
				return 1;
		}
	}



	double Elec = Const::fMElectron;
	double Muon = Const::fMMuon;
	double Tau = Const::fMTau;
	double Pion = Const::fMPion;
	double Pion0 = Const::fMPion0;
	double Kaon = Const::fMKaon;
	double Kaon0 = Const::fMKaon0;
	double Charm = Const::fMDs;
	//To have multiple output, handled by usage
	std::ostream &Out = (OutFile.is_open()) ? OutFile : std::cout;

	Out << "#MS\tElPi\tElKa\tElCh\tMuPi\tMuKa\tMuCh\tTuCh" << std::endl;
	for (double t = 0; t < 2.0; t += 0.001)
	{
		Out << t << "\t";
		Out << Kine::ShrockFactor(Pion, Elec, t) << "\t";
		Out << Kine::ShrockFactor(Kaon, Elec, t) << "\t";
		Out << Kine::ShrockFactor(Charm, Elec, t) << "\t";
		Out << Kine::ShrockFactor(Pion, Muon, t) << "\t";
		Out << Kine::ShrockFactor(Kaon, Muon, t) << "\t";
		Out << Kine::ShrockFactor(Charm, Muon, t) << "\t";
		Out << Kine::ShrockFactor(Charm, Tau, t) << "\t";
		Out << std::endl;
	}
	//Create object from classes
	//e.g.	Decay * SuperGamma = new Decay(M_Sterile, U_e, U_m, U_t);

	//Main body

	//Garbage collection

	return 0;
}
