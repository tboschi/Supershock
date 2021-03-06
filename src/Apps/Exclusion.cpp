#include <iostream>
#include <fstream>
#include <cstring>
#include <getopt.h>

#include "EventGenerator.h"
#include "FluxDriver.h"
#include "DecayRates.h"
#include "Detector.h"

#include "TH2D.h"
#include "TFile.h"

void Usage(char* argv0);

int main(int argc, char** argv)
{
	const struct option longopts[] = 
	{
		{"smconfig", 	required_argument, 	0, 's'},
		{"detconfig", 	required_argument,	0, 'd'},
		{"fluxconfig", 	required_argument,	0, 'f'},
		{"channel", 	required_argument,	0, 'c'},
		{"threshold", 	required_argument,	0, 't'},
		{"efficiency", 	no_argument,		0, 'W'},
		{"output", 	required_argument,	0, 'o'},
		{"help", 	no_argument,	 	0, 'h'},
		{0,	0, 	0,	0},
	};

	int index; 
	int iarg = 0;
	opterr = 1;
	
	//Initialize variables
	std::string SMConfig, DetConfig;
	std::string FluxConfig, EffFile;
	std::ofstream OutFile;
	//TFile *OutFile;
	std::string Channel = "ALL";
	bool UeFlag = false;
	bool UmFlag = false;
	bool UtFlag = false;
	bool Efficiency = false;
	
	while((iarg = getopt_long(argc,argv, "s:d:f:c:t:o:WEMTh", longopts, &index)) != -1)
	{
		switch(iarg)
		{
			case 's':
				SMConfig.assign(optarg);
				break;
			case 'd':
				DetConfig.assign(optarg);
				break;
			case 'f':
				FluxConfig.assign(optarg);
				break;
			case 'c':
				Channel.assign(optarg);
				break;
			case 'o':
				OutFile.open(optarg);
				//OutFile = new TFile(optarg, "RECREATE");
				break;
			case 'W':
				Efficiency = true;
				break;
			case 'E':
				UeFlag = true;
				break;
			case 'M':
				UmFlag = true;
				break;
			case 'T':
				UtFlag = true;
				break;
			case 'h':
				Usage(argv[0]);
				return 1;
			default:
				break;
		}
	}

	std::ostream &Out = (OutFile.is_open()) ? OutFile : std::cout;

	//TH2D * logCont = new TH2D ("logcont", "Above threshold", 100, -2.0, 0.0, 100, -10.0, -4.0);
	//TH2D * Contour = new TH2D ("contour", "Above threshold", 100, 0.01, 1.0, 100, 1.0e-10, 1.0e-4);
	EventGenerator * EvGen = new EventGenerator(SMConfig, DetConfig, FluxConfig);
	
	double Uo;
	if (UeFlag)
	{
		EvGen->SetChannel(Channel, Efficiency, 'E');
		Uo = EvGen->GetUm();
	}
	if (UmFlag)
	{
		EvGen->SetChannel(Channel, Efficiency, 'M');
		Uo = EvGen->GetUe();
	}
	if (UtFlag)
		Uo = EvGen->GetUt();

	EvGen->SetMass(0);
	EvGen->SyncUu();
	
	unsigned int Grid = 250;
	double Mass, Uu;
	double contMass, contUu, contN;
	std::vector<double> vSignal;	//summing over energy, array of Uus
	
	EvGen->SyncUu(0);

	for (double logMass = -2.0; logMass < -0.3; logMass += 1.7/Grid)	//increase mass log
	{
		Mass = pow(10.0, logMass);
		std::cout << "Mass " << Mass << std::endl;
		EvGen->SetMass(Mass);
		EvGen->MakeFlux(1);

		vSignal.clear();
		vSignal.resize(Grid);	//number of Uus probing

		double Start, End;
		double EnStep = EvGen->GetRange(Start, End)/EvGen->GetBinNumber();
		for (double Energy = Start; Energy < End; Energy += EnStep)
		{
			unsigned int i = 0;
			for (double logUu2 = -15.0; logUu2+1e-6 < 0.0; logUu2 += 15.0/Grid, ++i)	//increase Uu logarithmically
			{
				Uu = pow(10.0, 0.5*logUu2);
				//if (UeFlag)
				//	EvGen->SetUe(Uu);
				//if (UmFlag)
				//	EvGen->SetUm(Uu);
				//if (UtFlag)
				//	EvGen->SetUt(Uu);
				EvGen->SetUe(Uu, 1);	//production
				EvGen->SetUm(Uu, 0);	//decay
	
				vSignal.at(i) += EnStep * EvGen->DecayNumber(Energy, Efficiency);
			}
		}

		unsigned int j = 0;
		for (double logUu2 = -15.0; logUu2+1e-6 < 0.0; logUu2 += 15.0/Grid, ++j)	//increase Uu logarithmically
		{
			Uu = pow(10.0, 0.5*logUu2);
			//Out << Mass << "\t" << Uu*Uu << "\t" << vSignal.at(j) << std::endl;
			//Out << Mass << "\t" << Uo*Uu << "\t" << vSignal.at(j) << std::endl;
			Out << Mass << "\t" << Uu*Uu << "\t" << vSignal.at(j) << std::endl;
		}
	}

	//OutFile->cd();
	//logCont->Write();
	//Contour->Write();
	//OutFile->Close();

	return 0;
}
	
void Usage(char* argv0)
{
	std::cout << "Description" << std::endl;
	std::cout << "Usage : " << std::endl;
	std::cout << argv0 << " [OPTIONS]" << std::endl;
	std::cout <<"\n  -s,  --smconfig" << std::endl;
	std::cout << "\t\tStandard Model configuration file" << std::endl;
	std::cout <<"\n  -d,  --detconfig" << std::endl;
	std::cout << "\t\tDetector configuration file" << std::endl;
	std::cout <<"\n  -f,  --fluxconfig" << std::endl;
	std::cout << "\t\tFlux configuration file" << std::endl;
	std::cout <<"\n  -o,  --output" << std::endl;
	std::cout << "\t\tOutput file" << std::endl;
	std::cout <<"\n  -c,  --channel" << std::endl;
	std::cout << "\t\tDecay channel, defaul ALL" << std::endl;
	std::cout <<"\n  -E,  -M,  -T" << std::endl;
	std::cout << "\t\tSelect which mixing element" << std::endl;
	std::cout <<"\n  -h,  --help" << std::endl;
	std::cout << "\t\tPrint this message and exit" << std::endl;
}
