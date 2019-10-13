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
TPanel *pnl;
mehmetPanel *mpnl;
vector <TPanel*> pnlVector;
vector <KesilecekLevha> kesilmisLevha;
vector <AnsiString> yazVector;
vector <mehmetPanel*> pnlKesilmis;  //burdan kaydedip geri döncez

//vector <KesilecekLevha> kesilmisLevha;          //kesim iþlemi bitmiþ levhalar vektörü
vector <KaynakLevha> kaynakLevha;               //kaynak levhlalar vektörü

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
kac=0;
}
//---------------------------------------------------------------------------


//form2 kapatýldýðýnda yapýlacaklar
void __fastcall TForm2::onClose(TObject *Sender, TCloseAction &Action)
{
        testerePayi = 0;
        lblHata->Caption = "";
        if(Form1->dosyadan == false) {
                kesilmisLevha.clear();
                kaynakLevha.clear();
        }
        //daha önce dosyadan çizdirilmiþ panelleri formdan temizle
        for(unsigned int i=0;i<pnlKesilmis.size();i++)
                pnlKesilmis[i]->Free();
        for(unsigned int i=0;i<pnlVector.size();i++)
                pnlVector[i]->Free();  //daha önceden çizdirilen panel nesneleri yok edilir ki bellek ve form temizlensin
                
        yazVector.clear();
        clipBoardSolSeviye = 10;

        Form1->txtTane->Text = "";
        Form1->txtEn->Text = "";
        Form1->txtBoy->Text = "";
        Form1->txtTane->SetFocus();
        Form1->chk->Checked = false;
        Form1->cmbTesterePayi->ItemIndex = 0;
        Form1->sifirlaClick(Sender);
        Form1->sifirla2Click(Sender);

        //dosyadan okuma yapýlmýþsa eski haline getir
        if(Form1->dosyadan == true)
                Form1->dosyadan = false;


}
//---------------------------------------------------------------------------


