#ifndef ETA_PrimaryPFP_H
#define ETA_PrimaryPFP_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TVector3.h>

#include "SecondaryPFP.h"

/*

  Class to store LArsoft event level information and to store all slices for an event


*/

namespace ETA {

class PrimaryPFP : public TObject {
public:
	PrimaryPFP() {}
	~PrimaryPFP() {}
	
	int primaryPFPID = -1;
	
	std::vector<SecondaryPFP> secondary_pfps; // a vector of daughter objects associated with this PFP 	
	
	// Clear the vector members of the Slice
	void Clear();	

	// This is the LArSoft event ID
	void SetID(int _primaryPFPID) {primaryPFPID = _primaryPFPID;}
	int GetID() const {return primaryPFPID;}
	
	
		
	int GetSecondaryPFPCount() const {return secondary_pfps.size();}
	void AddSecondaryPFP(SecondaryPFP secondary_pfp) {return secondary_pfps.push_back(secondary_pfp);}
	SecondaryPFP* GetSecondaryPFP(int i) {return &secondary_pfps[i];}

private:

	//int scliceID = -1;
	//int sliceTop = -1;	

// Required for ROOT I/O with TTree and TFile                                                                                                                                      
ClassDef(PrimaryPFP, 1)   // Class holding LArSoft event information


};


} // end namespace ETA

#endif





