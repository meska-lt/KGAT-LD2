#include "BMP24.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>


using namespace std;


     void BMP24::nuliai(){
         this->vaizdas = NULL;
         this->eksportasIGL = NULL;
     }

     BMP24::BMP24(unsigned int plotis, unsigned int aukstis){
           nuliai();
           this->eilutesIlgis =  plotis * 3;
           if ( this->eilutesIlgis % 4 != 0 )  this->eilutesIlgis +=  (4 - this->eilutesIlgis % 4);            
           this->plotis = plotis;
           this->aukstis = aukstis;  
           this->vaizdoDydis = aukstis *  this -> eilutesIlgis;  
           this->failoDydis = this->vaizdoDydis + this->vaizdoPradzia; 
           this->vaizdas = (char*) new char[this->vaizdoDydis];
           memset((void*)  vaizdas, '\0',  this->vaizdoDydis ); 

      }
//   ---------------------------------------------------------------------------
     BMP24::BMP24(string failas){
           //
     int sk;
     bylosPavadinimas = failas;
     nuliai();

     FILE* fin=fopen(this->bylosPavadinimas.c_str(),"rb");
     if (fin==NULL) {cout << "Blogas failo vardas"; return ; }

     // Signatura BM:
     char  signat[2]; 
     fread(&signat, 2,1,fin);
  
     fread( &sk,4,1,fin);   
     this->failoDydis=sk;
  
     // Praleidziame 4 baitus;
     fread( &sk,4,1,fin);
     //------------------------------
     fread( &sk,4,1,fin);
   //  this->vaizdoPradzia = sk;    
    
     fread( &sk,4,1,fin);
//     this->aprasoDydis = sk;    



     fread( &(this->plotis),4,1,fin);
     fread( &(this->aukstis),4,1,fin);
     //---------------------------------------------
     sk=0;
     fread( &sk, 2 ,1,fin); // 2 baitu
//     this->bituPlokstumuSkaicius = sk;

     sk=0;
     fread( &sk,2 ,1,fin); // 2 baitu laukas
//     this->bituSkaiciusTaskui=sk;

     fread( &sk,4,1,fin);
//     this->vaizdoSuspaudimoMetodas=sk;

     fread( &sk,4,1,fin);
     this->vaizdoDydis=sk;  

     fread( &sk,4,1,fin);
//     this->rezoliucijaHorizontaliai=sk; 

     fread( &sk,4,1,fin);
//     this->rezoliucijaVertikaliai=sk;  
     

     fread( &sk,4,1,fin);
//     this->spalvuSkaiciusRastre = sk;
    
     fread( &sk,4,1,fin);
//     this->svarbiuSpalvuSkaiciusRastre=sk; 

     this->vaizdas = (char*) new char[this->vaizdoDydis];
     memset((void*)  vaizdas, '\0',  this->vaizdoDydis );      

     fread( this->vaizdas,this->vaizdoDydis,1,fin);


     this->eilutesIlgis =  plotis * 3;
     if ( this->eilutesIlgis % 4 != 0 )  this->eilutesIlgis +=  (4 - this->eilutesIlgis % 4); 
  
     fclose(fin); 
  



      }

   //  Metodai:

   void BMP24::dekTaska(int x,int y, char r,char g,char b){
     if((x<0)||(x>plotis)||(y<0)||(y>aukstis)) {
                    cerr << "BMP24::dekTaska klaida : Blogai nurodytos tasko koordinates \n"; 
                    return;
          }
        

         int xX = x;// % plotis;
         int  yY = y;// % aukstis;
         unsigned int vieta =  xX * 3 + this -> eilutesIlgis  * yY;  
        this->vaizdas[ vieta ] = b;
         this->vaizdas[ vieta + 1] = g;
         this->vaizdas[ vieta + 2] = r;
   }
   void BMP24::horizontaliTiese(int xL, int xR, int y, char r,char g,char b){
         if((xL<0)||(xL>plotis)||(y<0)||(y>aukstis)||(xR<0)||(xR>plotis)) {
                    cerr << "Blogai nurodytos tasko koordinates \n"; 
                    return;
          }
         int xXL = xL;
         int xXR = xR;

         int  yY = y;// % aukstis;
       for(int xX = xXL;  xX <= xXR;  xX++){
            unsigned int vieta =  xX * 3 + this -> eilutesIlgis  * yY;  
            this->vaizdas[ vieta ] = b;
            this->vaizdas[ vieta + 1] = g;
            this->vaizdas[ vieta + 2] = r;
      }
   }


  unsigned int BMP24::duokTaskoSpalva(int x,int y, char& r, char& g,char& b){
     if((x<0)||(x>plotis)||(y<0)||(y>aukstis)) {
                    cerr << "BMP24::duokTaskoSpalva klaida : Blogai nurodytos tasko koordinates \n"; 
                    return 0;
          }


        int xX = x;// % plotis;
        int  yY = y;// % aukstis;
        unsigned int vieta =  xX * 3 + this -> eilutesIlgis  * yY;  
        unsigned int spalva=0;
        b = this->vaizdas[ vieta ];
        g = this->vaizdas[ vieta + 1];
        r = this->vaizdas[ vieta + 2] ;
        spalva = (int)r + (int) g << 8 + (int)  b << 16;
        return spalva;
   }




   int  BMP24::rasyk(){
     FILE* fout=fopen(this->bylosPavadinimas.c_str(),"wb");
     // Signatura BM:
     fwrite("BM",2,1,fout);

     fwrite( &(this->failoDydis),4,1,fout);
     int sk=0;
     fwrite( &sk,4,1,fout);
     sk = this->vaizdoPradzia;    

     fwrite( &sk,4,1,fout);

     sk = this->aprasoDydis;    

     fwrite( &sk,4,1,fout);


     fwrite( &(this->plotis),4,1,fout);
     fwrite( &(this->aukstis),4,1,fout);
     sk = this->bituPlokstumuSkaicius;
     fwrite( &sk, 2 ,1,fout); // 2 baitu
     sk=this->bituSkaiciusTaskui;
     fwrite( &sk,2 ,1,fout); // 2 baitu laukas
     sk=this->vaizdoSuspaudimoMetodas;
     fwrite( &sk,4,1,fout);
     sk=this->vaizdoDydis;  
     fwrite( &sk,4,1,fout);
     sk=this->rezoliucijaHorizontaliai; 
     fwrite( &sk,4,1,fout);
     sk=this->rezoliucijaVertikaliai;  
     fwrite( &sk,4,1,fout);
     sk=this->spalvuSkaiciusRastre;
     fwrite( &sk,4,1,fout);
     sk=this->svarbiuSpalvuSkaiciusRastre; 
     fwrite( &sk,4,1,fout);


     fwrite( this->vaizdas,this->vaizdoDydis,1,fout);

  
     fclose(fout); 
     return 1;

   }  

   int  BMP24::rasykIByla(string bylosPavadinimas){

         this->bylosPavadinimas =    bylosPavadinimas;

         this->rasyk();  
         return 1; 
  
   }

    unsigned char* BMP24::eksportuokIGLTekstura(int& plot,int& aukst){
         if((this->aukstis==0)||(this->plotis==0)) return NULL;
         plot=0;aukst=0;
         for(int i=plotis;i>=2;i/=2) plot++;
         for(int i=aukstis;i>=2;i/=2) aukst++;
         plot= (1 << plot);
         aukst= (1 << aukst);
              cout << plot << " " << aukst << "\n";
         if(eksportasIGL!=NULL) { cout << "Deleting \n"; delete[] eksportasIGL;}
         eksportasIGL = new unsigned char[plot*aukst*3]; 

         cout << " Dydis eksporto yra" << sizeof(eksportasIGL) << "\n";


         if(eksportasIGL == NULL) {
           cout << "Out of memory \n";
           return NULL;
         }
         memset( eksportasIGL, '\0', plot*aukst*3); 
         for(int x=0;x<plot;x++)
          for(int y=0;y<aukst;y++)
           {
            char r,g,b;
            int v=(y*plot+x)*3;
            this->duokTaskoSpalva(x,y,r,g,b);
            eksportasIGL[v]=(unsigned char) r;  
            eksportasIGL[v+1]=(unsigned char) g;  
            eksportasIGL[v+2]=(unsigned char) b;                        
           }
         cout << "Atejome iki eksporto pabaigos \n";
         return  (unsigned char*) eksportasIGL; 

   }

