#include <iostream>
#include <fstream>
#include <cstring>

void PrintFile(std::string Root, std::string Out, bool Tau = false)
{
	TFile *fRoot = new TFile(Root.c_str(), "OPEN");

	TH1D *hTotal = GetCast(fRoot->Get("htotal"));
	TH1D *hPion  = GetCast(fRoot->Get("hpion"));
	TH1D *h2Pion = GetCast(fRoot->Get("h2pion"));
	TH1D *hKaon  = GetCast(fRoot->Get("hkaon"));
	TH1D *hKaon0 = GetCast(fRoot->Get("hkaon0"));
	TH1D *hCharm = GetCast(fRoot->Get("hcharm"));
	TH1D *hMuon  = GetCast(fRoot->Get("hmuon"));
	TH1D *hTauE  = GetCast(fRoot->Get("htaue"));
	TH1D *hTauM  = GetCast(fRoot->Get("htaum"));

	std::ofstream fOut(Out.c_str());

	double EBin = 20.0/100.0;
	double Scale = 1.0e20 / (574.0*574.0);
	for (unsigned int i = 0; i < hTotal->GetNbinsX(); ++i)
	{
		fOut << hTotal->GetBinCenter(i+1)  << "\t";
		fOut << Scale * hTotal->GetBinContent(i+1) << "\t";
		if (!Tau)
		{
			fOut << Scale * hPion->GetBinContent(i+1)  << "\t";
			fOut << Scale * hKaon->GetBinContent(i+1)  << "\t";
			fOut << Scale * hKaon0->GetBinContent(i+1) << "\t";
			fOut << Scale * hMuon->GetBinContent(i+1)  << std::endl;
		}
		else
		{
			fOut << Scale * hCharm->GetBinContent(i+1)  << "\t";
			fOut << Scale * hTauE->GetBinContent(i+1)  << "\t";
			fOut << Scale * hTauM->GetBinContent(i+1) << "\t";
			fOut << Scale * hPion->GetBinContent(i+1) << "\t";
			fOut << Scale * h2Pion->GetBinContent(i+1)  << std::endl;
		}
	}
	fRoot->Close();
	fOut.close();
}

TH1D* GetCast(TObject *X)
{
	if (X)
		return dynamic_cast<TH1D*> (X);
	else
		return NULL;
}
