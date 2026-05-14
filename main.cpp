#include <fstream>
#include <iostream>
#include "include/Channel Interface/ChannelInterfaceTransmitter.h"
#include "include/Encoding/RSencoder.h"
#include "include/Decoding/Syndrome.h"
#include "vector"
#include "include/Channel Interface/ChannelInterfaceReceiver.h"
#include "include/Decoding/KeyequationEEA.h"
#include "include/Decoding/Chiensearch.h"
#include "include/Decoding/RSdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Decoding/RSFEDdecoder.h"
#include "include/Decoding/RSFECdecoder.h"
#include "include/Encoding/RSencoderInterface.h"
#include "include/Channel Interface/ChannelInterfaceReceiver.h"
#include "include/DecoderInterface/RSdecoderInterface.h"
#include "include/DecoderInterface/RSFECdecoderInterface.h"
#include "include/DecoderInterface/RSFEDdecoderInterface.h"
#include <random>
#include <chrono>
#include <unordered_set>


int main() {
 vector<int>mess(1028,1);
 Generatorpolynomial gp({1,575,552,187,230,552,1,108,565,282,249,593,132,94,720,495,385,942,503,883,361,788,610,193,392,127,185,158,128,834,523 }, 10, 544, 514);

 RSencoderInterface RSEI(10,544,514,mess,gp);
 EncodedMessage encMsg=RSEI.Getencodedmessage();
 string filename="bitstream.txt";
   string filenamer="errorsDB.txt";
 std::cout<<endl;
 ChannelInterfaceTransmitter cit(10,544,514);
  cit.Transmit(encMsg,filename);
 ChannelInterfaceReceiver cir(10,544,514);
 EncodedMessage re1=cir.Receive(filenamer);
 cout<<endl<<" the received code word is "<<endl;
 for(int i=0;i<re1.GetcodewordVector().size();i++) {
  cout<<re1.GetcodewordVector()[i]<<" , ";
 }
 cout<<endl;
 RSdecoderInterface rsdecoder(10,544,514,re1);
 cout<<"The decoded message without error detection or correction is"<<endl;
 vector<int>m1=rsdecoder.Getmessage();
 for(int i=0;i<m1.size();i++) {
  cout<<m1.at(i)<<" , ";
 }
 RSFECdecoderInterface rsfecdecoder(10,544,514,re1);
 cout<<endl<<"The decoded message with error detection and correction is "<<endl;
 vector<int>m2=rsfecdecoder.Getmessage();
 for(int i=0;i<m2.size();i++) {
  cout<<m2.at(i)<<" , ";
 }
 RSFEDdecoderInterface rsfeddecoder(10,544,514,re1);
 cout<<endl<<"The error locations are "<<endl;
 vector<string>m3=rsfeddecoder.Geterrorlocations();
 for(int i=0;i<m3.size();i++) {
  cout<<m3[i]<<" , ";
 }
}