int zenklas(int x){
   if(x<0) return -1;
      else if (x==0) return 0;
         else return 1;
  
}

void BMP24::tiese(int xNuo,int yNuo, int xIki, int yIki, char  r, char g, char b)
{ 
  int dx = xIki - xNuo;  
  int dy = yIki - yNuo;
  
  int zingsnisX = zenklas(dx);
  int zingsnisY = zenklas(dy);
  dx = (int) abs( (double) dx);  dy = (int) abs((double)dy);
 
  int d = dx;
  if (d < dy) d = dy;
  int x = xNuo; int y = yNuo;
  this->dekTaska(x,y,r,g,b);
  int xPakl = dx; int yPakl = dy;
  for(int i = 0; i < d; i++ ){
  xPakl +=  dx;  yPakl +=  dy;
  if ( xPakl > d ) { xPakl -= d; x += zingsnisX;}
  if ( yPakl > d ) { yPakl -= d; y += zingsnisY;}
  this->dekTaska(x,y,r,g,b);
  }
} 

// Bezier 2-os eiles:

void BMP24::bezier2( double* kontTaskai, char r, char g, char b){
 for(double t=0.0; t<=1.0; t+=0.001)
 {
   double daugianaris[3] = {(1-t)*(1-t), 2*t*(1-t), t*t};
   double taskas[2]={0.0,0.0};
  
 for(int j=0;j<2;j++) // pagal koordinates
    for(int i=0;i<3;i++) // pagal polinomo koeficientus
       taskas[j]+=daugianaris[i]*kontTaskai[i*2+j];
 
    this->dekTaska(taskas[0],taskas[1],r,g,b);
 }

} 
//----------------------------------------------------------------------------------------------------
  void BMP24::bezier2Splainas( double* kontTaskai, int nTasku,  char r, char g, char b){
   
  int lieka = nTasku;
  int idx = 1;
  while(lieka > 2){
    this->bezier2(&kontTaskai[(idx-1)*2], r,g,b);
    lieka-=2;
    idx+=2;
  }   
}



