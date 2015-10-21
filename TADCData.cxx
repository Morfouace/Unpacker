
#include <iostream>
#include "TADCData.h"


ClassImp(TADCData)

TADCData::TADCData()
{
}


TADCData::~TADCData()
{
}



void TADCData::Clear()
{
    fADC_Channel.clear();
    fADC_Value.clear();
}



void TADCData::Dump() const
{
   cout << "XXXXXXXXXXXXXXXXXXXXXXXX New Event XXXXXXXXXXXXXXXXX" << endl;

   for(unsigned short i = 0 ; i<fADC_Channel.size() ; i++)
      {
         cout << "ADC channel: " << fADC_Channel[i]  << " | Value: "<< fADC_Value[i] << endl;
      
      }
}

