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
/*Gönderilen katar sadece sayýlardan mý oluþuyor onu kontrol eden nesne*/
//
class Is {
public:
        bool Number(char *, int);
};

bool Is::Number(char *str, int len)
{
    for(;len > 0;--len, ++str) {
        if(!ISDIGIT(*str))      //karakterlerin ascii kodlarý 00x30 ve 00x39 arasýndaysa sayý
            return false;       //deðilse karakter barýndýrýyor
    }

    return true;
}


//
/*Tüm levhalarýn temeli, diðer nesneler bundan türeyecek*/
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
{								//levhayý çevir
	int temp;

	temp = boy;
	boy = en;
	en = temp;
}


//
/*Parçalarýn kesileceði kaynak levhalarý temsil eden nesne*/
//
class KaynakLevha : public Levha{					//parçalanacak olan levha

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
/*Kesilecek levhalarýn temsil edileceði nesne*/
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
	yatir();																//en her zaman büyük

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
/*parçalanan kaynak levhanýn üst sýnýrlarýný tutan nesne*/
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
/*kesilecek levhalarýn ve üst sýnýrlarýn sýralanmasýný saðlayan nesne*/
//
class Sort{
public :
	static void sortProcedure( vector <KesilecekLevha> &);
	static void sortBorder(vector <BottomBorder> &);
};


//kesilecek levhalar enleri azalan þekilde sýralanýyor. 
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

					
				else if (myVector[i].getBoy()<myVector[j].getBoy()){       //eþit en ise boylara göre sýrala
				temp = myVector[i];
				myVector[i] = myVector[j];
				myVector[j] = temp;
				}
			}
		}
}

