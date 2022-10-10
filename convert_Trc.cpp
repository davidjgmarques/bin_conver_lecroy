// c++ -O3 convert_Trc.cpp -o oscilloscope_binary_conv.out `root-config --glibs --cflags`
// ./oscilloscope_binary_conv.out     

#include "lecroyparser.hpp"
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TLine.h"
#include "TROOT.h"
#include "TKey.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TTree.h"

using namespace std;

int main() {

	TApplication *myapp=new TApplication("myapp",0,0);


    lecroyparser::lecroy_wavedesc_2_3 header;
    int16_t* waveform = nullptr;
    bool res = lecroyparser::read("./data/test_run_pmt_zoom--3rd--300V_cm--00000.trc", header, waveform);

    vector <double> pmt_wf;
    vector <double> pmt_time;

    double x_offset = header.horiz_offset;
    double x_interval = header.horiz_interval;
    double y_gain = header.vertical_gain;
    double y_offset = header.vertical_offset;




    if(res && waveform) {

        for(long int i = 0; i < header.wave_array_count; ++i) {

            pmt_wf.push_back(waveform[i]*y_gain - y_offset);
            pmt_time.push_back(x_offset + x_interval*i );
        }

        delete[] waveform;
    }

    TGraph *gWaveform = new TGraph();

    for (int k = 0; k < pmt_wf.size(); k++){

        gWaveform -> SetPoint ( k, pmt_time[k], pmt_wf[k]);
    }







    TCanvas *c1 = new TCanvas("","", 800, 400);
    c1->cd();
    gWaveform->SetLineColor(kAzure-5);
    gWaveform->SetLineWidth(1);
    gWaveform->SetFillStyle(3003);
    gWaveform->SetFillColor(kAzure+5);
    gWaveform->GetYaxis()->SetTitleOffset(1.0);
    gWaveform->GetYaxis()->SetTitleSize(0.045);
    gWaveform->GetXaxis()->SetTitleOffset(1.0);
    gWaveform->GetXaxis()->SetTitleSize(0.045);
    gWaveform->Draw();

    myapp->Run();
    return 0;
}
