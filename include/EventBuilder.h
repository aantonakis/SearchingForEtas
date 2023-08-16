#ifndef ETA_EVENT_BUILDER_H
#define ETA_EVENT_BUILDER_H

// Standard Library Includes
#include <iostream>

// ROOT Includes
#include <TObject.h>
#include <TTree.h>
#include "Event.h"

namespace ETA {

//class EventBuilder: public TObject {
class EventBuilder : public TObject {

public:
	EventBuilder() {}
	~EventBuilder() {}

	// Branch Variables to be read from CAF files
	

	// Event level attributes
	UInt_t run;
	UInt_t subrun;
	UInt_t evt_id;


	// Slice level attributes
	int slcLength = 100;
	int *slc_true_pdg = new int[slcLength];
	float *vtx_x = new float[slcLength];
	float *vtx_y = new float[slcLength];
	float *vtx_z = new float[slcLength];
	int nprim_tot = 500;
	int *nprim = new int[slcLength];
	int *prim_pdgs = new int[nprim_tot];
	
	Char_t *is_clear_cosmic = new Char_t[slcLength];
	float *nu_score = new float[slcLength];
	Char_t *iscc = new Char_t[slcLength];
	Char_t *isnc = new Char_t[slcLength];


	int *slc_self = new int[slcLength];
	int *slc_true_prim_length = new int[slcLength];
	int *slc_true_prim_G4ID = new int[nprim_tot];
	int *pfp_slcID = new int[slcLength];
	
	int pfp_totalarraysize = 1000; // TODO Not sure if this is good ?

	// pfp info
	float *trkScore = new float[pfp_totalarraysize];
	float *photonScore = new float[pfp_totalarraysize];
	float *electronScore = new float[pfp_totalarraysize];
	float *bestScore = new float[pfp_totalarraysize];
	
	// reco shw info
	float *pfp_shw_start_x = new float[pfp_totalarraysize];
	float *pfp_shw_start_y = new float[pfp_totalarraysize];
	float *pfp_shw_start_z = new float[pfp_totalarraysize];
	
	float *pfp_shw_dir_x = new float[pfp_totalarraysize];
	float *pfp_shw_dir_y = new float[pfp_totalarraysize];
	float *pfp_shw_dir_z = new float[pfp_totalarraysize];
	
	float *pfp_shw_conv_gap = new float[pfp_totalarraysize];
	float *pfp_shw_bestplane_energy = new float[pfp_totalarraysize];
	float *pfp_shw_bestplane_dEdx = new float[pfp_totalarraysize];


	// True shw info
	int *pfp_true_shw_pdg = new int[pfp_totalarraysize];
	int *pfp_true_shw_G4ID = new int[pfp_totalarraysize];
	int *pfp_true_shw_genE = new int[pfp_totalarraysize];
	float *pfp_true_shw_start_x = new float[pfp_totalarraysize];
	float *pfp_true_shw_start_y = new float[pfp_totalarraysize];
	float *pfp_true_shw_start_z = new float[pfp_totalarraysize];

	float *pfp_true_shw_end_x = new float[pfp_totalarraysize];
	float *pfp_true_shw_end_y = new float[pfp_totalarraysize];
	float *pfp_true_shw_end_z = new float[pfp_totalarraysize];

	// PFP level attributes


	// Clear out the data members in the EventBuilder; typically done each
	// trigger to prevent the vector members from growing each trigger
	//void Clear();

	void SetBranchAddresses(TTree *_tree);

	// Function to determine if a pfp is truly primary
	int is_Prim(int pfp_trk_id, int slc_id, int slc_true_prim_len[], int slc_true_prim_G4IDs[]);

	int FindSlice(int pfp_slcID_t,  Event *event);

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





