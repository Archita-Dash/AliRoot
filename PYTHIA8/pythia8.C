R__LOAD_LIBRARY(libpythia8243)
R__LOAD_LIBRARY(libAliPythia8)
AliGenerator*  CreateGenerator();

void pythia8(Int_t nev = 1, const char* filename = "galice.root")
{
    gSystem->Setenv("PYTHIA8DATA", gSystem->ExpandPathName("$ALICE_ROOT/PYTHIA8/pythia8243/xmldoc"));
    gSystem->Setenv("LHAPDF",      gSystem->ExpandPathName("$ALICE_ROOT/LHAPDF"));
    gSystem->Setenv("LHAPATH",     gSystem->ExpandPathName("$ALICE_ROOT/LHAPDF/PDFsets"));

//  Runloader
    AliRunLoader* rl = AliRunLoader::Open("galice.root","FASTRUN","recreate");
    
    rl->SetCompressionLevel(2);
    rl->SetNumberOfEventsPerFile(10000);
    rl->LoadKinematics("RECREATE");
    rl->MakeTree("E");
    gAlice->SetRunLoader(rl);

//  Create stack
    rl->MakeStack();
    AliStack* stack      = rl->Stack();
 
//  Header
    AliHeader* header = rl->GetHeader();
//
//  Create and Initialize Generator
    AliGenerator *gener = CreateGenerator();
    gener->Init();
    (AliPythia8::Instance())->PrintDecayTable();
    gener->SetStack(stack);
    
//
//                        Event Loop
//
    Int_t iev;
     
    for (iev = 0; iev < nev; iev++) {

	printf("\n \n Event number %d \n \n", iev);
	
//  Initialize event
	header->Reset(0,iev);
	rl->SetEventNumber(iev);
	stack->Reset();
	rl->MakeTree("K");
//	stack->ConnectTree();
    
//  Generate event
	gener->Generate();
//  Analysis
	Int_t npart = stack->GetNprimary();
	printf("Analyse %d Particles\n", npart);
	for (Int_t part=0; part<npart; part++) {
	    TParticle *MPart = stack->Particle(part);
	    Int_t mpart  = MPart->GetPdgCode();
//	    printf("Particle %d\n", mpart);
	}
	
//  Finish event
	header->SetNprimary(stack->GetNprimary());
	header->SetNtrack(stack->GetNtrack());  
//      I/O
//	
	stack->FinishEvent();
	header->SetStack(stack);
	rl->TreeE()->Fill();
	rl->WriteKinematics("OVERWRITE");

    } // event loop
//
//                         Termination
//  Generator
    gener->FinishRun();
//  Write file
    rl->WriteHeader("OVERWRITE");
    gener->Write();
    rl->Write();
    
}


AliGenerator*  CreateGenerator()
{
    AliGenPythiaPlus* gener = new AliGenPythiaPlus(AliPythia8::Instance());

//
//
    gener->SetProcess(kPyCharmppMNRwmi);
    gener->SetForceDecay(kHadronicDWithout4Bodies);
//   Centre of mass energy 
    gener->SetEnergyCMS(7000.);
//   Initialize generator    
    gener->SetEventListRange(-1, 10);
    return gener;
}








