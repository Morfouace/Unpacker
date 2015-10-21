#include "VMEDecoder.h"

using namespace std;

int main()
{
    
    ////////////////////////////////////////////////////////////
    //////////////////////// Run Iutput ////////////////////////
    ////////////////////////////////////////////////////////////
    ifstream inputConfigFile;
    string inputConfigFile_name = "RunToTreat.txt";
    inputConfigFile.open(inputConfigFile_name.c_str());
    string buffer;
    getline(inputConfigFile,buffer);
    
    TString filename = buffer;
    fData.open(filename.Data(), std::ios::in|std::ios::ate|std::ios::binary);
    
    if (!(fData.is_open())) {
        cout << "== [VMEDecoder] VME file open error! File not found!" << endl;
        kOpen = false;
    }
    else{
        fFileSize = fData.tellg();// to get the size of the file
        cout << "== [VMEDecoder] " << filename << " is opened!" << endl;
        fData.seekg(0,fData.beg);// to go back to the position at the begining of the file
        kOpen = true;
    }
    
    ////////////////////////////////////////////////////////////
    /////////////////////// Tree Output ////////////////////////
    ////////////////////////////////////////////////////////////
    string run_number = buffer.substr(11,4).c_str();
    TString file_name = "run-"+run_number+".root";
    //--------------- Tree definition ---------------//
    TFile *file = new TFile(file_name,"RECREATE");
    TTree *Tree = new TTree("Tree","CsI Tree");
    
    // Defining Branch
    TADCData* theADC = new TADCData();
    Tree->Branch("ADC","TADCData", &theADC);
    
    
    
    UInt_t dataBuff = 0;
    ULong_t data = 0;
    int counter = 0;
    
    if(kOpen){
        fData.read(reinterpret_cast<Char_t *>(&dataBuff), 1);
        cout << "== [VMEDecoder] Starting Decoding Data" << endl;
        while(!fData.eof()){
            
        //for(int i=0; i<100; i++){
            fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
            
            if((dataBuff&0XFFFF)==0X004c) {
                theADC->Clear();
                counter++;
                
                //For TDC
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data = dataBuff;
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data += dataBuff<<16;
                geo=(data&0xf8000000)>>27;
                dataType = (data&0x02000000)>>24;
                TDC_NumberOfChannels = (data&0x00003f00)>>8;
                //cout << hex<<setw(8)<<setfill('0') << data << endl;
                //cout << geo << endl;
                //cout << dataType << endl;
                //cout << TDC_NumberOfChannels << endl;
                
                for(int i = 0; i<TDC_NumberOfChannels; i++){
                    fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                    data = dataBuff;
                    fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                    data += dataBuff<<16;
                    
                    geo=(data&0xf8000000)>>27;
                    dataType = (data&0x02000000)>>24;
                    Int_t channel_number = (data&0x001f0000)>>16;
                    Int_t TDC_Value = (data&0x00000fff);
                }
                
                //For End of Block
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data = dataBuff;
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data += dataBuff<<16;
                //cout << hex<<setw(8)<<setfill('0') << data << endl;
                
                //For ADC
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data = dataBuff;
                fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                data += dataBuff<<16;
                geo=(data&0xf8000000)>>27;
                dataType = (data&0x02000000)>>24;
                ADC_NumberOfChannels = (data&0x00003f00)>>8;
                
                for(int i = 0; i<ADC_NumberOfChannels; i++){
                    fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                    data = dataBuff;
                    fData.read(reinterpret_cast<Char_t *>(&dataBuff), 2);
                    data += dataBuff<<16;
                    //cout << hex<<setw(8)<<setfill('0') << data << endl;

                    geo=(data&0xf8000000)>>27;
                    dataType = (data&0x02000000)>>24;
                    channel_number = (data&0x001f0000)>>16;
                    ADC_Value = (data&0x00000fff);
                    
                    theADC->Fill(channel_number,ADC_Value);
                }
                //theADC->Dump();
                Tree->Fill();
            }
        }
    }
    
    cout << "== [VMEDecoder] Decoding Data Done" << endl;
    cout << "== [VMEDecoder] Number of entry found: " << counter << endl;
    
    fData.close();
    file->Write();
    file->Close();
    
    return 0;
}












