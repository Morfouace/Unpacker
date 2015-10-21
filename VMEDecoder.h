#include "TSystem.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
//#include <arpa/inet.h>

#include "TADCData.h"

ifstream fData;
ULong64_t fFileSize;
bool kOpen;

Int_t geo;
Int_t dataType;
Int_t ADC_NumberOfChannels;
Int_t TDC_NumberOfChannels;
Int_t channel_number;
Int_t ADC_Value;
Int_t TDC_Value;