// Spalvinimas: (rekursinis-linijinis)
int  BMP24::rekursinisLinijinisSpalvinimas( int vidinisX, int vidinisY, 
                                             int kryptis, int buvesXL, int buvesXR, 
                                             char rKonturo,   char gKonturo,   char bKonturo, 
                                             char rDazu,   char gDazu,   char bDazu ) 
{ 
          char tR,tG,tB; 
          int x = vidinisX; 
          int xr=x, xl=x; 
          // Randame atkarpos galus: 
          // kairiji: 
 
          do { 
             this->duokTaskoSpalva( --xl, vidinisY, tR,tG,tB); 
           //  cout << xl << (int) tR << "   "<< (int)  tG <<  "  " << (int)   tB << "  \n"; 
          } 
          while (     ( ( rKonturo != tR) ||   ( gKonturo != tG)  || ( bKonturo != tB)) && 
                      ( ( rDazu != tR) ||   ( gDazu != tG)  || ( bDazu != tB))); 
 
          // ... ir desiniji : 
 
       do 
             this->duokTaskoSpalva( ++xr, vidinisY, tR,tG,tB); 
          while (     ( ( rKonturo != tR) ||   ( gKonturo != tG)  || ( bKonturo != tB)) && 
                      ( ( rDazu != tR) ||   ( gDazu != tG)  || ( bDazu != tB))); 
 
         xl++; xr--; 
         //------------------------------------------------------------------------------------------------- 
      //   cout << "Tiese: (" << xl << "," << vidinisY<< ")-("<<  xr <<"," << vidinisY << ")\n"; 
         this->horizontaliTiese(xl,xr,vidinisY,rDazu,gDazu,bDazu); 
         // meginame eiti pirma  vertikalia kryptimi 
         for(x=xl;x<=xr;x++){ 
           this->duokTaskoSpalva( x, vidinisY + kryptis, tR,tG,tB); 
           if  (( ( rKonturo != tR) ||   ( gKonturo != tG)  || ( bKonturo != tB)) && 
                      ( ( rDazu != tR) ||   ( gDazu != tG)  || ( bDazu != tB))) {
                rekursinisLinijinisSpalvinimas(  x,  vidinisY + kryptis, 
                                             kryptis, xl, xr, 
                                             rKonturo, gKonturo, bKonturo, 
                                             rDazu, gDazu, bDazu ); 
           } 
        } 
        //   meginame eiti kita vertikalia kryptimi; 
  //       int xPrad1=xl;
 //        if  (buvesXL < xl) xPrad1=buvesXL; 
         for(x=xl;x <= buvesXL; x++){ 
           this->duokTaskoSpalva(x, vidinisY - kryptis, tR,tG,tB); 
           if  (( ( rKonturo != tR) ||   ( gKonturo != tG)  || ( bKonturo != tB)) && 
                      ( ( rDazu != tR) ||   ( gDazu != tG)  || ( bDazu != tB))) { 
           x =   rekursinisLinijinisSpalvinimas(  x,  vidinisY - kryptis, 
                                             -kryptis, xl, xr, 
                                             rKonturo, gKonturo, bKonturo, 
                                             rDazu, gDazu, bDazu ); 
         } 
        } 
 
         for(x=buvesXR; x <= xr; x++){ 
           this->duokTaskoSpalva(x, vidinisY - kryptis, tR,tG,tB); 
           if  (( ( rKonturo != tR) ||   ( gKonturo != tG)  || ( bKonturo != tB)) && 
                      ( ( rDazu != tR) ||   ( gDazu != tG)  || ( bDazu != tB))) { 
           x =   rekursinisLinijinisSpalvinimas(  x,  vidinisY - kryptis, 
                                             -kryptis, xl, xr, 
                                             rKonturo, gKonturo, bKonturo, 
                                             rDazu, gDazu, bDazu ); 
          } 
        } 
 
       return xr; 
 
} 

// Spalvinimas:
void BMP24::spalvink(int x,int y, char rKonturo,char  gKonturo,char  bKonturo,
                                char  rDazu,char  gDazu,char  bDazu ) 
{

       this->rekursinisLinijinisSpalvinimas(x,y,1,x,x,rKonturo, gKonturo, bKonturo, 
                                             rDazu, gDazu, bDazu);

        return;
}


//---------------------------


// valymas:
void BMP24::valyk(char  r, char  g ,char  b ) 
{

        
    for(int x=0; x <  this -> plotis; x++)
      for(int y=0; y < this -> aukstis; y++)
           this->dekTaska(x,y,r,g,b); 

        return;
}


//---------------------------


   //  Destruktorius:

     BMP24::~BMP24(){
       
        delete[] vaizdas;
        delete[]  eksportasIGL;


      }
