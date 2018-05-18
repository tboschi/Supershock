#include <FluxDriver.h>

FluxDriver::FluxDriver(std::string FluxConfig) : 
	M_Electron(Const::fMElectron),
	M_Muon(Const::fMMuon),
	M_Tau(Const::fMTau),
	M_Pion(Const::fMPion),
	M_Pion0(Const::fMPion0),
	M_Kaon(Const::fMKaon),
	M_Kaon0(Const::fMKaon0),
	M_Charm(Const::fMDs)
{
	fxNuElectron = 0;
	fxNuElectronBar = 0;
	fxNuMuon = 0;
	fxNuMuonBar = 0;
	fxNuTau = 0;
	fxNuTauBar = 0;

	std::stringstream ssL;
	std::string Line, Key, Name;
	Kine = false;
	Mod = false;
	
	std::ifstream ModFile;
	std::ifstream ConfigFile(FluxConfig.c_str());
	while (std::getline(ConfigFile, Line))
	{
		if (Line[0] == '#') continue;

		ssL.str("");
		ssL.clear();
		ssL << Line;

		if (ssL >> Key >> Name)
		{
			if (Key.find("Electron_")    != std::string::npos) fxNuElectron = new Flux(Name);
			if (Key.find("ElectronBar_") != std::string::npos) fxNuElectronBar = new Flux(Name);
			if (Key.find("Muon_")	     != std::string::npos) fxNuMuon = new Flux(Name);
			if (Key.find("MuonBar_")     != std::string::npos) fxNuMuonBar = new Flux(Name);
			if (Key.find("Tau_")	     != std::string::npos) fxNuTau = new Flux(Name);
			if (Key.find("TauBar_")	     != std::string::npos) fxNuTauBar = new Flux(Name);
			if (Key.find("BinNumber")    != std::string::npos) BinNumber = std::strtoul(Name.c_str(), NULL, 10);
			if (Key.find("RangeStart")   != std::string::npos) RangeStart = std::strtod(Name.c_str(), NULL);
			if (Key.find("RangeEnd")     != std::string::npos) RangeEnd = std::strtod(Name.c_str(), NULL);

			if (Key.find("Kinematics") != std::string::npos) 
			{
				KineFile = new TFile(Name.c_str(), "OPEN");
				Kine = true;

				CloneCopy(hMuonElec,  KineFile->Get("muonelec"));
				CloneCopy(hMuonMuon,  KineFile->Get("muonmuon"));
				CloneCopy(hKaonElec,  KineFile->Get("kaonelec"));
				CloneCopy(hKaonMuon,  KineFile->Get("kaonmuon"));
				CloneCopy(hKaon0Elec, KineFile->Get("kaon0elec"));
				CloneCopy(hKaon0Muon, KineFile->Get("kaon0muon"));
				CloneCopy(hTauEElec,  KineFile->Get("taueelec"));
				CloneCopy(hTauETau,   KineFile->Get("tauetau"));
				CloneCopy(hTauMMuon,  KineFile->Get("taummuon"));
				CloneCopy(hTauMTau,   KineFile->Get("taumtau"));

				KineFile->Close();
			}

			if (Key.find("Modifier") != std::string::npos)
			{
				Mod = true;
				ModFile.open(Name.c_str());
			}
		}
	}
	ConfigFile.close();

	//electronic components
	hTotalEn = new TH1D("htotalen", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionEn  = new TH1D("hpionen",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        hKaonEn  = new TH1D("hkaonen",  "Kaon flux",  BinNumber, RangeStart, RangeEnd);
        hKaon0En = new TH1D("hkaon0en", "Kaon0 flux", BinNumber, RangeStart, RangeEnd);
        hMuonEn  = new TH1D("hmuonen",  "Muon flux",  BinNumber, RangeStart, RangeEnd);
        hCharmEn = new TH1D("hcharmen", "Charm flux", BinNumber, RangeStart, RangeEnd);
	
	hTotalEa = new TH1D("htotalea", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionEa  = new TH1D("hpionea",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        hKaonEa  = new TH1D("hkaonea",  "Kaon flux",  BinNumber, RangeStart, RangeEnd);
        hKaon0Ea = new TH1D("hkaon0ea", "Kaon0 flux", BinNumber, RangeStart, RangeEnd);
        hMuonEa  = new TH1D("hmuonea",  "Muon flux",  BinNumber, RangeStart, RangeEnd);
        hCharmEa = new TH1D("hcharmea", "Charm flux", BinNumber, RangeStart, RangeEnd);

	//muonic components
	hTotalMn = new TH1D("htotalmn", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionMn  = new TH1D("hpionmn",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        hKaonMn  = new TH1D("hkaonmn",  "Kaon flux",  BinNumber, RangeStart, RangeEnd);
        hKaon0Mn = new TH1D("hkaon0mn", "Kaon0 flux", BinNumber, RangeStart, RangeEnd);
        hMuonMn  = new TH1D("hmuonmn",  "Muon flux",  BinNumber, RangeStart, RangeEnd);
        hCharmMn = new TH1D("hcharmmn", "Charm flux", BinNumber, RangeStart, RangeEnd);

	hTotalMa = new TH1D("htotalma", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionMa  = new TH1D("hpionma",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        hKaonMa  = new TH1D("hkaonma",  "Kaon flux",  BinNumber, RangeStart, RangeEnd);
        hKaon0Ma = new TH1D("hkaon0ma", "Kaon0 flux", BinNumber, RangeStart, RangeEnd);
        hMuonMa  = new TH1D("hmuonma",  "Muon flux",  BinNumber, RangeStart, RangeEnd);
        hCharmMa = new TH1D("hcharmma", "Charm flux", BinNumber, RangeStart, RangeEnd);

	//tauonic components
	hTotalTn = new TH1D("htotaltn", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionTn  = new TH1D("hpiontn",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        h2PionTn = new TH1D("h2piontn", "2Pion flux", BinNumber, RangeStart, RangeEnd);
        hCharmTn = new TH1D("hcharmtn", "Charm flux", BinNumber, RangeStart, RangeEnd);
        hTauETn  = new TH1D("htauetn",  "TauE flux",  BinNumber, RangeStart, RangeEnd);
        hTauMTn  = new TH1D("htaumtn",  "TauM flux",  BinNumber, RangeStart, RangeEnd);

	hTotalTa = new TH1D("htotalta", "Total flux", BinNumber, RangeStart, RangeEnd);
        hPionTa  = new TH1D("hpionta",  "Pion flux",  BinNumber, RangeStart, RangeEnd);
        h2PionTa = new TH1D("h2pionta", "2Pion flux", BinNumber, RangeStart, RangeEnd);
        hCharmTa = new TH1D("hcharmta", "Charm flux", BinNumber, RangeStart, RangeEnd);
        hTauETa  = new TH1D("htaueta",  "TauE flux",  BinNumber, RangeStart, RangeEnd);
        hTauMTa  = new TH1D("htaumta",  "TauM flux",  BinNumber, RangeStart, RangeEnd);

	M_Sterile_prev = -1.0;

	if (ModFile.is_open())
	{
		double Mass, X, Y;
		while (getline(ModFile, Line))
		{
			ssL.str("");
			ssL.clear();
			ssL << Line;

			ssL >> Mass >> X >> Y;
			vMdir.push_back(Mass);
			vXdir.push_back(X);
			vYdir.push_back(Y);
		}
		ModFile.close();
	}
}

FluxDriver::~FluxDriver()
{
	delete fxNuElectron;
	delete fxNuElectronBar;
	delete fxNuMuon;
	delete fxNuMuonBar;
	delete fxNuTau;
	delete fxNuTauBar;

	delete hTotalEn;
	delete hTotalEa;
	delete hPionEn;
	delete hPionEa;
	delete hKaonEn;
	delete hKaonEa;
	delete hKaon0En;
	delete hKaon0Ea;
	delete hMuonEn;
	delete hMuonEa;
	delete hCharmEn;
	delete hCharmEa;

	delete hTotalMn;
	delete hTotalMa;
	delete hPionMn;
	delete hPionMa;
	delete hKaonMn;
	delete hKaonMa;
	delete hKaon0Mn;
	delete hKaon0Ma;
	delete hMuonMn;
	delete hMuonMa;
	delete hCharmMn;
	delete hCharmMa;

	delete hTotalTn;
	delete hTotalTa;
	delete hPionTn;
	delete h2PionTn;
	delete hPionTa;
	delete h2PionTa;
	delete hCharmTn;
	delete hCharmTa;
	delete hTauETn;
	delete hTauETa;
	delete hTauETn;
	delete hTauETa;
}

void FluxDriver::CloneCopy(TH1D*& T, TObject* X)
{
	if (X)
	{
		T = dynamic_cast<TH1D*> (X->Clone());
		T->SetDirectory(0);
	}
	else
		T = NULL;
}

bool FluxDriver::MakeFlux(double M_Sterile, int H)	//helicity
{
	if (IsChanged(M_Sterile))
	{
		hTotalEn->Reset("ICES");	//Reset before generating
		hPionEn->Reset("ICES");
		hKaonEn->Reset("ICES"); 
		hKaon0En->Reset("ICES");
		hMuonEn->Reset("ICES"); 
                hCharmEn->Reset("ICES");

		hTotalMn->Reset("ICES");	//Reset before generating
		hPionMn->Reset("ICES");
		hKaonMn->Reset("ICES"); 
		hKaon0Mn->Reset("ICES");
		hMuonMn->Reset("ICES"); 
                hCharmMn->Reset("ICES");

		hTotalTn->Reset("ICES");
                hPionTn->Reset("ICES");
                h2PionTn->Reset("ICES");
                hCharmTn->Reset("ICES");
                hTauETn->Reset("ICES");
                hTauMTn->Reset("ICES");
                        
		hTotalEa->Reset("ICES");	//Reset before generating
		hPionEa->Reset("ICES");
		hKaonEa->Reset("ICES"); 
		hKaon0Ea->Reset("ICES");
		hMuonEa->Reset("ICES"); 
                hCharmEa->Reset("ICES");

		hTotalMa->Reset("ICES");	//Reset before generating
		hPionMa->Reset("ICES");
		hKaonMa->Reset("ICES"); 
		hKaon0Ma->Reset("ICES");
		hMuonMa->Reset("ICES"); 
                hCharmMa->Reset("ICES");

                hTotalTa->Reset("ICES");
                hPionTa->Reset("ICES");
                h2PionTa->Reset("ICES");
                hCharmTa->Reset("ICES");
                hTauETa->Reset("ICES");
                hTauMTa->Reset("ICES");

		if (fxNuElectron)	//Model on nu electron flux
		{
			SetHel(H);

			Flux sxFlux(*fxNuElectron);
			MakeElecComponent(1, sxFlux, M_Sterile);

			hTotalEn->Add(hPionEn);
			hTotalEn->Add(hKaonEn);
		 	hTotalEn->Add(hKaon0En);
			hTotalEn->Add(hMuonEn);
			hTotalEn->Add(hCharmEn);
		}
	
		if (fxNuElectronBar)	//Model on nu electron bar flux
		{
			SetHel(-H);

			Flux sxFlux(*fxNuElectronBar);
			MakeElecComponent(0, sxFlux, M_Sterile);

			hTotalEa->Add(hPionEa);
			hTotalEa->Add(hKaonEa);
		 	hTotalEa->Add(hKaon0Ea);
			hTotalEa->Add(hMuonEa);
			hTotalEa->Add(hCharmEa);
		}

		if (fxNuMuon)		//Model on nu mu flux
		{
			SetHel(H);

			Flux sxFlux(*fxNuMuon);
			MakeMuonComponent(1, sxFlux, M_Sterile);

			hTotalMn->Add(hPionMn);
			hTotalMn->Add(hKaonMn);
			hTotalMn->Add(hKaon0Mn);
			hTotalMn->Add(hMuonMn);
			hTotalMn->Add(hCharmMn);
		}
	
		if (fxNuMuonBar)	//Model on nu mu bar flux
		{
			SetHel(-H);

			Flux sxFlux(*fxNuMuonBar);
			MakeMuonComponent(0, sxFlux, M_Sterile);

			hTotalMa->Add(hPionMa);
			hTotalMa->Add(hKaonMa);
			hTotalMa->Add(hKaon0Ma);
			hTotalMa->Add(hMuonMa);
			hTotalMa->Add(hCharmMa);
		}
	
		if (fxNuTau)	//Model on nu electron flux
		{
			Flux sxFlux(*fxNuTau);
			MakeTauComponent(1, sxFlux, M_Sterile);

			hTotalTn->Add(hPionTn);
			hTotalTn->Add(h2PionTn);
		 	hTotalTn->Add(hCharmTn);
			hTotalTn->Add(hTauETn);
			hTotalTn->Add(hTauMTn);
		}
	
		if (fxNuTauBar)	//Model on nu electron bar flux
		{
			Flux sxFlux(*fxNuTauBar);
			MakeTauComponent(0, sxFlux, M_Sterile);

			hTotalTa->Add(hPionTa);
			hTotalTa->Add(h2PionTa);
		 	hTotalTa->Add(hCharmTa);
			hTotalTa->Add(hTauETa);
			hTotalTa->Add(hTauMTa);
		}

		return true;
	}
	else 
		return false;
}

void FluxDriver::MakeElecComponent(bool Neutrino, Flux &sxFlux, double M_Sterile)
{
	//pi- -> e- nu_e_bar
	TH1D *hPoint;
	if (hPoint = sxFlux.Get("Pion"))
	{
		hPoint->Scale(Kine::ShrockFactor(M_Pion, M_Electron, M_Sterile, GetHel()));
		if (Neutrino)
			hPionEn->Add(hPoint);
		else
			hPionEa->Add(hPoint);
	}

	//K- -> pi0 e- nu_e_bar
	if (hPoint = sxFlux.Get("Kaon"))
	{
		double KaonFactor = 1.582e-3/(1.582e-3+5.07) * Kine::ShrockFactor(M_Kaon, M_Electron, M_Sterile, GetHel());	//Two body
		if (Kine)
		{
			double KE = hKaonElec->GetBinContent(hKaonElec->FindBin(M_Sterile+1e-9)+1);	//1e-9 to prevent bin error
			KaonFactor += 5.07/(1.582e-3+5.07) * KE;	//Three body
		}
		else if (M_Sterile < M_Kaon - M_Pion0 - M_Electron)
			KaonFactor += 5.07/(1.582e-3+5.07);	//simple scaling
		else KaonFactor += 0;	//simple scaling
		hPoint->Scale(KaonFactor);
		if (Neutrino)
			hKaonEn->Add(hPoint);
		else
			hKaonEa->Add(hPoint);
	}

	//K0 -> pi- e- nu_e_bar
	if (hPoint = sxFlux.Get("Kaon0"))
	{
		if (Kine)
		{
			double K0E = hKaon0Elec->GetBinContent(hKaon0Elec->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			hPoint->Scale(K0E);
		}
		else if (M_Sterile > M_Kaon0 - M_Pion - M_Electron)
			hPoint->Scale(0);	//simple scaling
		if (Neutrino)
			hKaon0En->Add(hPoint);
		else
			hKaon0Ea->Add(hPoint);
	}

	//mu -> nu_mu e nu_e
	if (hPoint = sxFlux.Get("Muon"))
	{
		if (Kine)
		{
			double ME = hMuonElec->GetBinContent(hMuonElec->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			hPoint->Scale(ME);
		}
		else if (M_Sterile > M_Muon - M_Electron)
			hPoint->Scale(0);
		if (Neutrino)
			hMuonEn->Add(hPoint);
		else
			hMuonEa->Add(hPoint);
	}

	//Ds -> e nu_e
	if (hPoint = sxFlux.Get("Charm"))
	{
		hPoint->Scale(Kine::ShrockFactor(M_Charm, M_Electron, M_Sterile, GetHel()));
		if (Neutrino)
			hCharmEn->Add(hPoint);
		else 
			hCharmEa->Add(hPoint);
	}
}

void FluxDriver::MakeMuonComponent(bool Neutrino, Flux &sxFlux, double M_Sterile)
{
	//pi+ -> mu+ nu_mu
	TH1D *hPoint;
	if (hPoint = sxFlux.Get("Pion"))
	{	
		hPoint->Scale(Kine::ShrockFactor(M_Pion, M_Muon, M_Sterile, GetHel()));
		if (Neutrino)
			hPionMn->Add(hPoint);
		else 
			hPionMa->Add(hPoint);
	}

	//K+ -> mu+ nu_mu	&&	pi0 mu+ nu_mu
	if (hPoint = sxFlux.Get("Kaon"))
	{
		double KaonFactor = 63.56/(63.56+3.35) * Kine::ShrockFactor(M_Kaon, M_Muon, M_Sterile, GetHel());	//Two body
		if (Kine)
		{
			double KM = hKaonMuon->GetBinContent(hKaonMuon->FindBin(M_Sterile+1e-9)+1);	//1e-9 to prevent bin error
			KaonFactor += 3.35/(63.56+3.35) * KM;	//Three body
		}
		else if (M_Sterile < M_Kaon - M_Pion0 - M_Muon)
			KaonFactor += 3.35/(63.56+3.35);	//simple scaling
		else KaonFactor += 0;	//simple scaling
		hPoint->Scale(KaonFactor);
		if (Neutrino)
			hKaonMn->Add(hPoint);
		else
			hKaonMa->Add(hPoint);
	}

	//K0 -> pi- mu+ nu_mu
	if (hPoint = sxFlux.Get("Kaon0"))
	{
		if (Kine)
		{
			double K0M = hKaon0Muon->GetBinContent(hKaon0Muon->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
				hPoint->Scale(K0M);	//Three body
		}
		else if (M_Sterile > M_Kaon0 - M_Pion - M_Muon)
			hPoint->Scale(0);	//simple scaling
		if (Neutrino)
			hKaon0Mn->Add(hPoint);
		else
			hKaon0Ma->Add(hPoint);
	}

	//mu -> nu_mu e nu_e
	if (hPoint = sxFlux.Get("Muon"))
	{
		if (Kine)
		{
			double MM = hMuonMuon->GetBinContent(hMuonMuon->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			hPoint->Scale(MM);	//Three body
		}
		else if (M_Sterile > M_Muon - M_Electron)
			hPoint->Scale(0);
		if (Neutrino)
			hMuonMn->Add(hPoint);
		else
			hMuonMa->Add(hPoint);
	}

	//Ds -> mu nu_mu
	if (hPoint = sxFlux.Get("Charm"))
	{
		hPoint->Scale(Kine::ShrockFactor(M_Charm, M_Muon, M_Sterile, GetHel()));
		if (Neutrino)
			hCharmMn->Add(hPoint);
		else 
			hCharmMa->Add(hPoint);
	}	
}

void FluxDriver::MakeTauComponent(bool Neutrino, Flux &sxFlux, double M_Sterile)
{
	//Ds -> tau nu_tau
	TH1D *hPoint;
	if (hPoint = sxFlux.Get("Charm"))
	{
		hPoint->Scale(Kine::ShrockFactor(M_Charm, M_Tau, M_Sterile, GetHel()));

		//modifier from empirical observation
		if (Mod && M_Sterile < M_Charm - M_Tau)
		{
			TH1D *hTemp = dynamic_cast<TH1D*> (hPoint->Clone());
			//TH1D *hTemp2 = dynamic_cast<TH1D*> (hCharmTn->Clone());
			hPoint->Reset("ICES");

			double xdir, ydir;
			Modify(xdir ,ydir, M_Sterile);
			double EnStep = (RangeEnd-RangeStart)/5000.0;
			for (double Energy = RangeStart; Energy < RangeEnd; Energy += EnStep)
			{
				double Flux = hTemp->GetBinContent(hTemp->FindBin(Energy));
				hPoint->Fill(Energy*xdir, Flux*BinNumber/5000.0);	//fix end point
			}

			hPoint->Scale(xdir);		//fix peak
			hPoint->Scale(ydir);		//fix peak
			hTemp->Delete();
		}

		//hTemp->change_ydir
		if (Neutrino)
			hCharmTn->Add(hPoint);
		else 
			hCharmTa->Add(hPoint);
	}

	//tau -> pi tau			this doesnot suffer from helicity suppr, just phase space, maybe a fact of 2
	if (hPoint = sxFlux.Get("Pion"))
	{
		hPoint->Scale(Kine::ShrockFactor(M_Tau, M_Pion, M_Sterile, GetHel()));
		if (Neutrino)
			hPionTn->Add(hPoint);
		else 
			hPionTa->Add(hPoint);
	}

	//tau -> pi pi0 nu_tau
	if (hPoint = sxFlux.Get("2Pion"))
	{
		if (false)	//not implemented
		{
			//double P2 = hTau2Pion->GetBinContent(hTau2Pion->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			//hPoint->Scale(P2);	//Three body
		}
		else if (M_Sterile > M_Tau - M_Pion - M_Pion0)
			hPoint->Scale(0);
		if (Neutrino)
			h2PionTn->Add(hPoint);
		else
			h2PionTa->Add(hPoint);
	}

	//tau -> nu_tau e nu_e
	if (hPoint = sxFlux.Get("TauE"))
	{
		if (Kine)
		{
			double TE = hTauETau->GetBinContent(hTauETau->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			hPoint->Scale(TE);	//Three body
		}
		else if (M_Sterile > M_Tau - M_Electron)
			hPoint->Scale(0);
		if (Neutrino)
			hTauETn->Add(hPoint);
		else
			hTauETa->Add(hPoint);
	}

	//tau -> nu_tau mu nu_mu
	if (hPoint = sxFlux.Get("TauM"))
	{
		if (Kine)
		{
			double TM = hTauMTau->GetBinContent(hTauMTau->FindBin(M_Sterile+1e-9));	//1e-9 to prevent bin error
			hPoint->Scale(TM);	//Three body
		}
		else if (M_Sterile > M_Tau - M_Muon)
			hPoint->Scale(0);
		if (Neutrino)
			hTauMTn->Add(hPoint);
		else
			hTauMTa->Add(hPoint);
	}
}

/*
double FluxDriver::SampleEnergy()		//Sample PDF
{
	return hTotalM->GetRandom();
}
*/

double FluxDriver::GetRangeStart()
{
	return RangeStart;
}

double FluxDriver::GetRangeEnd()
{
	return RangeEnd;
}

int FluxDriver::GetBinNumber()
{
	return BinNumber;
}

double FluxDriver::GetIntensity(double Energy, bool NvA, bool Uu)	//Return flux intensity, given energy, simple linear interpolation
{									//NvA == 1 -> Neutrino, NvA == 0 -> Antineutrino
	double Ue, Um, Ut;						//Uu == 1 -> mixing , Uu == 0 -> maximal (light neutrino)

	if (Uu)
	{
		Ue = GetUe();
		Um = GetUm();
		Ut = GetUt();
	}
	else
	{
		Ue = 1.0;
		Um = 1.0;
		Ut = 1.0;
	}

	TH1D *hTotElec, *hTotMuon, *hTotTau;

	if (NvA)
	{
		hTotElec = hTotalEn;
		hTotMuon = hTotalMn;
		hTotTau  = hTotalTn;
	}
	else
	{
		hTotElec = hTotalEa;
		hTotMuon = hTotalMa;
		hTotTau  = hTotalTa;
	}

	int Bin;
	double I1, I2, E1, E2;

	Bin = hTotElec->FindBin(Energy);
	I1 = hTotElec->GetBinContent(Bin);
	E1 = hTotElec->GetBinCenter(Bin);
	if (Energy < E1)
	{
		I2 = hTotElec->GetBinContent(Bin-1);
		E2 = hTotElec->GetBinCenter(Bin-1);
	}
	else
	{
		I2 = hTotElec->GetBinContent(Bin+1);
		E2 = hTotElec->GetBinCenter(Bin+1);
	}

	double IntElec = (Energy-E1)*(I2-I1)/(E2-E1) + I1;

	Bin = hTotMuon->FindBin(Energy);
	I1 = hTotMuon->GetBinContent(Bin);
	E1 = hTotMuon->GetBinCenter(Bin);
	if (Energy < E1)
	{
		I2 = hTotMuon->GetBinContent(Bin-1);
		E2 = hTotMuon->GetBinCenter(Bin-1);
	}
	else
	{
		I2 = hTotMuon->GetBinContent(Bin+1);
		E2 = hTotMuon->GetBinCenter(Bin+1);
	}

	double IntMuon = (Energy-E1)*(I2-I1)/(E2-E1) + I1;

	Bin = hTotTau->FindBin(Energy);
	I1 = hTotTau->GetBinContent(Bin);
	E1 = hTotTau->GetBinCenter(Bin);
	if (Energy < E1)
	{
		I2 = hTotTau->GetBinContent(Bin-1);
		E2 = hTotTau->GetBinCenter(Bin-1);
	}
	else
	{
		I2 = hTotTau->GetBinContent(Bin+1);
		E2 = hTotTau->GetBinCenter(Bin+1);
	}

	double IntTau = (Energy-E1)*(I2-I1)/(E2-E1) + I1;

	return Ue*Ue*IntElec + Um*Um*IntMuon + Ut*Ut*IntTau;
} 

void FluxDriver::SetBaseline(double Baseline)
{
	hTotalEn->Scale(1.0/(Baseline*Baseline));
	hPionEn->Scale(1.0/(Baseline*Baseline));
	hKaonEn->Scale(1.0/(Baseline*Baseline));
	hKaon0En->Scale(1.0/(Baseline*Baseline));
	hMuonEn->Scale(1.0/(Baseline*Baseline));
	hCharmEn->Scale(1.0/(Baseline*Baseline));

	hTotalEa->Scale(1.0/(Baseline*Baseline));
	hPionEa->Scale(1.0/(Baseline*Baseline));
	hKaonEa->Scale(1.0/(Baseline*Baseline));
	hKaon0Ea->Scale(1.0/(Baseline*Baseline));
	hMuonEa->Scale(1.0/(Baseline*Baseline));
	hCharmEa->Scale(1.0/(Baseline*Baseline));

	hTotalMn->Scale(1.0/(Baseline*Baseline));
	hPionMn->Scale(1.0/(Baseline*Baseline));
	hKaonMn->Scale(1.0/(Baseline*Baseline));
	hKaon0Mn->Scale(1.0/(Baseline*Baseline));
	hMuonMn->Scale(1.0/(Baseline*Baseline));
	hCharmMn->Scale(1.0/(Baseline*Baseline));

	hTotalMa->Scale(1.0/(Baseline*Baseline));
	hPionMa->Scale(1.0/(Baseline*Baseline));
	hKaonMa->Scale(1.0/(Baseline*Baseline));
	hKaon0Ma->Scale(1.0/(Baseline*Baseline));
	hMuonMa->Scale(1.0/(Baseline*Baseline));
	hCharmMa->Scale(1.0/(Baseline*Baseline));

	hTotalTn->Scale(1.0/(Baseline*Baseline));
	hPionTn->Scale(1.0/(Baseline*Baseline));
	h2PionTn->Scale(1.0/(Baseline*Baseline));
	hCharmTn->Scale(1.0/(Baseline*Baseline));
	hTauETn->Scale(1.0/(Baseline*Baseline));
	hTauMTn->Scale(1.0/(Baseline*Baseline));
                 
	hTotalTa->Scale(1.0/(Baseline*Baseline));
	hPionTa->Scale(1.0/(Baseline*Baseline));
	h2PionTa->Scale(1.0/(Baseline*Baseline));
	hCharmTa->Scale(1.0/(Baseline*Baseline));
	hTauETa->Scale(1.0/(Baseline*Baseline));
	hTauMTa->Scale(1.0/(Baseline*Baseline));
}

void FluxDriver::SetPOT(double POT)
{
	hTotalEn->Scale(POT);
	hPionEn->Scale(POT);
	hKaonEn->Scale(POT);
	hKaon0En->Scale(POT);
	hMuonEn->Scale(POT);
	hCharmEn->Scale(POT);

	hTotalEa->Scale(POT);
	hPionEa->Scale(POT);
	hKaonEa->Scale(POT);
	hKaon0Ea->Scale(POT);
	hMuonEa->Scale(POT);
	hCharmEa->Scale(POT);

	hTotalMn->Scale(POT);
	hPionMn->Scale(POT);
	hKaonMn->Scale(POT);
	hKaon0Mn->Scale(POT);
	hMuonMn->Scale(POT);
	hCharmMn->Scale(POT);

	hTotalMa->Scale(POT);
	hPionMa->Scale(POT);
	hKaonMa->Scale(POT);
	hKaon0Ma->Scale(POT);
	hMuonMa->Scale(POT);
	hCharmMa->Scale(POT);

	hTotalTn->Scale(POT);
	hPionTn->Scale(POT);
	h2PionTn->Scale(POT);
	hCharmTn->Scale(POT);
	hTauETn->Scale(POT);
	hTauMTn->Scale(POT);
                 
	hTotalTa->Scale(POT);
	hPionTa->Scale(POT);
	h2PionTa->Scale(POT);
	hCharmTa->Scale(POT);
	hTauETa->Scale(POT);
	hTauMTa->Scale(POT);
}

void FluxDriver::SetArea(double Area)
{
	hTotalEn->Scale(Area);
	hPionEn->Scale(Area);
	hKaonEn->Scale(Area);
	hKaon0En->Scale(Area);
	hMuonEn->Scale(Area);
	hCharmEn->Scale(Area);

	hTotalEa->Scale(Area);
	hPionEa->Scale(Area);
	hKaonEa->Scale(Area);
	hKaon0Ea->Scale(Area);
	hMuonEa->Scale(Area);
	hCharmEa->Scale(Area);

	hTotalMn->Scale(Area);
	hPionMn->Scale(Area);
	hKaonMn->Scale(Area);
	hKaon0Mn->Scale(Area);
	hMuonMn->Scale(Area);
	hCharmMn->Scale(Area);

	hTotalMa->Scale(Area);
	hPionMa->Scale(Area);
	hKaonMa->Scale(Area);
	hKaon0Ma->Scale(Area);
	hMuonMa->Scale(Area);
	hCharmMa->Scale(Area);

	hTotalTn->Scale(Area);
	hPionTn->Scale(Area);
	h2PionTn->Scale(Area);
	hCharmTn->Scale(Area);
	hTauETn->Scale(Area);
	hTauMTn->Scale(Area);
                 
	hTotalTa->Scale(Area);
	hPionTa->Scale(Area);
	h2PionTa->Scale(Area);
	hCharmTa->Scale(Area);
	hTauETa->Scale(Area);
	hTauMTa->Scale(Area);
}


bool FluxDriver::IsChanged(double M_Sterile)
{
	bool Ret = (fabs(M_Sterile - M_Sterile_prev) > 1e-9);
	M_Sterile_prev = M_Sterile;

	return Ret;
}

void FluxDriver::SetUe(double X)
{
	U_e = X;
}

void FluxDriver::SetUm(double X)
{
	U_m = X;
}

void FluxDriver::SetUt(double X)
{
	U_t = X;
}

double FluxDriver::GetUe()
{
	return U_e;
}

double FluxDriver::GetUm()
{
	return U_m;
}

double FluxDriver::GetUt()
{
	return U_t;
}

void FluxDriver::Modify(double &xdir, double &ydir, double M_Sterile)
{
	for (unsigned int i = 0; i < vMdir.size(); ++i)
	{
		if (vMdir.at(i) > M_Sterile || fabs(M_Sterile-vMdir.at(i)) < 1e-9)
		{
			xdir = vXdir.at(i);
			ydir = vYdir.at(i);
			break;
		}
	}
}

void FluxDriver::SetHel(int H)
{
	iH = H;
}

int FluxDriver::GetHel()
{
	return iH;
}