void __fastcall TForm2::Load(TObject *Sender)
{
        kac = 0;
        screenW = GetSystemMetrics(SM_CXSCREEN);  //bilgisayarýn mevcut çözünürlüðünün eni
        screenH = GetSystemMetrics(SM_CYSCREEN);  //bilgisayarýn mevcut çözünürlüðünün boyu

        clipBoard->Left = 10;
        clipBoard->Width = screenW-30;
        clipBoard->Top = screenH/2+145;

        kaynakAlani->Left = 0;
        kaynakAlani->Top = 0;
        kaynakAlani->Width = screenW-30;
        kaynakAlani->Height = clipBoard->Top-30;


        lblHata->Left = 10;
        lblHata->Top = clipBoard->Top-10;
        clipBoardSolSeviye = 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::onShow(TObject *Sender)
{

        if(Form1->dil == 0) {
            sd->Filter = "Grup19 Dosyasý (*.g19)|*.g19|";
            islem->Caption = "Ýþlem";
            sk->Caption = "Sonuçlarý Kaydet";
            Form2->Caption = "Kesim Sonucu";
        }
        else {
            sd->Filter = "Group19 File (*.g19)|*.g19|";
            islem->Caption = "Operation";
            sk->Caption = "Save Results";
            Form2->Caption = "Cut Result";
        }

        if(kac > 0) {       //ilk kez çizim veya hesaplama yapýlmýyorsa
 /*               for(unsigned int i=0;i<pnlKesilmis.size();i++)
                        pnlKesilmis[i]->Free();
                for(unsigned int i=0;i<pnlVector.size();i++)
                        pnlVector[i]->Free();
                //daha önceden çizdirilen panel nesneleri yok edilir ki bellek ve form temizlensin
*/
                pnlVector.clear();
                pnlKesilmis.clear();
        }


        //dosyadan okunmuyorsa, yani hesap yapýlacaksa
        if(Form1->dosyadan == false) {

        bool cevrilebilir=true;
        unsigned int i;
        testerePayi = Form1->cmbTesterePayi->ItemIndex+1;

        vector <KesilecekLevha> kesilecekLevha;         //kesilecek levhalar vektörü
        vector <KesilecekLevha> kesilemezLevha;         //kenarlarý kaynak levhadan daha büyük
	vector <BottomBorder> bottomBorder;		//alt sýnýrlar vektörü

        olcek = 0;        //ölçekleme katsayýsý

        int row=0;

        float x1=0,y1=0,x2=0,y2=0;     //koordinatlar


        for(row=1; row<Form1->kaynakLevhaSirasi; row++) {
             for(int i=0; i<Form1->StringGrid2->Cells[0][row].ToInt(); i++) {    //1.sütundaki tane kadar kaynak levha eklenecek
                  KaynakLevha tempKaynak(Form1->StringGrid2->Cells[1][row].ToInt()*10,Form1->StringGrid2->Cells[2][row].ToInt()*10);
                  tempKaynak.setSira(row);    //stringgrid e kaçýncý sýrada girildiði
                  kaynakLevha.push_back(tempKaynak);
            }
        }



        for(row=1; row<Form1->kesilecekLevhaSirasi; row++) {
             for(int i=0; i<Form1->StringGrid1->Cells[0][row].ToInt(); i++) {    //1.sütundaki tane kadar kesilecek levha eklenecek
                  if(Form1->StringGrid1->Cells[3][row].ToInt()==-1)
                        cevrilebilir=false;
                  else
                        cevrilebilir=true;

                  KesilecekLevha temp(Form1->StringGrid1->Cells[1][row].ToInt()*10+2*testerePayi,Form1->StringGrid1->Cells[2][row].ToInt()*10+2*testerePayi,cevrilebilir);
                  temp.setSira(row);    //stringgrid e kaçýncý sýrada girildiði
                  kesilecekLevha.push_back(temp);
            }
        }
        Sort::sortProcedure(kaynakLevha);
        //veriler bilgiler doðru mu
        if( (kaynakLevha.size() > 0) && (kesilecekLevha.size() > 0) ) {

                for(unsigned int i=0; i<kaynakLevha.size(); i++) {    //girildiði kadar kaynak levha oluþturulup image nesneleri ayarlandý

                        float w=screenW/2,h=screenW/2;

                        int gelenEn = kaynakLevha[i].getEn();
                        int gelenBoy = kaynakLevha[i].getBoy();

                        olcek = min((float)h/gelenEn, (float)w/gelenBoy);
                        //ölçek, oluþturulmuþ image nesnelerinin en ve boyunun,kaynak levha en ve boyuna bölümüdür

                        //kaynak levhanýn en/boy oranýna göre oluþturduðumuz image nesnelerinin enini ve boyunu ayarlayacaðýz
                        if(gelenEn > gelenBoy)
                                h *= (float)gelenBoy/gelenEn;
                        else if(gelenEn < gelenBoy)
                                w *= (float)gelenEn/gelenBoy;

                        pnl = new TPanel(this);
                        pnl->Parent = kaynakAlani;
                        pnl->Width = w;         //panellerin eni ve boyu mevcut çözünürlüðün eninin yarýsý olarak seçildi
                        pnl->Height = h;        //duruma göre ölçeklenen kaynak levhanýn oranýnda yeniden en/boy oraný belirlenmiþ olacak
                        pnl->Top = 10;
                        pnl->Left = i*(10+(float)(screenW/2));
                        pnl->Color = clWhite;
                        pnl->OnDragOver = myDragOver;
                        pnl->OnDragDrop = myDragDrop;
                        pnl->Visible = true;

                        pnlVector.push_back(pnl);


                }

                Sort::sortProcedure(kesilecekLevha);		//levhalarý enleri küçüðe doðru sýrala

                BottomBorder bBorder(0, kaynakLevha.front().getEn(), 0);	//ilk alt sýnýr kaynak levhanýn alt kenarý

                bottomBorder.push_back(bBorder);

                // levhalarý kes
                Placement levhaPlacement;
                levhaPlacement.placementPolicy(kesilecekLevha, kesilmisLevha,kesilemezLevha, kaynakLevha, bottomBorder, testerePayi);
                //kesilmisLevha nýn içine gerekli deðerleri atanmýþ kesilecek levhalar geldi
                //kesim iþlemi bitti

                kesilmis = kesilmisLevha.size();

                //kesilmiþ levhalarý çizdiriyoruz
                for(i = 0; i < kesilmisLevha.size(); i++) {

                        //koordinatlar
                        x1 = (float) kesilmisLevha[i].getXStart();
                        y1 = (float) kesilmisLevha[i].getYStart();
                        //x2 = (float) kesilmisLevha[i].getXEnd();
                        //y2 = (float) kesilmisLevha[i].getYEnd();
                        //yerleþtiði levha no
                        int levhaNo = kesilmisLevha[i].getLevhaNo();
                        //kesilecek levhalar klasörüne hangi sýrada girildiði
                        int sirasi = kesilmisLevha[i].getSira();
                        int hei = kesilmisLevha[i].getBoy();
                        int wid = kesilmisLevha[i].getEn();
                        bool rotate1 = kesilmisLevha[i].getRotate();

                        mpnl = new mehmetPanel(this, i, levhaNo, rotate1 );
                        if(levhaNo == 0)
                                mpnl->Parent = pnlVector[levhaNo];
                        else
                                mpnl->Parent = pnlVector[levhaNo - 1];

                        mpnl->Width = (float)olcek*(wid-2*testerePayi);
                        mpnl->Height = (float)olcek*(hei-2*testerePayi);
                        mpnl->Top = olcek*(y1+testerePayi);
                        mpnl->Left = olcek*(x1+testerePayi);
                        mpnl->Caption = IntToStr(sirasi);
                        mpnl->Color = clBlue;
                        mpnl->DragMode = dmAutomatic;
                        mpnl->PopupMenu = popUpMenu;
                        mpnl->Visible = true;


                        pnlKesilmis.push_back(mpnl);
                }
        }
        else
                lblHata->Caption="Bilgiler alýnýrken sorun oluþtu. Geçersiz giriþ.";


        kesilecekLevha.clear();
        bottomBorder.clear();
        }
        //dosyadan mevcut düzen yüklenecek
        else if(Form1->dosyadan == true){

                for(unsigned int i=0; i<Form1->panelVector.size(); i++){

                        pnl = new TPanel(this);
                        pnl->Parent = kaynakAlani;
                        pnl->Width = Form1->panelVector[i]->Width;         //panellerin eni ve boyu mevcut çözünürlüðün eninin yarýsý olarak seçildi
                        pnl->Height = Form1->panelVector[i]->Height;        //duruma göre ölçeklenen kaynak levhanýn oranýnda yeniden en/boy oraný belirlenmiþ olacak
                        pnl->Top = 10;
                        pnl->Left = Form1->panelVector[i]->Left;
                        pnl->Color = clWhite;

                        pnl->OnDragOver = myDragOver;
                        pnl->OnDragDrop = myDragDrop;

                        pnl->Visible = true;
                        pnlVector.push_back(pnl);
                }
                for(unsigned int i=0; i<Form1->panelKesilmis.size(); i++){

                        int newi = Form1->panelKesilmis[i]->index;
                        bool rotate1 = Form1->panelKesilmis[i]->rotate;
                        int levhaNo = Form1->panelKesilmis[i]->levhaNo;
                        mpnl = new mehmetPanel(this, newi, levhaNo, rotate1 );
                        if(Form1->panelKesilmis[i]->levhaNo == 0)
                                mpnl->Parent = pnlVector[levhaNo];
                        else
                                mpnl->Parent = pnlVector[levhaNo - 1];

                        mpnl->Width = Form1->panelKesilmis[i]->Width;
                        mpnl->Height = Form1->panelKesilmis[i]->Height;
                        mpnl->Top = Form1->panelKesilmis[i]->Top;
                        mpnl->Left = Form1->panelKesilmis[i]->Left;
                        mpnl->Caption = Form1->panelKesilmis[i]->Caption;
                        mpnl->Color = clBlue;
                        mpnl->Visible = true;
                        mpnl->DragMode = dmAutomatic;
                        mpnl->PopupMenu = popUpMenu;
                        pnlKesilmis.push_back(mpnl);
                }
        }

        //program açýldýðýndan beri kaç kere hesaplama/çizdirilme yapýldý
        kac++;
}
//---------------------------------------------------------------------------
//sonuçlarý kaydet menüsü týklandý
void __fastcall TForm2::skClick(TObject *Sender)
{
        yazVector.clear();
        //kaynak levhalarý ekle
        yazVector.push_back(IntToStr((int)pnlVector.size())+"\n");
        for(unsigned int i=0;i<pnlVector.size();i++)
                yazVector.push_back(IntToStr((int)pnlVector[i]->Width)+"\n"+IntToStr((int)pnlVector[i]->Height)+"\n"+IntToStr((int)pnlVector[i]->Left)+"\n");

        //kesilmiþ levhalarý ekle
        yazVector.push_back(IntToStr((int)pnlKesilmis.size())+"\n");    //kac tane kesilmiþ levha var
        for(unsigned int i=0;i<pnlKesilmis.size();i++)
                yazVector.push_back(IntToStr((int)pnlKesilmis[i]->levhaNo)+"\n"+BoolToStr((bool)pnlKesilmis[i]->rotate)+"\n"+IntToStr((int)pnlKesilmis[i]->Width)+"\n"+IntToStr((int)pnlKesilmis[i]->Height)+"\n"+
                        IntToStr((int)pnlKesilmis[i]->Top)+"\n"+IntToStr((int)pnlKesilmis[i]->Left)+"\n"+ pnlKesilmis[i]->Caption +"\n");

        //kullanýcýdan dosya ismi al
        sd->Execute();

        fstream file_op(sd->FileName.c_str(),ios::out);
        for(unsigned int i=0; i<yazVector.size();i++)
                file_op<<yazVector[i].c_str();

        file_op.close();
        
}
//---------------------------------------------------------------------------
//kaynak levhalardan biri üzerinde kesilmiþ bir levha clipBoard a alýnmak için "kes" e basýldý
void __fastcall TForm2::kesClick(TObject *Sender)
{
                mehmetPanel *hede = (mehmetPanel*)popUpMenu->PopupComponent;    //kes iþlemi yapýlan panel (levha)

                //kaynak levha üzerindeyse clipBoard a taþý
                if(hede->Parent != clipBoard ) {
                        hede->Parent = clipBoard;

                        hede->Top = 10;
                        hede->Left = clipBoardSolSeviye;

                        clipBoardSolSeviye += max(hede->Width+testerePayi,hede->Height+testerePayi)+10;
                        //çevirildiði zaman baþka bir levhanýn üzerini kapamamasý için eni ve boyundan büyük olaný kadar alan býrakýlýr
                        //mesela 3 5 levhasý konuldu, çevrilmek istendiðinde saðýndaki sol seviye 2 artacak
                        //bundan dolayý bu 2 payý en baþta veriyoruz ki çevrildiðinde levhalar birbirlerinin üzerine gelmesin
                        //kýsaca çevrilme payý býrakýyoruz,
                        //aþaðý doðru uzarsa sorun yok ama sol tarafa doðru uzayýnca sorun olabilir diye böyle bir çözüm gerekli
                }


}
//---------------------------------------------------------------------------
//clipBoard'ta bir levhaya "çevir" e basýldý
void __fastcall TForm2::cevirClick(TObject *Sender)
{
                mehmetPanel *hede = (mehmetPanel*)popUpMenu->PopupComponent;    //"çevir" e basýlan panel (levha)
                int index = hede->index;        //kaçýncý kesilmiþ Levha

                if(hede->Parent == clipBoard ) {
                        bool c;
                        if(Form1->dosyadan == false)
                                c = kesilmisLevha[index].getRotate();
                        else
                                c = hede->rotate;

                        //çevrilebilirse çevir
                        if(c == true) {
                                int temp = hede->Width;
                                hede->Width = hede->Height;
                                hede->Height = temp;
                                if(Form1->dosyadan == false)
                                        kesilmisLevha[index].cevir();
                        }
                }

}
//---------------------------------------------------------------------------
//sürüklenen nesne býrakýldý
void __fastcall TForm2::myDragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
        mehmetPanel *suruklenen = (mehmetPanel*)Source;
        TPanel *kaynak = (TPanel*)Sender;
        TPoint solUst, sagAlt, temp;
        bool nesneVar = false;

        int h = kaynak->Height;
        int w = kaynak->Width;

        solUst.x = X-testerePayi;
        solUst.y = Y-testerePayi;
        sagAlt.x = X+suruklenen->Width+testerePayi;
        sagAlt.y = Y+suruklenen->Height+testerePayi;



        //sürüklenen levhanýn býrakýldýðý yerde herhangi bir kesilmis levha yoksa býrakýlabilir
        for(int i=solUst.x; i<=sagAlt.x; i++)
        {
            temp.x=i;
            for(int j=solUst.y; j<=sagAlt.y; j++)
            {
                temp.y=j;
                if(kaynak->ControlAtPos(temp, false, true)!=NULL){   //bakýlan noktada bir kontrol (form nesnesi var mý)
                    nesneVar=true;
                    break;
                }

            }
            if(nesneVar)
                break;
        }

        /* sadece kendi kaynak levhasý üzerinde bir yere koyulabilir
          kaynak levha sýnýrlarý dýþýna koyulamaz
          koyulduðu yerde bir nesne ile hiç bir þekilde çakýþamaz
        */
        if(solUst.x>0 && solUst.y>0 && sagAlt.x<w && sagAlt.y<h && nesneVar==false && kaynak==suruklenen->Parent) {

                if(Sender == kaynak) { //sadece kendi kaynak levhasýnda bir yere gelebilir
                        suruklenen->Left=X;
                        suruklenen->Top=Y;
                }
        }
        else if(solUst.x>0 && solUst.y>0 && sagAlt.x<w && sagAlt.y<h && nesneVar==false && suruklenen->Parent==clipBoard) { //clipBoard tan sürükleniyorsa parent ý gittiði yer olacak
                suruklenen->Parent = kaynak;
                for(unsigned int i=0; i<pnlVector.size(); i++) {
                        if(kaynak==pnlVector[i])
                                suruklenen->levhaNo = i+1;
                }
                suruklenen->Left=X;
                suruklenen->Top=Y;
        }
}
//---------------------------------------------------------------------------
//sürüklenen nesnenin nerelere sürüklenebileceði
void __fastcall TForm2::myDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
        Accept=true;    //kaynak levhalar üzerinde sürüklenebilecek
}

