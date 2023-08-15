#ifndef ETA_SecondaryPFP_H
#define ETA_SecondaryPFP_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TVector3.h>


/*

  Class to store LArsoft event level information and to store all slices for an event


*/

namespace ETA {

class SecondaryPFP : public TObject {
public:
	SecondaryPFP() {}
	~SecondaryPFP() {}
	
	int secondaryPFPID = -1;
	

	// This is the LArSoft event ID
	void SetID(int _secondaryPFPID) {secondaryPFPID = _secondaryPFPID;}
	int GetID() const {return secondaryPFPID;}
		

private:

	//int scliceID = -1;
	//int sliceTop = -1;	

// Required for ROOT I/O with TTree and TFile                                                                                                                                      
ClassDef(SecondaryPFP, 1)   // Class holding LArSoft event information


};


} // end namespace ETA

#endif





