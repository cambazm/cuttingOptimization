//---------------------------------------------------------------------------

#ifndef veriGirisiH
#define veriGirisiH
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <Mask.hpp>
#include <vector>
#include <locale>
#define max(x,y) x>=y ? x:y
#define min(x,y) x<y ? x:y
#define MIN_DIGIT 0x30
#define MAX_DIGIT 0x39
#define ISDIGIT(x) ((x >= MIN_DIGIT) && (x <= MAX_DIGIT))
using namespace std;
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *ekle;
        TGroupBox *GroupBox1;
        TLabel *lblKac;
        TLabel *lblBoy;
        TLabel *lblEn;
        TEdit *txtTane;
        TEdit *txtBoy;
        TEdit *txtEn;
        TGroupBox *GroupBox2;
        TButton *kes;
        TMainMenu *MainMenu1;
        TMenuItem *Ayarlar;
        TMenuItem *Yardim;
        TMenuItem *Hakkinda;
        TStringGrid *StringGrid1;
        TMenuItem *Dil;
        TMenuItem *English;
        TMenuItem *Turkce;
        TMenuItem *Cikis;
        TComboBox *ComboBox1;
        TLabel *lblHata;
        TLabel *lblHata2;
        TLabel *lblKac2;
        TEdit *txtTane2;
        TEdit *txtEn2;
        TLabel *lblEn2;
        TLabel *lblBoy2;
        TEdit *txtBoy2;
        TLabel *lblTurn;
        TLabel *lblRow;
        TButton *sifirla;
        TComboBox *cmbTesterePayi;
        TLabel *lblTestere;
        TLabel *lblAciklama;
        void __fastcall Load(TObject *Sender);
        void __fastcall kesClick(TObject *Sender);
        void __fastcall EnglishClick(TObject *Sender);
        void __fastcall CikisClick(TObject *Sender);
        void __fastcall TurkceClick(TObject *Sender);
        void __fastcall HakkindaClick(TObject *Sender);
        void __fastcall ekleClick(TObject *Sender);
        void __fastcall sifirlaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

//
/*G�nderilen katar sadece say�lardan m� olu�uyor onu kontrol eden nesne*/
//
class Is {
public:
        bool Number(char *, int);
};

bool Is::Number(char *str, int len)
{
    for(;len > 0;--len, ++str) {
        if(!ISDIGIT(*str))      //karakterlerin ascii kodlar� 00x30 ve 00x39 aras�ndaysa say�
            return false;       //de�ilse karakter bar�nd�r�yor
    }

    return true;
}


//
/*T�m levhalar�n temeli, di�er nesneler bundan t�reyecek*/
//
class Levha	{										//levha 

protected:
	int en;
	int boy;
	int alan;


public:
	Levha(int, int);
	int getEn() { return en; }
	int getBoy() { return boy; }
	int getAlan() { return alan; }
	void setAlan(int levhaAlan) { alan = levhaAlan; }
	void setBoy(int levhaBoy) { boy = levhaBoy; }
	void setEn(int levhaEn) { en = levhaEn; }
	void yatir();								// en = max(en,boy)
	void cevir();
};

Levha::Levha(int enLevha, int boyLevha)
{			//constructer
	en = enLevha;
	boy = boyLevha;
	alan = enLevha * boyLevha;
}

void Levha::yatir()
{
	int temp1,temp2;
	temp1 = en;
	temp2 = boy;
	en = max(temp1,temp2);
	boy = min(temp1,temp2);
}

void Levha::cevir()
{								//levhay� �evir
	int temp;

	temp = boy;
	boy = en;
	en = temp;
}


//
/*Par�alar�n kesilece�i kaynak levhalar� temsil eden nesne*/
//
class KaynakLevha : public Levha{					//par�alanacak olan levha

public:
        KaynakLevha( int,  int);
        ~KaynakLevha();
};

