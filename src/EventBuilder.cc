
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

#include "EventBuilder.h"

namespace ETA {

void EventBuilder::SetBranchAddresses(TTree *_tree) {
	
	_tree->SetBranchAddress("rec.hdr.run", &run);
	_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
	_tree->SetBranchAddress("rec.hdr.evt", &evt_id);

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
			std::cout << "p in top func: " << p << std::endl;
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

