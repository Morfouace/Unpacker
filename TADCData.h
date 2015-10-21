#ifndef __TADCCDATA__
#define __TADCCDATA__

#include <vector>
#include "TObject.h"

using namespace std ;

class TADCData : public TObject {
 private:
   // ADC
   vector<UShort_t>  fADC_Channel;
   vector<UShort_t>  fADC_Value;
    
 public:
   TADCData();
   virtual ~TADCData();

   void   Clear();
   void   Clear(const Option_t*) {};
   void   Dump() const;

    /////////////////////           GETTERS           ////////////////////////
    int GetChannel(int i) { return fADC_Channel[i] ;}
    int GetValue(int i) { return fADC_Value[i] ;}
   
    /////////////////////           SETTERS           ////////////////////////
    void SetChannel(int channel) { fADC_Channel.push_back(channel) ;}
    void SetValue(int val) { fADC_Value.push_back(val) ;}
    void Fill(int channel, int val) {SetChannel(channel); SetValue(val); }
    
   //
   ClassDef(TADCData,1)  // TADCData structure
};
#endif
