//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "veriGirisi.h"
#include "hesapCizim.h"
#include <fstream.h> //dosya iþlemleri için
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


//form2 kapatýldýðýnda yapýlacaklar
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
        sd->Filter = "Metin Dosyasý (*.txt)|*.txt|";
;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::onShow(TObject *Sender)
{
        unsigned int i;
        int testerePayi = Form1->cmbTesterePayi->ItemIndex+1;

        if(lblKac->Caption.ToInt() > 0) {       //ilk kez hesaplama yapýlmýyorsa
                for(i=0;i<imgVector.size();i++)
                        imgVector[i]->Destroying();  //daha önceden çizdirilen image nesneleri yok edilir ki bellek temizlensin
                imgVector.clear();
        }
        vector <KesilecekLevha> kesilecekLevha;         //kesilecek levhalar vektörü
        vector <KaynakLevha> kaynakLevha;               //kaynak levhlalar vektörü
        vector <KesilecekLevha> kesilmisLevha;          //kesim iþlemi bitmiþ levhalar vektörü
	vector <BottomBorder> bottomBorder;		//alt sýnýrlar vektörü

        float screenW = GetSystemMetrics(SM_CXSCREEN);  //bilgisayarýn mevcut çözünürlüðünün eni
        //float screenH = GetSystemMetrics(SM_CYSCREEN);  //bilgisayarýn mevcut çözünürlüðünün boyu

        float olcek = 0;        //ölçekleme katsayýsý

        int tane=0,en=0,boy=0,row=0,toplam=1,temp=0;

        float x1=0,y1=0,x2=0,y2=0;     //koordinatlar


        tane = Form1->txtTane->Text.ToInt();
        en = Form1->txtEn->Text.ToInt();
        boy = Form1->txtBoy->Text.ToInt();
        toplam = Form1->lblRow->Caption.ToInt();


        for(row=1; row<toplam; row++) {
             for(int i=0; i<Form1->StringGrid1->Cells[0][row].ToInt(); i++) {    //1.sütundaki tane kadar kesilecek levha eklenecek
                  KesilecekLevha temp(Form1->StringGrid1->Cells[1][row].ToInt()*10+testerePayi,Form1->StringGrid1->Cells[2][row].ToInt()*10+testerePayi);
                  temp.setSira(row);    //stringgrid e kaçýncý sýrada girildiði
                  kesilecekLevha.push_back(temp);
            }
        }

        //kaynak levha için veriler bilgiler doðru
        if(tane!=0 && en!=0 && boy!=0) {

                float w=screenW/2,h=screenW/2;
                KaynakLevha kl(en*10, boy*10);  //testere payý için geniþlet
                yazVector.push_back("Verilen Kaynak Levha eni: "+IntToStr(en*10)+" boyu: "+IntToStr(boy*10)+"\n\n");
                yazVector.push_back("Testere payý: "+IntToStr(testerePayi)+"\n\n");

                olcek = min((float)h/kl.getEn(), (float)w/kl.getBoy());
                //ölçek, oluþturulmuþ image nesnelerinin en ve boyunun,kaynak levha en ve boyuna bölümüdür
                int gelenEn = kl.getEn();
                int gelenBoy = kl.getBoy();
                //kaynak levhanýn en/boy oranýna göre oluþturduðumuz image nesnelerinin enini ve boyunu ayarlayacaðýz
                if(gelenEn > gelenBoy)
                        h *= (float)gelenBoy/gelenEn;
                else if(gelenEn < gelenBoy)
                        w *= (float)gelenEn/gelenBoy;


                for(int i=0; i<tane; i++) {    //tane kadar kaynak levha oluþturulup image nesneleri ayarlandý

                        kaynakLevha.push_back(kl);

                        img = new TImage(this);
                        img->Parent = this;
                        img->Stretch = false;
                        img->Width = w;         //image larýn eni ve boyu mevcut çözünürlüðün eninin yarýsý olarak seçildi
                        img->Height = h;        //duruma göre ölçeklenen kaynak levhanýn oranýnda yeniden en/boy oraný belirlenmiþ olacak
                        img->Top = 20;
                        img->Left = i*(10+screenW/2);
                        img->Canvas->Font->Color = clWhite;
                        //testere paysýz levha mavi olarak çizildi. arada kalan kýsýmlar testere payýdýr,büyük beyazlar ise boþluk
                        img->Canvas->Brush->Color = clBlue;

                        img->Visible = true;

                        imgVector.push_back(img);
                }

                Sort::sortProcedure(kesilecekLevha);		//levhalarý enleri küçüðe doðru sýrala

                BottomBorder bBorder(0, kaynakLevha.front().getEn(), 0);	//ilk alt sýnýr kaynak levhanýn alt kenarý

                bottomBorder.push_back(bBorder);

                // levhalarý kes
                Placement levhaPlacement;
                levhaPlacement.placementPolicy(kesilecekLevha, kesilmisLevha, kaynakLevha, bottomBorder);
                //kesilmisLevha nýn içine gerekli deðerleri atanmýþ kesilecek levhalar geldi
                //kesim iþlemi bitti

                lblKesilmis->Caption=IntToStr(kesilmisLevha.size());

                //kesilmiþ levhalarý çizdiriyoruz
                for(i = 0; i < kesilmisLevha.size(); i++) {

                        //koordinatlar
                        x1 = (float) kesilmisLevha[i].getXStart();
                        y1 = (float) kesilmisLevha[i].getYStart();
                        x2 = (float) kesilmisLevha[i].getXEnd();
                        y2 = (float) kesilmisLevha[i].getYEnd();
                        //yerleþtiði levha no
                        int levhaNo = kesilmisLevha[i].getLevhaNo();
                        //kesilecek levhalar klasörüne hangi sýrada girildiði
                        int sirasi = kesilmisLevha[i].getSira();
                        int hei = kesilmisLevha[i].getBoy();
                        int wid = kesilmisLevha[i].getEn();

                        imgVector[levhaNo-1]->Canvas->Brush->Color = clBlue;
                        imgVector[levhaNo-1]->Canvas->Rectangle(olcek*(x1+testerePayi),olcek*(y1+testerePayi),olcek*(x2-testerePayi),olcek*(y2-testerePayi));

                        int x=0, y=0;
                        x=wid/10;
                        y=hei/10;
                        //ortalayabilmek için kesilmiþ levhanýn eni ve boyunun 10de biri kadar içerden baþlayan dikdörtgen içine almalýyýz ki üst üste binmesin ve yazý ortalanabilsin
                        TRect TheRect(olcek*(x1+x),olcek*(y1+y),olcek*(x2-x),olcek*(y2-y));
                        imgVector[levhaNo-1]->Canvas->TextRect(TheRect,olcek*((x1+x2)/2),olcek*((y1+y2)/2),IntToStr(sirasi));
                        //çizilen levhalarýn içine kesilecek levhalar tablosuna kaçýncý sýrada girildiði yazýldý

                        yazVector.push_back((IntToStr(i)+" no lu kesilmiþ levha için x1: "+IntToStr((int)x1)+"\t y1: "+IntToStr((int)y1)+"\t x2: "+IntToStr((int)x2)+"\t y2: "+IntToStr((int)y2)+"\t Yerleþtiði Levha no su: "+IntToStr(levhaNo)+"\n"));
                        //yazdýrýlmak istenirse gerekli bilgiler yazVector'de
                }
        }
        else
                lblHata->Caption="Bilgiler alýnýrken sorun oluþtu. Geçersiz giriþ.";

        yazVector.push_back("\nKesilmemiþ levhalar:\n");
        for(i=1;i<kesilecekLevha.size();i++)
                yazVector.push_back("en: "+IntToStr(kesilecekLevha[i].getEn())+" boy: "+IntToStr(kesilecekLevha[i].getBoy())+"\n");
        kaynakLevha.clear();
        kesilecekLevha.clear();
        bottomBorder.clear();

        //program açýldýðýndan beri kaç kere hesaplama/çizdirilme yapýldý
        temp=lblKac->Caption.ToInt();
        temp++;
        lblKac->Caption = IntToStr(temp);
}
//---------------------------------------------------------------------------
//sonuçlarý kaydet menüsü týklandý
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

