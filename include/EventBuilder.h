#ifndef ETA_EVENT_BUILDER_H
#define ETA_EVENT_BUILDER_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TTree.h>

namespace ETA {

//class EventBuilder: public TObject {
class EventBuilder : public TObject {

public:
	EventBuilder() {}
	~EventBuilder() {}

	// Branch Variables to be read from CAF files
	
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


	// Clear out the data members in the EventBuilder; typically done each
	// trigger to prevent the vector members from growing each trigger
	//void Clear();

	void SetBranchAddresses(TTree *_tree);

	// Function to determine if a true slice vertex is in the TPC volume 
	int is_TPC(float vtx_x, float vtx_y, float vtx_z);


	// Determine the topology of a slice
	int what_is_this_slice(int slc_ind, int slc_true_pdg, float vtx[3], int prim_pdgs[], int nprim[]);



private:
	// Branch Variables to be read from CAF files
	//int run;
	//int subrun;
	//int evt_id;

	//int slcLength = 50;
	//int *slc_true_pdg = new int[slcLength];
	//float *vtx_x = new float[slcLength];
	//float *vtx_y = new float[slcLength];
	//float *vtx_z = new float[slcLength];
	//int nprim_tot = 100;
	//int *nprim = new int[slcLength];
	//int *prim_pdgs = new int[nprim_tot];
	
	//Char_t *is_clear_cosmic = new Char_t[slcLength];
	//float *nu_score = new float[slcLength];
	//Char_t *iscc = new Char_t[slcLength];
	//Char_t *isnc = new Char_t[slcLength];

// Required for ROOT I/O with TTree and TFile                                                                                                                                      
ClassDef(EventBuilder, 1)   // Class holding the event building information

};


} // end of namespace ETA

#endif





