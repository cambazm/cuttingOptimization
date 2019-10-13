//---------------------------------------------------------------------------

#ifndef sondurumH
#define sondurumH
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
#include <Dialogs.hpp>
#include <vector>
#include <locale>
#include "hesapCizim.h"
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
        TLabel *lblHata;
        TLabel *lblHata2;
        TLabel *lblKac2;
        TEdit *txtTane2;
        TEdit *txtEn2;
        TLabel *lblEn2;
        TLabel *lblBoy2;
        TEdit *txtBoy2;
        TLabel *lblTurn;
        TButton *sifirla;
        TComboBox *cmbTesterePayi;
        TLabel *lblTestere;
        TLabel *lblAciklama;
        TStringGrid *StringGrid2;
        TButton *ekle2;
        TButton *sifirla2;
        TCheckBox *chk;
        TOpenDialog *od;
        TMenuItem *Yardm1;
        TMenuItem *dosyaac;
        void __fastcall Load(TObject *Sender);
        void __fastcall kesClick(TObject *Sender);
        void __fastcall EnglishClick(TObject *Sender);
        void __fastcall CikisClick(TObject *Sender);
        void __fastcall TurkceClick(TObject *Sender);
        void __fastcall HakkindaClick(TObject *Sender);
        void __fastcall ekleClick(TObject *Sender);
        void __fastcall sifirlaClick(TObject *Sender);
        void __fastcall sifirla2Click(TObject *Sender);
        void __fastcall ekle2Click(TObject *Sender);
        void __fastcall Yardm1Click(TObject *Sender);
        void __fastcall dosyaacClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int kesilecekLevhaSirasi;
        int kaynakLevhaSirasi;
        int dil;        //dil - 0 TR, 1 ENG
        char str[10];
        bool dosyadan;
        vector <TPanel*> panelVector;
        vector <mehmetPanel*> panelKesilmis;
        AnsiString hataSadeceSayi;
        AnsiString hataKaynakLevhaBos;
        AnsiString hataLevhaBos;
        AnsiString hataKesilecekLevhaBos;
        void turkce();
        void eng();
        __fastcall TForm1(TComponent* Owner);
};
//-------------------------------------------------
void TForm1::turkce()
{
        StringGrid1->Cells[0][0] = "Kaç Tane";
        StringGrid1->Cells[1][0] = "En";
        StringGrid1->Cells[2][0] = "Boy";
        StringGrid1->Cells[3][0] = "Çevrilebilirlik";
        StringGrid1->ColWidths[0] = 69;
        StringGrid1->ColWidths[1] = 50;
        StringGrid1->ColWidths[2] = 50;
        StringGrid1->ColWidths[3] = 95;

        StringGrid2->Cells[0][0] = "Kaç Tane";
        StringGrid2->Cells[1][0] = "En";
        StringGrid2->Cells[2][0] = "Boy";
        StringGrid2->ColWidths[0] = 81;
        StringGrid2->ColWidths[1] = 83;
        StringGrid2->ColWidths[2] = 83;

        GroupBox1->Caption = "Kaynak Levhalar";
        GroupBox2->Caption = "Kesilecek Levhalar";
        lblKac->Caption = "Kaç Tane";
        lblEn->Caption = "En";
        lblBoy->Caption = "Boy";
        lblAciklama->Caption = "Levha uzunluklarý cm cinsinden olup; testere payý bunun 10 da biri olan mm cinsindendir";

        ekle->Caption = "Ekle";
        ekle2->Caption = "Ekle";
        kes->Caption = "Kes";
        sifirla->Caption = "Sýfýrla";
        sifirla2->Caption = "Sýfýrla";
        chk->Caption = "Döndürülemez";

        Ayarlar->Caption = "Ayarlar";
        dosyaac->Caption = "Dosya Aç";
        Cikis->Caption = "Çýkýþ";
        Yardim->Caption = "Yardým";
        Dil->Caption = "Language";
        Hakkinda->Caption = "Hakkýnda";

        hataSadeceSayi = "HATA: Sadece sayýlar girilebilir";
        hataKaynakLevhaBos = "HATA: Kaynak Levha alanlarý boþ býrakýlamaz";
        hataLevhaBos = "HATA: Yeterli sayýda levha girilmedi";
        hataKesilecekLevhaBos = "HATA: Kesilecek Levha bilgileri eksik verilemez";

}
//--------------------------------------------------
void TForm1::eng()
{
        GroupBox1->Caption = "Base tablets";
        GroupBox2->Caption = "Tablets to be cut";
        lblKac->Caption = "How Many";
        lblKac2->Caption = "How Many";
        lblEn->Caption = "Width";
        lblEn2->Caption = "Width";
        lblBoy->Caption = "Length";
        lblBoy2->Caption = "Length";
        lblTurn->Caption = "Turnability";
        lblTestere->Caption = "Saw share";
        lblAciklama->Caption = "Lengths are centimeters but saw share is milimeters";

        ekle->Caption = "Add";
        ekle2->Caption = "Add";
        kes->Caption = "Cut";
        sifirla->Caption = "Reset";
        sifirla2->Caption = "Reset";
        chk->Caption = "Can not Turn";

        StringGrid1->Cells[0][0] = "How Many";
        StringGrid1->Cells[1][0] = "Width";
        StringGrid1->Cells[2][0] = "Length";
        StringGrid1->Cells[3][0] = "Turnability";

        StringGrid2->Cells[0][0] = "How Many";
        StringGrid2->Cells[1][0] = "Width";
        StringGrid2->Cells[2][0] = "Length";

        Ayarlar->Caption = "Settings";
        dosyaac->Caption = "Open File";
        Cikis->Caption = "Exit";
        Yardim->Caption = "Help";
        Dil->Caption = "Dil";
        Hakkinda->Caption = "About";

        hataSadeceSayi = "ERROR: Only numbers are allowed";
        hataKaynakLevhaBos = "ERROR: Base Tablet info must be given";
        hataLevhaBos = "ERROR: Not enough tablets are given";
        hataKesilecekLevhaBos = "ERROR: Tablets to be cut info must be given";
}
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
        int girisSirasi;


