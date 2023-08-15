#ifndef ETA_EVENT_H
#define ETA_EVENT_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TVector3.h>

#include "Slice.h"


/*

  Class to store LArsoft event level information and to store all slices for an event


*/

namespace ETA {


class Event : public TObject {
public:
	Event() {}
	~Event() {}
	
	int eventID = -1;
	int runID = -1;
	int subRunID = -1;
	
	std::vector<Slice> slices; // a vector of slice objects associated with this event	
	
	// Clear the vector members of the Event
	void Clear();	

	// This is the LArSoft event ID
	void SetID(int _eventID) {eventID = _eventID;}
	int GetID() const {return eventID;}
	
	// Run # for this event
	void SetRun(int _runID) {runID = _runID;}
	int GetRun() const {return runID;}
	
	// Sub Run # for this event
	void SetSubRun(int _subRunID) {subRunID = _subRunID;}
	int GetSubRun() const {return subRunID;}
	
	int GetSliceCount() const {return slices.size();}
	void AddSlice(Slice slice) {return slices.push_back(slice);}
	Slice* GetSlice(int i) {return &slices[i];}


private:

	//int eventID = -1;
	//int runID = -1;
	//int subRunID = -1;
	
	//std::vector<Slice> slices; // a vector of slice objects associated with this event	
	

// Required for ROOT I/O with TTree and TFile                                                                                                                                      
ClassDef(Event, 1)   // Class holding LArSoft event information


};

} // end namespace ETA

#endif