KaynakLevha::KaynakLevha( int en1, int boy1) : Levha(en1, boy1)	//consructer
{
	yatir();
}

KaynakLevha::~KaynakLevha()
{

}


//
/*Kesilecek levhalar�n temsil edilece�i nesne*/
//
class KesilecekLevha : public Levha{					//kesilecek levha
private:
	int yerlestigiLevhaNo;
	int x1,
            x2,
	    y1,
	    y2;
        int girisSirasi;

public:
        KesilecekLevha(int, int);
	KesilecekLevha(const KesilecekLevha &);
	void setLevha( int,bool,int,int);
        void setSira(int);
        int getSira() { return girisSirasi; }
        int getYStart(){ return y1; }
        int getYEnd(){ return y2; }
        int getXStart(){ return x1; }
        int getXEnd(){ return x2; }
        int getLevhaNo() { return yerlestigiLevhaNo; }
        ~KesilecekLevha();
};

KesilecekLevha::KesilecekLevha( int en1,  int boy1) : Levha(en1, boy1)      //constructer
{
	yatir();																//en her zaman b�y�k

	yerlestigiLevhaNo = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
        girisSirasi = 0;

}

KesilecekLevha::KesilecekLevha(const KesilecekLevha &right) : Levha(right.en,right.boy) //copy consructer
{
	en = right.en;
	boy = right.boy;
	alan = right.alan;
	yerlestigiLevhaNo = right.yerlestigiLevhaNo;
	x1=right.x1;
	x2=right.x2;
	y1=right.y1;
	y2=right.y2;
        girisSirasi = right.girisSirasi;
}


//levha hangi levhadan ve koordinatlardan kesildi
void KesilecekLevha::setLevha( int levhaNo ,bool rotate, int x, int y)
{
	if(rotate == false) {
		yerlestigiLevhaNo = levhaNo; 
		x1 = x;
		x2 = x + en;
		y1 = y;
		y2 = y + boy;
	}
	else {
		yerlestigiLevhaNo=levhaNo;
		x1 = x;
		x2 = x + boy;
		y1 = y;
		y2 = y + en;
	}
}

void KesilecekLevha::setSira(int row)
{
        girisSirasi = row;
}

KesilecekLevha::~KesilecekLevha()
{

}


//
/*par�alanan kaynak levhan�n �st s�n�rlar�n� tutan nesne*/
//
class BottomBorder{
private:
	int x1,x2;
	int y;
public:
        BottomBorder(int xStart = 0, int xEnd = 0, int height = 0);
	void setXStart(int x){ x1 = x;}
	void setXEnd(int x){ x2 = x;}
	void setHeight(int yh){ y = yh;}
	int getXStart(){ return x1;}
	int getXEnd(){ return x2;}
	int getLenght(){ return x2 - x1;}
	int getHeight(){ return y;}
};

BottomBorder::BottomBorder(int xStart,int xEnd,int height)
{		//consructer
        x1 = xStart;
        x2 = xEnd;
        y = height;
}


//
/*kesilecek levhalar�n ve �st s�n�rlar�n s�ralanmas�n� sa�layan nesne*/
//
class Sort{
public :
	static void sortProcedure( vector <KesilecekLevha> &);
	static void sortBorder(vector <BottomBorder> &);
};


//kesilecek levhalar enleri azalan �ekilde s�ralan�yor. 
void Sort::sortProcedure( vector<KesilecekLevha> &myVector)
{
	KesilecekLevha temp(0,0);
		for(unsigned int i=0; i<myVector.size(); i++) {
			for(unsigned int j = i+1; j<= myVector.size(); j++){
				if (myVector[i].getEn() < myVector[j].getEn()){
					temp = myVector[i];
					myVector[i] = myVector[j];
					myVector[j] = temp;
				}

					
				else if (myVector[i].getBoy()<myVector[j].getBoy()){       //e�it en ise boylara g�re s�rala
				temp = myVector[i];
				myVector[i] = myVector[j];
				myVector[j] = temp;
				}
			}
		}
}