public:
	Levha(int, int);
	int getEn() { return en; }
	int getBoy() { return boy; }
	int getAlan() { return alan; }
        void setSira(int);
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

void Levha::setSira(int row)
{
        girisSirasi = row;
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
        bool cevrilebilir;

public:
        KesilecekLevha(int, int, bool);
	KesilecekLevha(const KesilecekLevha &);
	void setLevha( int,bool,int,int);
        int getSira() { return girisSirasi; }
        int getYStart(){ return y1; }
        int getYEnd(){ return y2; }
        int getXStart(){ return x1; }
        int getXEnd(){ return x2; }
        int getLevhaNo() { return yerlestigiLevhaNo; }
        bool getRotate() { return cevrilebilir; }
        ~KesilecekLevha();
};

KesilecekLevha::KesilecekLevha( int en1,  int boy1, bool cevrilebilir1) : Levha(en1, boy1)      //constructer
{
        cevrilebilir = cevrilebilir1;
        if(cevrilebilir==true)
            yatir();

        																//en her zaman büyük
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
        cevrilebilir = right.cevrilebilir;
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
                cevir();
	}
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
        static void sortProcedure( vector <KaynakLevha> &);

};


//kesilecek levhalar enleri azalan þekilde sýralanýyor.

void Sort::sortProcedure( vector<KesilecekLevha> &myVector){


        KesilecekLevha temp(0,0,true);
      //  for(int z = 0; z<myVector.size(); z++)
      //         temp = myVector[z];



		for(unsigned int i=0; i<myVector.size(); i++) {
			for(unsigned int j = i+1; j< myVector.size(); j++){
				if (myVector[i].getEn() < myVector[j].getEn()){		//büyükten küçüðe sýrala
					temp = myVector[i];
					myVector[i] = myVector[j];
					myVector[j] = temp;
				}


				else if(myVector[i].getEn() == myVector[j].getEn()){  // en eþit ise boylara göre sýrala
					if(myVector[i].getBoy()<myVector[j].getBoy()){
						temp = myVector[i];
						myVector[i] = myVector[j];
						myVector[j] = temp;
					}
				}
			}
		}
}
//kaynak levhalarý enleri büyükten küçüðe doðru sýralar
void Sort::sortProcedure( vector<KaynakLevha> &myVector){


        KaynakLevha temp(0,0);
      //  for(int z = 0; z<myVector.size(); z++)
      //         temp = myVector[z];



		for(unsigned int i=0; i<myVector.size(); i++) {
			for(unsigned int j = i+1; j< myVector.size(); j++){
				if (myVector[i].getEn() < myVector[j].getEn()){		//büyükten küçüðe sýrala
					temp = myVector[i];
					myVector[i] = myVector[j];
					myVector[j] = temp;
				}


				else if(myVector[i].getEn() == myVector[j].getEn()){  // en eþit ise boylara göre sýrala
					if(myVector[i].getBoy()<myVector[j].getBoy()){
						temp = myVector[i];
						myVector[i] = myVector[j];
						myVector[j] = temp;
					}
				}
			}
		}
}

