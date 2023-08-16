
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

#include "Event.h"
#include "EventBuilder.h"

namespace ETA {

void EventBuilder::SetBranchAddresses(TTree *_tree) {
	
	// Event level Branches	
	_tree->SetBranchAddress("rec.hdr.run", &run);
	_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
	_tree->SetBranchAddress("rec.hdr.evt", &evt_id);


	// Slice level Branches
	_tree->SetBranchAddress("rec.slc..length", &slcLength);
	_tree->SetBranchAddress("rec.slc.truth.prim..totarraysize", &nprim_tot);
	_tree->SetBranchAddress("rec.slc.truth.pdg", slc_true_pdg);
	_tree->SetBranchAddress("rec.slc.truth.position.x", vtx_x);
	_tree->SetBranchAddress("rec.slc.truth.position.y", vtx_y);
	_tree->SetBranchAddress("rec.slc.truth.position.z", vtx_z);
	_tree->SetBranchAddress("rec.slc.truth.prim.pdg", prim_pdgs);
	_tree->SetBranchAddress("rec.slc.truth.nprim", nprim);
	
	_tree->SetBranchAddress("rec.slc.is_clear_cosmic", is_clear_cosmic);
	_tree->SetBranchAddress("rec.slc.nu_score", nu_score);
	_tree->SetBranchAddress("rec.slc.truth.iscc", iscc);
	_tree->SetBranchAddress("rec.slc.truth.isnc", isnc);
	
	// Slice level stuff useful for particle heirarchy
	_tree->SetBranchAddress("rec.slc.self", slc_self);
	_tree->SetBranchAddress("rec.slc.truth.prim..length", slc_true_prim_length); // the number of primaries in a given slice
	_tree->SetBranchAddress("rec.slc.truth.prim.G4ID", slc_true_prim_G4ID);
	

	// PFP level branches
	_tree->SetBranchAddress("rec.slc.reco.pfp..totalarraysize", &pfp_totalarraysize);
	_tree->SetBranchAddress("rec.slc.reco.pfp.slcID", pfp_slcID); // slice ID to which the pfp belongs

	// The main reco shw variables
	_tree->SetBranchAddress("rec.slc.reco.pfp.trackScore", trkScore);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.razzle.photonScore", photonScore);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.razzle.electronScore", photonScore);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.razzle.bestScore", bestScore);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.start.x", pfp_shw_start_x);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.start.y", pfp_shw_start_y);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.start.z", pfp_shw_start_z);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.dir.x", pfp_shw_dir_x);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.dir.y", pfp_shw_dir_y);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.dir.z", pfp_shw_dir_z);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.conversion_gap", pfp_shw_conv_gap);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.bestplane_energy", pfp_shw_bestplane_energy);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.bestplane_dEdx", pfp_shw_bestplane_dEdx);
	
	
	// The main true shw variables
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.pdg", pfp_true_shw_pdg);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.G4ID", pfp_true_shw_G4ID);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.genE", pfp_true_shw_genE);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.start.x", pfp_true_shw_start_x);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.start.y", pfp_true_shw_start_y);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.start.z", pfp_true_shw_start_z);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.end.x", pfp_true_shw_end_x);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.end.y", pfp_true_shw_end_y);
	_tree->SetBranchAddress("rec.slc.reco.pfp.shw.truth.p.end.z", pfp_true_shw_end_z);



}

int EventBuilder::is_Prim(int pfp_trk_id, int slc_id, int slc_true_prim_len[], int slc_true_prim_G4IDs[]) {

	int is_prim = 0;
	int start_ind = 0;
	for (int j = 0; j < slc_id; ++j) {
		start_ind += slc_true_prim_len[j];
	}
	int k;
	for (k = start_ind; k < start_ind + slc_true_prim_len[slc_id]; ++k) {

		if (pfp_trk_id == slc_true_prim_G4IDs[k]) {
			is_prim = 1;
		}

	}
	
	return is_prim;

}


int EventBuilder::FindSlice(int pfp_slcID_t,  Event *event) {
	int slice_ind = -2; // dummy value
	//std::cout << "number of slices to compare " << event->GetSliceCount() << std::endl;
	for (int i = 0; i < event->GetSliceCount(); ++i) {
		int self_id = event->GetSlice(i)->GetSelf();
		//std::cout << "self_id for this slice " << self_id << std::endl;
		if (self_id == pfp_slcID_t) {
			
			return i;
		
		}
		
	}
	//std::cout << "Problem? Can't find slice for this pfp: " << "pfp_slcID = " << pfp_slcID_t <<std::endl;
	return slice_ind;
}



int EventBuilder::is_TPC(float vtx_x, float vtx_y, float vtx_z) {
	// TPC volume dimensions in cm
	int TPC_minX = -200;
	int TPC_maxX = 200;
	int TPC_minY = -200;
	int TPC_maxY = 200;
	int TPC_minZ = 0;
	int TPC_maxZ = 500;

	if ( (TPC_minX < vtx_x < TPC_maxX) && (TPC_minY < vtx_y < TPC_maxY) && (TPC_minZ < vtx_z < TPC_maxZ) ) {

		return 1;
	}	
	return 0;
}



int EventBuilder::what_is_this_slice(int slc_ind, int slc_true_pdg, float vtx[3], int prim_pdgs[], int nprim[]) {
	

	std::cout << "nprim: " << nprim[slc_ind] << std::endl;
	if (slc_true_pdg == -1) {
		// We have a Cosmic
		std::cout << "We have a cosmic" << std::endl;
		return 6;	
	}
	if (abs(slc_true_pdg) == 14 || abs(slc_true_pdg) == 12) {
		// We have a neutrino thing
		if (is_TPC(vtx[0], vtx[1], vtx[2]) == 0) {
			return 1; // neutrino event outside the TPC volume
		} 
		int prim_start = 0;
		//int primLength = sizeof(prim_pdgs) / sizeof(int);
		for (int s = 0; s < slc_ind; ++s) {
      			prim_start += nprim[s];
   		}
		int prim_end = prim_start + nprim[slc_ind];

		std::cout << "prim_start: " << prim_start << " prim_end" << prim_end << std::endl;
		
		int npi0 = 0;
		int eta = 0;
		int ngamma = 0;
		int p;

		for (p = prim_start; p < prim_end; ++p) {
			//std::cout << "p in top func: " << p << std::endl;
			if (prim_pdgs[p] == 111) {
				npi0 += 1;
			}
			if (prim_pdgs[p] == 221) {
				eta = 1;
			}
			if (prim_pdgs[p] == 22) {
				ngamma += 1;			
				
			}
	
		}
		// TODO No way this is the problem ?
		prim_start = 0;
		prim_end = 0;		

		if ( (npi0 == 0) && eta && (slc_true_pdg == 14) && (ngamma >= 2) ) {
			// This is the MicroBooNE signal topology
			return 5;
		}

		if ( eta && npi0 > 0) {
			// this is the eta other topology
			return 0;
		}

		if (npi0 == 1 && eta == 0) {
			return 3;
		}

		if (npi0 >= 2 && eta == 0) {
			return 4; 
		}
		if (npi0 == 0 && eta ==0) {
			return 2;
		}
		else {
			// not a topology we are currently tracking
			return -1;
		}

	}
	else {
		// not a topology we are currently tracking
		return -1;
	}

}

} // end namespace ETA