//alt s�n�rlar y�ksekli�i artan �ekilde s�ralan�yor
void Sort::sortBorder(vector<BottomBorder> &bottomBorder)
{
	BottomBorder temp = bottomBorder.back();
		
	
	for(unsigned int i = 0; i < bottomBorder.size(); i++){						//en son eklenen uygun s�raya yerle�tiriyor
		if(bottomBorder.back().getHeight() < bottomBorder[i].getHeight()){
			for(unsigned int j = bottomBorder.size() - 1; j > i; j--)
				bottomBorder[j] = bottomBorder[j - 1];

			bottomBorder[i] = temp;
		}
	}
	
	//ayn� y�ksekli�e sahip yanyana olan s�n�rlar birle�tiriliyor
	for(unsigned int i = 0; i < bottomBorder.size() - 1; i++){
		if(bottomBorder[i].getHeight() == bottomBorder[i+1].getHeight()){
			if(bottomBorder[i].getXStart() < bottomBorder[i+1].getXStart())
				bottomBorder[i].setXEnd(bottomBorder[i+1].getXEnd());
			else
				bottomBorder[i].setXStart(bottomBorder[i+1].getXStart());

			bottomBorder.erase(bottomBorder.begin() + i+1);
		}
	}
}
	

//
/*kesilcek levhalar�n�n nereden kesilece�ini belirleyen nesne*/
//
class Placement{									//kesilcek levhalar�n�n nereden kesilece�ini belirler
private:
        bool rotate,newBottomBorder;
	int maxAlan;								//bo�lu�a tam oturan levhalar aras�nda en b�y�k alan
	int indexOfLevha,maxEn;						//bo�lu�a tam oturmayanlar levhalar aras�nda en b�y�k en

public:
        void placementPolicy(vector<KesilecekLevha> &,vector<KesilecekLevha> &, vector<KaynakLevha> &, vector<BottomBorder> &);
};