//alt sýnýrlar yüksekliði artan þekilde sýralanýyor
void Sort::sortBorder(vector<BottomBorder> &bottomBorder)
{
	BottomBorder temp = bottomBorder.back();

      //  BottomBorder w;
      // for(int o = 0;o < bottomBorder.size(); o++)
      //       w = bottomBorder[o];


	for(unsigned int i = 0; i < bottomBorder.size() - 1; i++){						//en son eklenen uygun sýraya yerleþtiriyor
		if(bottomBorder.back().getHeight() < bottomBorder[i].getHeight()){
			for(unsigned int j = bottomBorder.size() - 1; j > i; j--)
				bottomBorder[j] = bottomBorder[j - 1];

			bottomBorder[i] = temp;
		}
	}
      //  for(int o = 0;o < bottomBorder.size(); o++)
      //       w = bottomBorder[o];


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
       // for(int o = 0;o < bottomBorder.size(); o++)
       //      w = bottomBorder[o];

}


//
/*kesilcek levhalarýnýn nereden kesileceðini belirleyen nesne*/
//
class Placement{									//kesilcek levhalarýnýn nereden kesileceðini belirler
    private:
	    bool rotate,newBottomBorder,cevirme,cevir;
		int maxAlan,index;								//boþluða tam oturan levhalar arasýnda en büyük alan
		int indexOfLevha,maxEn;						//boþluða tam oturmayanlar levhalar arasýnda en büyük en

	public:
 	    void placementPolicy(vector<KesilecekLevha> &,vector<KesilecekLevha> &,vector<KesilecekLevha> &, vector<KaynakLevha> &, vector<BottomBorder> &, int);
};

