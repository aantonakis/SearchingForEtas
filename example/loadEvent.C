
// Standard Library Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>


// Load the JADE libraries
R__LOAD_LIBRARY(libETA.so)

// We don't want to have to put ETA before everything so
// load the ETA namespace
using namespace ETA;

void loadEvent(const char* filename) {
	std::cout << "We successfully loaded the ETA data structure" << std::endl;

	// Get the Trigger tree from the file
	TFile* inputFile = new TFile(filename, "READ");
	inputFile->ls(); // print out the input contents 
	
	// Get the input tree and define all the branches we will need to build events
	TTree* input_tree = (TTree*) inputFile->Get("event_tree");
	std::cout << "Got the input tree" << std::endl;
	input_tree->Print();  

	Event* event = nullptr;
	input_tree->SetBranchAddress("event", &event);

	int numEvents = input_tree->GetEntries();
	
	for (int iEvent = 0; iEvent < numEvents; ++iEvent) {
		input_tree->GetEntry(iEvent);
		std::cout << "Event " << event->GetID() << " Run " << event->GetRun() << " SubRun " << event->GetSubRun() << std::endl;
		

	}// end of event loop

} // end of macro


