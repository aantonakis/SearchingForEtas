#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TLegend.h"
#include "TEllipse.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

// Eta Framework includes
#include "EventBuilder.h"
#include "Event.h"
#include "Slice.h"


using namespace ETA;

// Note:: the different topologies are defined in plotter.py--> a python class with many features


int main( int argc, char** argv ) {


	std::string inputFileString;
	std::string outputFileString;
	int iArg = 1;
	while (iArg < argc) {
		std::string argFlag = argv[iArg];
		if (argFlag == "-i") {
			inputFileString = argv[iArg+1];
		}
		else if (argFlag == "-o") {
			outputFileString = argv[iArg+1];
		}
		else {
			std::cout << "Bad Usage !!!" << std::endl;
			return 1;
		}
		iArg += 2;
	}
	
	std::cout << "Let's open the files" << std::endl;

	TFile* inputFile = new TFile(inputFileString.c_str(), "READ");
	TFile* out = new TFile(outputFileString.c_str(), "RECREATE" );

	inputFile->ls(); // print out the input contents 
	

	TTree * out_tree = new TTree("event_tree","event_tree");
	Event* event = nullptr;
	out_tree->Branch("event", &event);
	std::cout << "Just set the output tree branches" << std::endl;

	// Get the input tree and define all the branches we will need to build events
	TTree* input_tree = (TTree*) inputFile->Get("recTree");

	std::cout << "Got the input tree" << std::endl;
	input_tree->Print();  


	// The EventBuilder Class has useful helper functions
	EventBuilder ev;
	ev.SetBranchAddresses(input_tree);

	for (int i = 0, N = input_tree->GetEntries(); i < N; ++i) {
	//for (int i = 0, N = input_tree->GetEntries(); i < 10; ++i) {

		//event->Clear(); // clear the event before filling with new stuff
		
		input_tree->GetEntry(i);
		
		event->Clear(); // clear the event before filling with new stuff
		

		event->SetID(ev.evt_id);
		event->SetRun(ev.run); 
		event->SetSubRun(ev.subrun);
		//event->SetSliceCount(slcLength);

		std::cout << std::endl;
		std::cout << "Event: " << i << std::endl;
		std::cout << "Run: " << ev.run << " SubRun " << ev.subrun << std::endl;		


		// The EventBuilder Class has useful helper functions
		//EventBuilder ev;

		//std::cout << "We initiated the EventBuilder Class" << std::endl;
		std::cout << "starting Slice Loop" << std::endl;
		for (int j = 0; j < ev.slcLength; ++j) {
			

			Slice new_slice;
			new_slice.SetID(j);
			new_slice.SetIsClearCosmic(ev.is_clear_cosmic[j]);
			new_slice.SetNuScore(ev.nu_score[j]);
			new_slice.SetIsCC(ev.iscc[j]);
			new_slice.SetIsNC(ev.isnc[j]);
			new_slice.SetSelf(ev.slc_self[j]);			
			
			float vtx[3] = {ev.vtx_x[j], ev.vtx_y[j], ev.vtx_z[j]};
			
			new_slice.SetTop(ev.what_is_this_slice(j, ev.slc_true_pdg[j], vtx, ev.prim_pdgs, ev.nprim));

			event->AddSlice(new_slice);

   		}
		
		std::cout << "Starting Primary PFP Loop" << std::endl;
		
		for (int k = 0; k < ev.pfp_totalarraysize; ++k) {
			int pfp_slcID_t = ev.pfp_slcID[k];
			//std::cout << "pfp " << k << " pfp_slcID " << pfp_slcID_t << std::endl;
			int pfp_trk_id = ev.pfp_true_shw_G4ID[k];

			int slc_id = ev.FindSlice(pfp_slcID_t, event);	
			int is_prim_pfp;
			if (slc_id != -2) { 
				is_prim_pfp = ev.is_Prim(pfp_trk_id, slc_id, ev.slc_true_prim_length, ev.slc_true_prim_G4ID);
			}

			if (is_prim_pfp) {
				
				PrimaryPFP new_primary_pfp;
				new_primary_pfp.SetID(k);
				event->GetSlice(slc_id)->AddPrimaryPFP(new_primary_pfp);

			}

		}
		std::cout << "Fill out_tree with this event" << std::endl;
		out_tree->Fill();
		std::cout << "About to clear the slices of their Primary pfps" << std::endl;
		for (int s = 0; s < event->GetSliceCount(); ++s) {

			event->GetSlice(s)->Clear();

		}

	}


	std::cout << "Writing." << std::endl;
	// Write to the output file
	out->cd();

	out_tree->Write();	 

	std::cout << "Finished." << std::endl;

	out->Close();
	return 0;
}