//alt sýnýrlar yüksekliði artan þekilde sýralanýyor
void Sort::sortBorder(vector<BottomBorder> &bottomBorder)
{
	BottomBorder temp = bottomBorder.back();
		
	
	for(unsigned int i = 0; i < bottomBorder.size(); i++){						//en son eklenen uygun sýraya yerleþtiriyor
		if(bottomBorder.back().getHeight() < bottomBorder[i].getHeight()){
			for(unsigned int j = bottomBorder.size() - 1; j > i; j--)
				bottomBorder[j] = bottomBorder[j - 1];

			bottomBorder[i] = temp;
		}
	}
	
	//ayný yüksekliðe sahip yanyana olan sýnýrlar birleþtiriliyor
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
/*kesilcek levhalarýnýn nereden kesileceðini belirleyen nesne*/
//
class Placement{									//kesilcek levhalarýnýn nereden kesileceðini belirler
private:
        bool rotate,newBottomBorder;
	int maxAlan;								//boþluða tam oturan levhalar arasýnda en büyük alan
	int indexOfLevha,maxEn;						//boþluða tam oturmayanlar levhalar arasýnda en büyük en

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

			if(kesilecekLevha.size() > 0){						//kesilecek levha olduðu sürece devam
				newBottomBorder = true;
				for(unsigned int j = 0; j < kesilecekLevha.size(); j++){
						
						//eni boþluða tam oturan levhalar arasýndan max alan olaný bul
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
						   
				//boyu boþluða tam oturan levhalar arasýndan max alan olaný bul
				for(j = 0; j < kesilecekLevha.size(); j++){
 					if(bottomBorder.front().getLenght() == kesilecekLevha[j].getBoy()){
						
						if(kesilecekLevha[j].getEn() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
				 			if(maxAlan < 0){
  		   						maxAlan = kesilecekLevha[j].getAlan();
				 	   			indexOfLevha = j;
								rotate = true;
							}
							else if(kesilecekLevha[j].getAlan() > maxAlan){			//max alaný bul
		    					maxAlan = kesilecekLevha[j].getAlan();
				 	   			indexOfLevha = j;						    	 
							}
						}
					}
				}
				if(maxAlan > 0){			//maxAlan > 0 ise boþluða tam oturan bir levha var
					kesilecekLevha[indexOfLevha].setLevha(i+1,rotate,bottomBorder.front().getXStart(),bottomBorder.front().getHeight());  //levhanýn koordinatlarýný belirle
					kesilmisLevha.push_back(kesilecekLevha[indexOfLevha]);   //kesilen levhalara ekle
							
					for(unsigned int k = 0; k < bottomBorder.size(); k++){   //yeni alt sýnýra gerek olup olmadýðý bulunuyor
						if(kesilecekLevha[indexOfLevha].getYEnd() == bottomBorder[k].getHeight() && (kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd() || kesilecekLevha[indexOfLevha].getXEnd() == bottomBorder[k].getXStart())){		//ayný yükseklikte ve yanyana bir durum varsa gerek yok
							newBottomBorder = false;

							//yanýnda yer alan alt sýnýrý yeniden düzenle
							if(kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd())		
								bottomBorder[k].setXEnd(kesilecekLevha[indexOfLevha].getXEnd());
							else
								bottomBorder[k].setXStart(kesilecekLevha[indexOfLevha].getXStart());
						}
					}
					if(newBottomBorder == true){
						BottomBorder newBorder(kesilecekLevha[indexOfLevha].getXStart(),kesilecekLevha[indexOfLevha].getXEnd(),kesilecekLevha[indexOfLevha].getYEnd()); //kesilen parçaya göre yeni BottomBorder oluþtur
						bottomBorder.push_back(newBorder);
					}
				
					kesilecekLevha.erase(kesilecekLevha.begin() + indexOfLevha);		//kesilmis olaný sil
					bottomBorder.erase(bottomBorder.begin());							//en alt seviye doldu

					Sort::sortBorder(bottomBorder);										//seviyeleri artan þekilde sýrala
					maxAlan = -1;
					indexOfLevha = -1;
					continue;									//yeni bir levha kesmeye git
				}
				
				

	 			for(j = 0; j < kesilecekLevha.size(); j++){
				
					//boþluða tam oturan yok,yerleþebilen en büyük eni bul 
					if( kesilecekLevha[j].getEn() < bottomBorder.front().getLenght()){		
				 		
						//levhanýn boyu uygun mu
						if(kesilecekLevha[j].getBoy() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){		
				   			 
		  		    		 if(maxEn < 0){
			 				 	maxEn = kesilecekLevha[j].getEn();
			 				 	indexOfLevha = j;
							 	rotate = false;
							 }
							 else if(kesilecekLevha[j].getEn() > maxEn){		//en büyük en'i bul
							 	maxEn = kesilecekLevha[j].getEn();	 
							 	indexOfLevha = j;						 
							 }
						}
							
					}	
				}
				if(maxEn > 0){	//maxEn > 0 ise boþluða yerleþebilen en büyük en bulunmuþ demektir
		 			kesilecekLevha[indexOfLevha].setLevha(i+1,rotate,bottomBorder.front().getXStart(),bottomBorder.front().getHeight());//levhanýn nereden kesileceðini belirle
					kesilmisLevha.push_back(kesilecekLevha[indexOfLevha]);		//kesilmiþ olana ekle
					
					
								
					for(unsigned int k = 0; k < bottomBorder.size(); k++){	//yeni sýnýra gerek olup oladýðý bulunuyor
						if(kesilecekLevha[indexOfLevha].getYEnd() == bottomBorder[k].getHeight() && kesilecekLevha[indexOfLevha].getXStart() == bottomBorder[k].getXEnd()){
			  				bottomBorder[k].setXEnd(kesilecekLevha[indexOfLevha].getXEnd());	//komþu sýnýrý düzenle
							newBottomBorder = false;
						}
					}
						
						
					if(newBottomBorder == true){
						BottomBorder newBorder(kesilecekLevha[indexOfLevha].getXStart(),kesilecekLevha[indexOfLevha].getXEnd(),kesilecekLevha[indexOfLevha].getYEnd()); //kesilen levhaya göre yeni sýnýr oluþtur
						bottomBorder.push_back(newBorder);
					}
					
					
					
					bottomBorder.front().setXStart(kesilecekLevha[indexOfLevha].getXEnd());		//en alt seviye sýnýrýný yeniden düzenle
					Sort::sortBorder(bottomBorder);		//sýrala
					kesilecekLevha.erase(kesilecekLevha.begin() + indexOfLevha);	//kesilmiþ olaný sil
					maxEn = -1;
					indexOfLevha = -1;
					continue;		//yeni levha kesmeye git
				}
				


				if(maxAlan < 0 && maxEn < 0){				//boþluða yerleþen bulunamadý,kullanýlmayan alan
					int indexLeft = -1,indexRight = -1;		//boþluðun sýnýrlarý
					for(unsigned int b = 0; b < bottomBorder.size(); b ++){
						if(bottomBorder.front().getXStart() != 0){		//0 ise solda alt sýnýr elemený yok
							if(bottomBorder.front().getXStart() == bottomBorder[b].getXEnd())
								indexLeft = b;
						}
						if(bottomBorder.front().getXEnd() != kaynakLevha[i].getEn()){	// kaynak levhanýn enine eþitse sað üst sýnýr elemaný yok
							if(bottomBorder.front().getXEnd() == bottomBorder[b].getXStart())
								indexRight = b;
								
						}
					}
					
					if(indexLeft != -1 || indexRight != -1){		//her ikisi de -1 ise,tek alt sýnýr kalmýþtýr
						if((indexLeft == -1 && indexRight != -1))	//sað alt sýnýrý düzenle
							bottomBorder[indexRight].setXStart(bottomBorder.front().getXStart());
						
							
						else if(indexRight == -1 && indexLeft != -1)	//sol alt sýnýrý düzenle
								bottomBorder[indexLeft].setXEnd(bottomBorder.front().getXEnd());
							
							
						else if(indexRight > -1 && indexLeft > -1){		//yüksekliði küçük olaný düzenle
								if(bottomBorder[indexRight].getHeight() < bottomBorder[indexLeft].getHeight())
									bottomBorder[indexRight].setXStart(bottomBorder.front().getXStart());
								
							else if(bottomBorder[indexLeft].getHeight() < bottomBorder[indexRight].getHeight())
									bottomBorder[indexLeft].setXEnd(bottomBorder.front().getXEnd());
								
						}
						
						bottomBorder.erase(bottomBorder.begin());		//düzenlemeler yapýldý,en düþük seviyeyi sil
					}
				}
				
				if(bottomBorder.size() == 1){		//üst sýnýr bir tane ve kesilecek levhalarýn hiçbirinin boyu uygun deðilse
					bool hepsiBuyuk = true;
					for(unsigned int b = 0; b < kesilecekLevha.size(); b++){			//uygun olan var mý
						if(bottomBorder.front().getHeight() + kesilecekLevha[b].getBoy() <= kaynakLevha[i].getBoy()){
							hepsiBuyuk = false;
							break;
						}
					}
					if(hepsiBuyuk == true){			//uygun levha bulunamadý,üst sýnýrlarý sýfýrla,yeni kaynak levhaya geç
						bottomBorder.erase(bottomBorder.begin(),bottomBorder.end());
						BottomBorder bBorder(0,kaynakLevha.front().getEn(),0);
						bottomBorder.push_back(bBorder);
						break;
					
					}
						
				}
				
			}
			else				//kesilecek levha kalmadý
				break;
			
		} //
	}
}

#endif
