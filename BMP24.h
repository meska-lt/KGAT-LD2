#ifndef __BMP24_H_
#define __BMP24_H_

#include <string>
#include <stdio.h>

using namespace std;

class BMP24 {
  public:
  unsigned int failoDydis;
  unsigned int nenaudojamas;
  static const unsigned int vaizdoPradzia = 54;
  static const unsigned int aprasoDydis = 40;
  
  unsigned int plotis;
  unsigned int aukstis;

  static const unsigned int bituPlokstumuSkaicius = 1;
  static const unsigned int bituSkaiciusTaskui = 24;

  static const unsigned int vaizdoSuspaudimoMetodas = 0;

  unsigned int vaizdoDydis;
   
  static const unsigned int rezoliucijaHorizontaliai = 0;
  static const unsigned int rezoliucijaVertikaliai = 0;

  static const unsigned int spalvuSkaiciusRastre = 0;
  static const unsigned int svarbiuSpalvuSkaiciusRastre = 0;

  //---------------------------------
  string bylosPavadinimas;   

  //   Konstruktoriai:
  
  // BMP24();
  BMP24(unsigned int plotis,unsigned int aukstis);
  BMP24(string failas);

  // Destruktoriai:
  
  ~BMP24();



  //   Funkcijos:

  void nuliai();
  void dekTaska(int x,int y, char r,char g,char b);
  unsigned int duokTaskoSpalva(int x,int y, char& r, char& g,char& b);  
  void horizontaliTiese(int xL, int xR, int y, char r,char g,char b);
  unsigned char* eksportuokIGLTekstura(int& plotis,int& aukstis);
  int rasykIByla(string bylosPavadinimas);
  int rasyk();
  void tiese(int xNuo,int yNuo, int xIki, int yIki, char r, char g, char b);
  void bezier2( double* kontTaskai, char r, char g, char b);
  void bezier2Splainas( double* kontTaskai, int nTasku, char r, char g, char b);
  void spalvink(int x,int y,char  rKonturo,char  gKonturo,char  bKonturo,
                                       char  rDazu,char  gDazu,char  bDazu ); 
  void valyk(char  r, char  g ,char  b ); 

  char*  vaizdas;
  unsigned int eilutesIlgis;
  
//
  unsigned char* eksportasIGL; 
  protected:
  int rekursinisLinijinisSpalvinimas( int vidinisX, int vidinisY, 
                                             int kryptis, int buvesXL, int buvesXR, 
                                             char rKonturo,   char gKonturo,   char bKonturo, 
                                             char rDazu,   char gDazu,   char bDazu ) ;
  
     


};


#endif

