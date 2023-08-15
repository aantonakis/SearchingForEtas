#ifndef ETA_Slice_H
#define ETA_Slice_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TVector3.h>


#include "PrimaryPFP.h"

/*

  Class to store LArsoft event level information and to store all slices for an event


*/

namespace ETA {

class Slice : public TObject {
public:
	Slice() {}
	~Slice() {}
	
	int sliceID = -1;
	int sliceTop = -1;	
	Char_t is_clear_cosmic = -128;
	float nu_score = -5.0;	
	Char_t iscc = -128;
	Char_t isnc = -128;
	
	std::vector<PrimaryPFP> primary_pfps; // a vector of slice objects associated with this event	
	
	// Clear the vector members of the Slice
	void Clear();	

	// This is the LArSoft event ID
	void SetID(int _sliceID) {sliceID = _sliceID;}
	int GetID() const {return sliceID;}
	
	// The Slice Topology
	void SetTop(int _sliceTop) {sliceTop = _sliceTop;}
	int GetTop() const {return sliceTop;}
		
	void SetIsClearCosmic(Char_t _is_clear_cosmic) {is_clear_cosmic = _is_clear_cosmic;}
	Char_t GetIsClearCosmic() const {return is_clear_cosmic;}

	void SetNuScore(float _nu_score) {nu_score = _nu_score;}
	float GetNuScore() const {return nu_score;}
	
	void SetIsCC(Char_t _iscc) {iscc = _iscc;}
	Char_t GetIsCC() const {return iscc;}
	
	void SetIsNC(Char_t _isnc) {isnc = _isnc;}
	Char_t GetIsNC() const {return isnc;}
		
	int GetPrimaryPFPCount() const {return primary_pfps.size();}
	void AddPrimaryPFP(PrimaryPFP primary_pfp) {return primary_pfps.push_back(primary_pfp);}
	PrimaryPFP* GetPrimaryPFP(int i) {return &primary_pfps[i];}

private:

	//int scliceID = -1;
	//int sliceTop = -1;	

// Required for ROOT I/O with TTree and TFile                                                                                                                                      
ClassDef(Slice, 1)   // Class holding LArSoft event information


};


} // end namespace ETA

#endif





