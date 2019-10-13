//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "veriGirisi.h"
#include "hesapCizim.h"
#include <fstream.h> //dosya i�lemleri i�in
using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TImage *img;
vector <TImage*> imgVector;
vector <KesilecekLevha> kesilmisLevha;
vector <AnsiString> yazVector;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//form2 kapat�ld���nda yap�lacaklar
void __fastcall TForm2::onClose(TObject *Sender, TCloseAction &Action)
{
        lblHata->Caption = "";
        kesilmisLevha.clear();
        yazVector.clear();

        Form1->txtTane->Text = "";
        Form1->txtEn->Text = "";
        Form1->txtBoy->Text = "";
        Form1->txtTane->SetFocus();
        Form1->ComboBox1->ItemIndex = 0;
        Form1->cmbTesterePayi->ItemIndex = 0;
        Form1->sifirlaClick(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TForm2::Load(TObject *Sender)
{
        sd->Filter = "Metin Dosyas� (*.txt)|*.txt|";
;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::onShow(TObject *Sender)
{
        unsigned int i;
        int testerePayi = Form1->cmbTesterePayi->ItemIndex+1;

        if(lblKac->Caption.ToInt() > 0) {       //ilk kez hesaplama yap�lm�yorsa
                for(i=0;i<imgVector.size();i++)
                        imgVector[i]->Destroying();  //daha �nceden �izdirilen image nesneleri yok edilir ki bellek temizlensin
                imgVector.clear();
        }
        vector <KesilecekLevha> kesilecekLevha;         //kesilecek levhalar vekt�r�
        vector <KaynakLevha> kaynakLevha;               //kaynak levhlalar vekt�r�
        vector <KesilecekLevha> kesilmisLevha;          //kesim i�lemi bitmi� levhalar vekt�r�
	vector <BottomBorder> bottomBorder;		//alt s�n�rlar vekt�r�

        float screenW = GetSystemMetrics(SM_CXSCREEN);  //bilgisayar�n mevcut ��z�n�rl���n�n eni
        //float screenH = GetSystemMetrics(SM_CYSCREEN);  //bilgisayar�n mevcut ��z�n�rl���n�n boyu

        float olcek = 0;        //�l�ekleme katsay�s�

        int tane=0,en=0,boy=0,row=0,toplam=1,temp=0;

        float x1=0,y1=0,x2=0,y2=0;     //koordinatlar


        tane = Form1->txtTane->Text.ToInt();
        en = Form1->txtEn->Text.ToInt();
        boy = Form1->txtBoy->Text.ToInt();
        toplam = Form1->lblRow->Caption.ToInt();


        for(row=1; row<toplam; row++) {
             for(int i=0; i<Form1->StringGrid1->Cells[0][row].ToInt(); i++) {    //1.s�tundaki tane kadar kesilecek levha eklenecek
                  KesilecekLevha temp(Form1->StringGrid1->Cells[1][row].ToInt()*10+testerePayi,Form1->StringGrid1->Cells[2][row].ToInt()*10+testerePayi);
                  temp.setSira(row);    //stringgrid e ka��nc� s�rada girildi�i
                  kesilecekLevha.push_back(temp);
            }
        }

        //kaynak levha i�in veriler bilgiler do�ru
        if(tane!=0 && en!=0 && boy!=0) {

                float w=screenW/2,h=screenW/2;
                KaynakLevha kl(en*10, boy*10);  //testere pay� i�in geni�let
                yazVector.push_back("Verilen Kaynak Levha eni: "+IntToStr(en*10)+" boyu: "+IntToStr(boy*10)+"\n\n");
                yazVector.push_back("Testere pay�: "+IntToStr(testerePayi)+"\n\n");

                olcek = min((float)h/kl.getEn(), (float)w/kl.getBoy());
                //�l�ek, olu�turulmu� image nesnelerinin en ve boyunun,kaynak levha en ve boyuna b�l�m�d�r
                int gelenEn = kl.getEn();
                int gelenBoy = kl.getBoy();
                //kaynak levhan�n en/boy oran�na g�re olu�turdu�umuz image nesnelerinin enini ve boyunu ayarlayaca��z
                if(gelenEn > gelenBoy)
                        h *= (float)gelenBoy/gelenEn;
                else if(gelenEn < gelenBoy)
                        w *= (float)gelenEn/gelenBoy;


                for(int i=0; i<tane; i++) {    //tane kadar kaynak levha olu�turulup image nesneleri ayarland�

                        kaynakLevha.push_back(kl);

                        img = new TImage(this);
                        img->Parent = this;
                        img->Stretch = false;
                        img->Width = w;         //image lar�n eni ve boyu mevcut ��z�n�rl���n eninin yar�s� olarak se�ildi
                        img->Height = h;        //duruma g�re �l�eklenen kaynak levhan�n oran�nda yeniden en/boy oran� belirlenmi� olacak
                        img->Top = 20;
                        img->Left = i*(10+screenW/2);
                        img->Canvas->Font->Color = clWhite;
                        //testere pays�z levha mavi olarak �izildi. arada kalan k�s�mlar testere pay�d�r,b�y�k beyazlar ise bo�luk
                        img->Canvas->Brush->Color = clBlue;

                        img->Visible = true;

                        imgVector.push_back(img);
                }

                Sort::sortProcedure(kesilecekLevha);		//levhalar� enleri k����e do�ru s�rala

                BottomBorder bBorder(0, kaynakLevha.front().getEn(), 0);	//ilk alt s�n�r kaynak levhan�n alt kenar�

                bottomBorder.push_back(bBorder);

                // levhalar� kes
                Placement levhaPlacement;
                levhaPlacement.placementPolicy(kesilecekLevha, kesilmisLevha, kaynakLevha, bottomBorder);
                //kesilmisLevha n�n i�ine gerekli de�erleri atanm�� kesilecek levhalar geldi
                //kesim i�lemi bitti

                lblKesilmis->Caption=IntToStr(kesilmisLevha.size());

                //kesilmi� levhalar� �izdiriyoruz
                for(i = 0; i < kesilmisLevha.size(); i++) {

                        //koordinatlar
                        x1 = (float) kesilmisLevha[i].getXStart();
                        y1 = (float) kesilmisLevha[i].getYStart();
                        x2 = (float) kesilmisLevha[i].getXEnd();
                        y2 = (float) kesilmisLevha[i].getYEnd();
                        //yerle�ti�i levha no
                        int levhaNo = kesilmisLevha[i].getLevhaNo();
                        //kesilecek levhalar klas�r�ne hangi s�rada girildi�i
                        int sirasi = kesilmisLevha[i].getSira();
                        int hei = kesilmisLevha[i].getBoy();
                        int wid = kesilmisLevha[i].getEn();

                        imgVector[levhaNo-1]->Canvas->Brush->Color = clBlue;
                        imgVector[levhaNo-1]->Canvas->Rectangle(olcek*(x1+testerePayi),olcek*(y1+testerePayi),olcek*(x2-testerePayi),olcek*(y2-testerePayi));

                        int x=0, y=0;
                        x=wid/10;
                        y=hei/10;
                        //ortalayabilmek i�in kesilmi� levhan�n eni ve boyunun 10de biri kadar i�erden ba�layan dikd�rtgen i�ine almal�y�z ki �st �ste binmesin ve yaz� ortalanabilsin
                        TRect TheRect(olcek*(x1+x),olcek*(y1+y),olcek*(x2-x),olcek*(y2-y));
                        imgVector[levhaNo-1]->Canvas->TextRect(TheRect,olcek*((x1+x2)/2),olcek*((y1+y2)/2),IntToStr(sirasi));
                        //�izilen levhalar�n i�ine kesilecek levhalar tablosuna ka��nc� s�rada girildi�i yaz�ld�

                        yazVector.push_back((IntToStr(i)+" no lu kesilmi� levha i�in x1: "+IntToStr((int)x1)+"\t y1: "+IntToStr((int)y1)+"\t x2: "+IntToStr((int)x2)+"\t y2: "+IntToStr((int)y2)+"\t Yerle�ti�i Levha no su: "+IntToStr(levhaNo)+"\n"));
                        //yazd�r�lmak istenirse gerekli bilgiler yazVector'de
                }
        }
        else
                lblHata->Caption="Bilgiler al�n�rken sorun olu�tu. Ge�ersiz giri�.";

        yazVector.push_back("\nKesilmemi� levhalar:\n");
        for(i=1;i<kesilecekLevha.size();i++)
                yazVector.push_back("en: "+IntToStr(kesilecekLevha[i].getEn())+" boy: "+IntToStr(kesilecekLevha[i].getBoy())+"\n");
        kaynakLevha.clear();
        kesilecekLevha.clear();
        bottomBorder.clear();

        //program a��ld���ndan beri ka� kere hesaplama/�izdirilme yap�ld�
        temp=lblKac->Caption.ToInt();
        temp++;
        lblKac->Caption = IntToStr(temp);
}
//---------------------------------------------------------------------------
//sonu�lar� kaydet men�s� t�kland�
void __fastcall TForm2::skClick(TObject *Sender)
{
        sd->Execute();

        fstream file_op(sd->FileName.c_str(),ios::out);
        for(unsigned int i=0; i<yazVector.size();i++)
                file_op<<yazVector[i].c_str();

        file_op.close();
        yazVector.clear();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