void Placement::placementPolicy(vector<KesilecekLevha> &kesilecekLevha,vector<KesilecekLevha> &kesilmisLevha,vector<KesilecekLevha> &kesilemezLevha, vector<KaynakLevha> &kaynakLevha, vector<BottomBorder> &bottomBorder, int testerePayi){
	maxAlan = -1;
	indexOfLevha = -1;
	maxEn = -1;
        cevirme = false;
        cevir = false;
        bool kesilemez = false;
        for(unsigned int a = 0; a < kaynakLevha.size(); a++){
                for(unsigned int n = 0; n < kesilecekLevha.size(); n++){
                        if(kesilecekLevha[n].getEn() - testerePayi == kaynakLevha[a].getEn() && kesilecekLevha[n].getBoy() - testerePayi == kaynakLevha[a].getBoy() ){
                                kesilecekLevha[n].setLevha(a+1,true,0,0);//levhanýn nereden kesileceðini belirle
                                kesilmisLevha.push_back(kesilecekLevha[n]);
                                kesilecekLevha.erase(kesilecekLevha.begin() + n);
                                break;
                        }

                        else if(kesilecekLevha[n].getRotate() == true){
                                for(int e = 0; e<kaynakLevha.size(); e++){

                                        if(kesilecekLevha[n].getEn() - testerePayi > kaynakLevha[e].getEn() || kesilecekLevha[n].getBoy() - testerePayi > kaynakLevha[e].getBoy()){
                                                if(kesilecekLevha[n].getBoy() - testerePayi > kaynakLevha[e].getEn() || kesilecekLevha[n].getEn() - testerePayi > kaynakLevha[e].getBoy())
                                                        kesilemez = true;
                                                else{ kesilemez = false;
                                                        break;
                                                }
                                        }
                                        else {kesilemez = false;
                                                break;
                                        }
                                }
                                if(kesilemez == true){
                                        kesilemezLevha.push_back(kesilecekLevha[n]);
                                        kesilecekLevha.erase(kesilecekLevha.begin() + n);
                                }
                        }
                        else{
                                for(int d = 0; d<kaynakLevha.size(); d++){
                                        if(kesilecekLevha[n].getEn() - testerePayi > kaynakLevha[d].getEn() || kesilecekLevha[n].getBoy() - testerePayi > kaynakLevha[d].getBoy())
                                                kesilemez = true;
                                         else{
                                                kesilemez = false;
                                                break;
                                        }
                                }
                                if(kesilemez == true){
                                        kesilemezLevha.push_back(kesilecekLevha[n]);
                                        kesilecekLevha.erase(kesilecekLevha.begin() + n);
                                }
                }       }
        }



	for(unsigned int i = 0; i < kaynakLevha.size(); i++){
		while(true){

			if(kesilecekLevha.size() > 0){						//kesilecek levha olduðu sürece devam
				newBottomBorder = true;
				for(unsigned int j = 0; j < kesilecekLevha.size(); j++){
        				index = -1;
                                        cevir = false;
                                        cevirme = false;		//eni ya da boyu tam oturan levhalarýn indexini tutar

					//eni boþluða tam oturan levhalar arasýndan max alan olaný bul
					if(bottomBorder.front().getLenght() == kesilecekLevha[j].getEn() ){
						if(kesilecekLevha[j].getBoy() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
							index = j;
							cevirme = true;
						}
					}
					if(bottomBorder.front().getLenght() == kesilecekLevha[j].getBoy() && index < 0 && kesilecekLevha[j].getRotate() == true){   //levhanýn çevrilebilir olmasý gerekiyor.
						if(kesilecekLevha[j].getEn() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy())
							index = j;
							cevir = true;
					}
					if(index > -1 ){			//boþluða eni veya boyu tam oturan levhalardan alaný en büyük olaný seç

						if(maxAlan < 0){
  		   					maxAlan = kesilecekLevha[j].getAlan();
				 	   		indexOfLevha = index;
                                                        index = -1;
                                                        if(cevir == true){
                                                                rotate = true;
                                                                cevir = false;
                                                        }
                                                        if(cevirme == true){
                                                                rotate = false;
                                                                cevirme = false;
                                                        }
						}
						else if(kesilecekLevha[j].getAlan() > maxAlan){			//max alaný bul
		    				maxAlan = kesilecekLevha[j].getAlan();
				 	   		indexOfLevha = index;
                                                        index = -1;
                                                        if(cevir == true){
                                                                rotate = true;
                                                                cevir = false;
                                                        }
                                                        if(cevirme == true){
                                                                rotate = false;
                                                                cevirme = false;
                                                        }

						}
					}
				}
				int y = kesilecekLevha.size();
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



				//boþluða tam uyan levha bulunamadý,eni yada boyu uygun olan levhalardan en büyük ene
				//yada boya sahip olan seçilecek
                                //int r = kesilecekLevha.size();
				for(unsigned int k = 0; k < kesilecekLevha.size(); k++){
                                        cevir = false;
                                        cevirme = false;
                                //int a = kesilecekLevha[k].getEn();
                                //int b = bottomBorder.front().getLenght();

					if( kesilecekLevha[k].getEn() < bottomBorder.front().getLenght()){	//levhanýn eni boþluða uygun mu

						//levhanýn boyu kaynak levhaya uygun mu
						if(kesilecekLevha[k].getBoy() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
		  		    		        index = k;
							cevirme = true;
						}
					}
                                  //      int z = kesilecekLevha[k].getBoy();
                                  //      int t = bottomBorder.front().getLenght();
                                  //      bool d = kesilecekLevha[k].getRotate();
					if(kesilecekLevha[k].getBoy() < bottomBorder.front().getLenght() && index < 0 && kesilecekLevha[k].getRotate() == true){   //levhanýn çevrilebilir olmasý gerekiyor.
						if(kesilecekLevha[k].getEn() + bottomBorder.front().getHeight() <= kaynakLevha[i].getBoy()){
							index = k;
							cevir = true;
						}
					}

					if(index > -1 ){			//boþluða eni veya boyu tam oturan levhalardan alaný en büyük olaný seç

						if(maxEn < 0 && cevirme == true){
							maxEn = kesilecekLevha[k].getEn();
							indexOfLevha = index;
                                                        index = -1;
                                                        rotate = false;
                                                        cevirme = false;
						}
						else if(maxEn < 0 && cevir == true){
							maxEn = kesilecekLevha[k].getBoy();
							indexOfLevha = index;
                                                        index = -1;
                                                        rotate = true;
                                                        cevir = false;
						}
						else if(kesilecekLevha[k].getEn() > maxEn && cevirme == true){		//max alaný bul
		    				        maxEn = kesilecekLevha[k].getEn();
							indexOfLevha = index;
                                                        index = -1;
                                                        rotate = false;
                                                        cevirme = false;
						}


						else if(kesilecekLevha[k].getBoy() > maxEn && cevir == true){
							maxEn = kesilecekLevha[k].getBoy();
				 	   		indexOfLevha = index;
                                                        index = -1;
                                                        rotate = true;
                                                        cevir = false;
						}
					}
				}


				if(maxEn > 0){	//maxEn > 0 ise boþluða yerleþebilen en büyük ene yada boya sahip levha bulunmuþtur

					kesilecekLevha[indexOfLevha].setLevha(i+1,rotate,bottomBorder.front().getXStart(),bottomBorder.front().getHeight());//levhanýn nereden kesileceðini belirle
					kesilmisLevha.push_back(kesilecekLevha[indexOfLevha]);		//kesilmiþ olana ekle



					for(unsigned int k = 0; k < bottomBorder.size(); k++){	//yeni sýnýra gerek olup oladýðý bulunuyor
                                                //KesilecekLevha p(0,0,true);
                                                //p = kesilecekLevha[indexOfLevha];
                                                //BottomBorder i = bottomBorder[k];
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
                                        BottomBorder r = bottomBorder.front();
					Sort::sortBorder(bottomBorder);		//sýrala
					kesilecekLevha.erase(kesilecekLevha.begin() + indexOfLevha);	//kesilmiþ olaný sil
					maxEn = -1;
					indexOfLevha = -1;
					continue;

				}







				if(maxAlan < 0 && maxEn < 0){                           //boþluða yerleþen bulunamadý,kullanýlmayan alan

					int indexLeft = -1,indexRight = -1;		//boþluðun sýnýrlarý
					for(unsigned int b = 1; b < bottomBorder.size(); b ++){

                                        //int h = bottomBorder.front().getXStart();

                                        //BottomBorder a(0,0,0);
                                        for(unsigned int u = 0; u < bottomBorder.size(); u++){
                                                //a = bottomBorder[u];
                                                //h = bottomBorder[u].getXStart();
                                        }

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
						if(bottomBorder.front().getHeight() + kesilecekLevha[b].getBoy() < kaynakLevha[i].getBoy()){
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

		}
	}
}

#endif
