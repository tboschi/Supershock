#include "Flux.h"



Flux(double MuonPion, double MuonKaon, double ElectronPion, double ElectronKaon, double ElectronKaon3, double MuonKaonOther);
{
	SetMuonPion(MuonPion);
        SetMuonKaon(MuonKaon);
        SetElectronPion(ElectronPion);
        SetElectronKaon(ElectronKaon);
        SetElectronKaon3(ElectronKaon3);
        SetMuonKaonOther(MuonKaonOther);
}


//Get functions
double Flux::GetMuonPion()
{
	return fMuonPion;
}

double Flux::GetMuonKaon()
{
	return fMuonKaon;
}

double Flux::GetElectronPion()
{
	return fElectronPion;
}

double Flux::GetElectronKaon()
{
	return fElectronKaon;
}

double Flux::GetElectronKaon3()
{
	return fElectronKaon3;
}

double Flux::GetMuonKaonOther()
{
	return fMuonKaonOther;
}

double Flux::GetTotalFlux()
{
	return (GetMuonPion() + GetMuonKaon() + GetElectronPion() + GetElectronKaon() + GetElectronKaon3() + GetMuonKaonOther());
}

//Set functions
void Flux::SetMuonPion(double X)
{
	fMuonPion = X;
}

void Flux::SetMuonKaon(double X)
{
	fMuonKaon = X;
}

void Flux::SetElectronPion(double X)
{
	fElectronPion = X;
}

void Flux::SetElectronKaon(double X)
{
	fElectronKaon = X;
}

void Flux::SetElectronKaon3(double X)
{
	fElectronKaon = X;
}

void Flux::SetMuonKaonOther(double X)
{
	fMuonKaonOther = X;
}

void Flux::SetTotalFlux(double X)	//Rescale each component
{
	double Ratio = X/GetTotalFlux();
	SetMuonPion(GetMuonPion()*Ratio);
	SetMuonKaon(GetMuonKaon()*Ratio);
	SetElectronPion(GetElectronPion()*Ratio);
	SetElectronKaon(GetElectronKaon()*Ratio);
	SetElectronKaon3(GetElectronKaon3()*Ratio);
	SetMuonKaonOther(GetMuonKaonOther()*Ratio);
}