void Placement::placementPolicy(vector<KesilecekLevha> &kesilecekLevha,vector<KesilecekLevha> &kesilmisLevha, vector<KaynakLevha> &kaynakLevha, vector<BottomBorder> &bottomBorder)
{
	maxAlan = -1;
	indexOfLevha = -1;
	maxEn = -1;
        unsigned int j;

	for(unsigned int i = 0; i < kaynakLevha.size(); i++){
		while(true){

			if(kesilecekLevha.size() > 0){						//kesilecek levha oldu�u s�rece devam
				newBottomBorder = true;
				for(unsigned int j = 0; j < kesilecekLevha.size(); j++){
						
						//eni bo�lu�a tam oturan levhalar aras�ndan max alan olan� bul
						if(bottomBorder.front().getLenght() == kesilecekLevha[j].getEn() ){			
                    
							if(kesilecekLevha[j].getBoy() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
								
								if(maxAlan < 0){
									maxAlan = kesilecekLevha[j].getAlan();
									indexOfLevha = j;
    								rotate = false;	
								}
								else if(kesilecekLevha[j].getAlan() > maxAlan){			//max alan 	
									  maxAlan = kesilecekLevha[j].getAlan();
									  indexOfLevha = j;                                   
								 }
							}
						}
					
				}
						   
				//boyu bo�lu�a tam oturan levhalar aras�ndan max alan olan� bul
				for(j = 0; j < kesilecekLevha.size(); j++){
 					if(bottomBorder.front().getLenght() == kesilecekLevha[j].getBoy()){
						
						if(kesilecekLevha[j].getEn() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
				 			if(maxAlan < 0){
  		   						maxAlan = kesilecekLevha[j].getAlan();
				 	   			indexOfLevha = j;
								rotate = true;
							}
							else if(kesilecekLevha[j].getAlan() > maxAlan){			//max alan� bul
		    					maxAlan = kesilecekLevha[j].getAlan();
				 	   			indexOfLevha = j;						    	 
							}
						}
					}
				}
				if(maxAlan > 0){			//maxAlan > 0 ise bo�lu�a tam oturan bir levha var
					kesilecekLevha[indexOfLevha].setLevha(i+1,rotate,bottomBorder.front().getXStart(),bottomBorder.front().getHeight());  //levhan�n koordinatlar�n� belirle
					kesilmisLevha.push_back(kesilecekLevha[indexOfLevha]);   //kesilen levhalara ekle
							
					for(unsigned int k = 0; k < bottomBorder.size(); k++){   //yeni alt s�n�ra gerek olup olmad��� bulunuyor
						if(kesilecekLevha[indexOfLevha].getYEnd() == bottomBorder[k].getHeight() && (kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd() || kesilecekLevha[indexOfLevha].getXEnd() == bottomBorder[k].getXStart())){		//ayn� y�kseklikte ve yanyana bir durum varsa gerek yok
							newBottomBorder = false;

							//yan�nda yer alan alt s�n�r� yeniden d�zenle
							if(kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd())		
								bottomBorder[k].setXEnd(kesilecekLevha[indexOfLevha].getXEnd());
							else
								bottomBorder[k].setXStart(kesilecekLevha[indexOfLevha].getXStart());
						}
					}
					if(newBottomBorder == true){
						BottomBorder newBorder(kesilecekLevha[indexOfLevha].getXStart(),kesilecekLevha[indexOfLevha].getXEnd(),kesilecekLevha[indexOfLevha].getYEnd()); //kesilen par�aya g�re yeni BottomBorder olu�tur
						bottomBorder.push_back(newBorder);
					}
				
					kesilecekLevha.erase(kesilecekLevha.begin() + indexOfLevha);		//kesilmis olan� sil
					bottomBorder.erase(bottomBorder.begin());							//en alt seviye doldu

					Sort::sortBorder(bottomBorder);										//seviyeleri artan �ekilde s�rala
					maxAlan = -1;
					indexOfLevha = -1;
					continue;									//yeni bir levha kesmeye git
				}
				
				

	 			for(j = 0; j < kesilecekLevha.size(); j++){
				
					//bo�lu�a tam oturan yok,yerle�ebilen en b�y�k eni bul 
					if( kesilecekLevha[j].getEn() < bottomBorder.front().getLenght()){		
				 		
						//levhan�n boyu uygun mu
						if(kesilecekLevha[j].getBoy() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){		
				   			 
		  		    		 if(maxEn < 0){
			 				 	maxEn = kesilecekLevha[j].getEn();
			 				 	indexOfLevha = j;
							 	rotate = false;
							 }
							 else if(kesilecekLevha[j].getEn() > maxEn){		//en b�y�k en'i bul
							 	maxEn = kesilecekLevha[j].getEn();	 
							 	indexOfLevha = j;						 
							 }
						}
							
					}	
				}
				if(maxEn > 0){	//maxEn > 0 ise bo�lu�a yerle�ebilen en b�y�k en bulunmu� demektir
		 			kesilecekLevha[indexOfLevha].setLevha(i+1,rotate,bottomBorder.front().getXStart(),bottomBorder.front().getHeight());//levhan�n nereden kesilece�ini belirle
					kesilmisLevha.push_back(kesilecekLevha[indexOfLevha]);		//kesilmi� olana ekle
					
					
								
					for(unsigned int k = 0; k < bottomBorder.size(); k++){	//yeni s�n�ra gerek olup olad��� bulunuyor
						if(kesilecekLevha[indexOfLevha].getYEnd() == bottomBorder[k].getHeight() && kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd()){
			  				bottomBorder[k].setXEnd(kesilecekLevha[indexOfLevha].getXEnd());	//kom�u s�n�r� d�zenle
							newBottomBorder = false;
						}
					}
						
						
					if(newBottomBorder == true){
						BottomBorder newBorder(kesilecekLevha[indexOfLevha].getXStart(),kesilecekLevha[indexOfLevha].getXEnd(),kesilecekLevha[indexOfLevha].getYEnd()); //kesilen levhaya g�re yeni s�n�r olu�tur
						bottomBorder.push_back(newBorder);
					}
					
					
					
					bottomBorder.front().setXStart(kesilecekLevha[indexOfLevha].getXEnd());		//en alt seviye s�n�r�n� yeniden d�zenle
					Sort::sortBorder(bottomBorder);		//s�rala
					kesilecekLevha.erase(kesilecekLevha.begin() + indexOfLevha);	//kesilmi� olan� sil
					maxEn = -1;
					indexOfLevha = -1;
					continue;		//yeni levha kesmeye git
				}
				


				if(maxAlan < 0 && maxEn < 0){				//bo�lu�a yerle�en bulunamad�,kullan�lmayan alan
					int indexLeft = -1,indexRight = -1;		//bo�lu�un s�n�rlar�
					for(unsigned int b = 0; b < bottomBorder.size(); b ++){
						if(bottomBorder.front().getXStart() != 0){		//0 ise solda alt s�n�r elemen� yok
							if(bottomBorder.front().getXStart() == bottomBorder[b].getXEnd())
								indexLeft = b;
						}
						if(bottomBorder.front().getXEnd() != kaynakLevha[i].getEn()){	// kaynak levhan�n enine e�itse sa� �st s�n�r eleman� yok
							if(bottomBorder.front().getXEnd() == bottomBorder[b].getXStart())
								indexRight = b;
								
						}
					}
					
					if(indexLeft != -1 || indexRight != -1){		//her ikisi de -1 ise,tek alt s�n�r kalm��t�r
						if((indexLeft == -1 && indexRight != -1))	//sa� alt s�n�r� d�zenle
							bottomBorder[indexRight].setXStart(bottomBorder.front().getXStart());
						
							
						else if(indexRight == -1 && indexLeft != -1)	//sol alt s�n�r� d�zenle
								bottomBorder[indexLeft].setXEnd(bottomBorder.front().getXEnd());
							
							
						else if(indexRight > -1 && indexLeft > -1){		//y�ksekli�i k���k olan� d�zenle
								if(bottomBorder[indexRight].getHeight() < bottomBorder[indexLeft].getHeight())
									bottomBorder[indexRight].setXStart(bottomBorder.front().getXStart());
								
							else if(bottomBorder[indexLeft].getHeight() < bottomBorder[indexRight].getHeight())
									bottomBorder[indexLeft].setXEnd(bottomBorder.front().getXEnd());
								
						}
						
						bottomBorder.erase(bottomBorder.begin());		//d�zenlemeler yap�ld�,en d���k seviyeyi sil
					}
				}
				
				if(bottomBorder.size() == 1){		//�st s�n�r bir tane ve kesilecek levhalar�n hi�birinin boyu uygun de�ilse
					bool hepsiBuyuk = true;
					for(unsigned int b = 0; b < kesilecekLevha.size(); b++){			//uygun olan var m�
						if(bottomBorder.front().getHeight() + kesilecekLevha[b].getBoy() <= kaynakLevha[i].getBoy()){
							hepsiBuyuk = false;
							break;
						}
					}
					if(hepsiBuyuk == true){			//uygun levha bulunamad�,�st s�n�rlar� s�f�rla,yeni kaynak levhaya ge�
						bottomBorder.erase(bottomBorder.begin(),bottomBorder.end());
						BottomBorder bBorder(0,kaynakLevha.front().getEn(),0);
						bottomBorder.push_back(bBorder);
						break;
					
					}
						
				}
				
			}
			else				//kesilecek levha kalmad�
				break;
			
		} //
	}
}

#endif
