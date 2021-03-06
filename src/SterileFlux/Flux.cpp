#include "Flux.h"

//ctor
Flux::Flux(std::string HistFile) :
	hTotal(0),
        hPion(0),
        h2Pion(0),
        hKaon(0),
        hKaon0(0),
        hCharm(0),
        hMuon(0),
        hTauE(0),
        hTauM(0)
{
	TFile* InFile = new TFile(HistFile.c_str(), "READ");

	CloneCopy(hTotal, InFile->Get("htotal"));
	CloneCopy(hPion,  InFile->Get("hpion"));
	CloneCopy(h2Pion, InFile->Get("h2pion"));
	CloneCopy(hKaon,  InFile->Get("hkaon"));
	CloneCopy(hKaon0, InFile->Get("hkaon0"));
	CloneCopy(hCharm, InFile->Get("hcharm"));
	CloneCopy(hMuon,  InFile->Get("hmuon"));
	CloneCopy(hTauE,  InFile->Get("htaue"));
	CloneCopy(hTauM,  InFile->Get("htaum"));

	InFile->Close();

}

//copy ctor
Flux::Flux(const Flux & f)
{
	CloneCopy(hTotal, f.Get("Total"));
	CloneCopy(hPion,  f.Get("Pion"));
	CloneCopy(h2Pion, f.Get("2Pion"));
	CloneCopy(hKaon,  f.Get("Kaon"));
	CloneCopy(hKaon0, f.Get("Kaon0"));
	CloneCopy(hCharm, f.Get("Charm"));
	CloneCopy(hMuon,  f.Get("Muon"));
	CloneCopy(hTauE,  f.Get("TauE"));
	CloneCopy(hTauM,  f.Get("TauM"));
}

//detor
Flux::~Flux()
{
	delete hTotal;
	delete hPion;
	delete h2Pion;
	delete hKaon;
	delete hKaon0;
	delete hCharm;
	delete hMuon;
	delete hTauE;
	delete hTauM;
}

//Clone functions, so that an object from this class owns valid copies of the histograms
void Flux::CloneCopy(TH1D*& T, TObject* X)
{
	if (X)
	{
		T = dynamic_cast<TH1D*> (X->Clone());
		T->SetDirectory(0);
	}
	else
		T = NULL;
}

void Flux::CloneCopy(TH1D*& T, TH1D* X)
{
	if (X)
	{
		T = dynamic_cast<TH1D*> (X->Clone());
		T->SetDirectory(0);
	}
	else
		T = NULL;
}


//Get functions

TH1D* Flux::Get(std::string T) const
{
	if (T == "Total")
	{
		if (hTotal)
			return hTotal;
		else return NULL;
	}
	else if (T == "Pion")
	{
		if (hPion)
			return hPion;
		else return NULL;
	}
	else if (T == "2Pion")
	{
		if (h2Pion)
			return h2Pion;
		else return NULL;
	}
	else if (T == "Kaon")
	{
		if (hKaon)
			return hKaon;
		else return NULL;
	}

	else if (T == "Kaon0")
	{
		if (hKaon0)
			return hKaon0;
		else return NULL;
	}
	else if (T == "Charm")
	{
		if (hCharm)
			return hCharm;
		else return NULL;
	}
	else if (T == "Muon")
	{
		if (hMuon)
			return hMuon;
		else return NULL;
	}
	else if (T == "TauE")
	{
		if (hTauE)
			return hTauE;
		else return NULL;
	}
	else if (T == "TauM")
	{
		if (hTauM)
			return hTauM;
		else return NULL;
	}
	else
		return NULL;
}
