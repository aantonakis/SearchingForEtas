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

	// initialize all of the branch variables
	
	/*
	int run;
	int subrun;
	int evt_id;
	
	int slcLength = 50;
	int *slc_true_pdg = new int[slcLength];
	float *vtx_x = new float[slcLength];
	float *vtx_y = new float[slcLength];
	float *vtx_z = new float[slcLength];
	int nprim_tot = 100;
	int *nprim = new int[slcLength];
	int *prim_pdgs = new int[nprim_tot];
	
	Char_t *is_clear_cosmic = new Char_t[slcLength];
	float *nu_score = new float[slcLength];
	Char_t *iscc = new Char_t[slcLength];
	Char_t *isnc = new Char_t[slcLength];

	std::cout << "About to set the Branch Addresses" << std::endl;
	
	input_tree->SetBranchAddress("rec.hdr.run", &run);
	input_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
	input_tree->SetBranchAddress("rec.hdr.evt", &evt_id);

	input_tree->SetBranchAddress("rec.slc..length", &slcLength);
	input_tree->SetBranchAddress("rec.slc.truth.prim..totarraysize", &nprim_tot);
	input_tree->SetBranchAddress("rec.slc.truth.pdg", slc_true_pdg);
	input_tree->SetBranchAddress("rec.slc.truth.position.x", vtx_x);
	input_tree->SetBranchAddress("rec.slc.truth.position.y", vtx_y);
	input_tree->SetBranchAddress("rec.slc.truth.position.z", vtx_z);
	input_tree->SetBranchAddress("rec.slc.truth.prim.pdg", prim_pdgs);
	input_tree->SetBranchAddress("rec.slc.truth.nprim", nprim);
	
	input_tree->SetBranchAddress("rec.slc.is_clear_cosmic", is_clear_cosmic);
	input_tree->SetBranchAddress("rec.slc.nu_score", nu_score);
	input_tree->SetBranchAddress("rec.slc.truth.iscc", iscc);
	input_tree->SetBranchAddress("rec.slc.truth.isnc", isnc);
	
	std::cout << "SetBranchAddress Successful" << std::endl;
	*/

	// The EventBuilder Class has useful helper functions
	EventBuilder ev;
	ev.SetBranchAddresses(input_tree);

	for (int i = 0, N = input_tree->GetEntries(); i < N; ++i) {
	//for (int i = 0, N = input_tree->GetEntries(); i < 10; ++i) {

		//std::cout << "Event: " << i << std::endl;
		input_tree->GetEntry(i);
		
		event->Clear(); // clear the event before filling with new stuff

		event->SetID(ev.evt_id);
		event->SetRun(ev.run); 
		event->SetSubRun(ev.subrun);
		//event->SetSliceCount(slcLength);

		std::cout << std::endl;
		std::cout << "Event: " << i << std::endl;

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
			
			std::cout << "is_clear_cosmic" << ev.is_clear_cosmic[j] << std::endl;
			
			std::cout << "j " << j << " iscc " << ev.iscc[j] << std::endl;
			//std::cout << "Set iscc " << new_slice.GetIsCC() << std::endl;
			//std::cout << "j " << j << " isnc " << isnc[j] << std::endl;
			//std::cout << "Set isnc " << new_slice.GetIsNC() << std::endl;
			float vtx[3] = {ev.vtx_x[j], ev.vtx_y[j], ev.vtx_z[j]};
			
			new_slice.SetTop(ev.what_is_this_slice(j, ev.slc_true_pdg[j], vtx, ev.prim_pdgs, ev.nprim));

			event->AddSlice(new_slice);

   		}
		
		out_tree->Fill();
	}


	std::cout << "Writing." << std::endl;
	// Write to the output file
	out->cd();

	out_tree->Write();	 

	std::cout << "Finished." << std::endl;

	out->Close();
	return 0;
}


