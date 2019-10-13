//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "veriGirisi.h"
#include "hesapCizim.h"
#include "hakkinda.h"
#include <fstream.h> //dosya iþlemleri için

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TPanel *pnl;
mehmetPanel *mpnl;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}



//---------------------------------------------------------------------------
//form1 yüklenirken yapýlacaklar
void __fastcall TForm1::Load(TObject *Sender)
{
        dosyadan = false;
        kesilecekLevhaSirasi = 1;
        kaynakLevhaSirasi = 1;

        dil = 0;
        turkce();

        cmbTesterePayi->Clear();
        for(int i=1;i<11;i++)
            cmbTesterePayi->AddItem(i,Sender);
        cmbTesterePayi->ItemIndex = 0;

}
//---------------------------------------------------------------------------
//verilen levhalarla kesim iþlemi yap dendiðinde yapýlacaklar
void __fastcall TForm1::kesClick(TObject *Sender)
{
        lblHata->Caption="";
        lblHata2->Caption="";
        if( (kaynakLevhaSirasi > 1) && (kesilecekLevhaSirasi > 1) )
                Form2->ShowModal();
        else
               lblHata->Caption = hataLevhaBos;


}
//---------------------------------------------------------------------------
//dil ingilizce seçilince yapýlacaklar
void __fastcall TForm1::EnglishClick(TObject *Sender)
{
        dil = 1;
        Form1->Caption = "Group 19 :: Project 2";
        eng();
}
//---------------------------------------------------------------------------

//menüden çýkýþ yap diyince yapýlacaklar
void __fastcall TForm1::CikisClick(TObject *Sender)
{
        Form1->Close();
}
//---------------------------------------------------------------------------
//dili türkçe seçince yapýlacaklar
void __fastcall TForm1::TurkceClick(TObject *Sender)
{
        dil = 0;
        Form1->Caption = "Grup 19 :: Proje 2";
        turkce();
}
//---------------------------------------------------------------------------
//uygulama hakkýnda bilgi al denince yapýlacaklar
void __fastcall TForm1::HakkindaClick(TObject *Sender)
{
        AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
//verilen deðerlere göre kesilecek levha ekle denilince yapýlacaklar
void __fastcall TForm1::ekleClick(TObject *Sender)
{
        lblHata2->Caption="";
        int row = kesilecekLevhaSirasi;
        if( (txtTane2->Text!= "") &&(txtEn2->Text != "") &&(txtBoy2->Text != "") )
        {
               lblHata2->Caption="";
               Is Is1;

               if( (Is1.Number(txtTane2->Text.c_str(), txtTane2->Text.Length())) && (Is1.Number(txtEn2->Text.c_str(), txtEn2->Text.Length())) && (Is1.Number(txtBoy2->Text.c_str(), txtBoy2->Text.Length())) )
               {
                   StringGrid1->Cells[0][row] = txtTane2->Text;
                   StringGrid1->Cells[1][row] = txtEn2->Text;
                   StringGrid1->Cells[2][row] = txtBoy2->Text;
                   StringGrid1->Cells[3][row] = BoolToStr(chk->Checked);
                   row++;
                   kesilecekLevhaSirasi = row;
                   txtTane2->Text = "";
                   txtEn2->Text = "";
                   txtBoy2->Text = "";
                   txtTane2->SetFocus();
               }
               else
                   lblHata2->Caption = hataSadeceSayi;
        }
        else
                lblHata2->Caption = hataKesilecekLevhaBos;

        chk->Checked = false;
}
//---------------------------------------------------------------------------
//kesilecek levha stringgrid ini boþaltmak için yapýlacaklar
void __fastcall TForm1::sifirlaClick(TObject *Sender)
{
    for(int row=1; row<kesilecekLevhaSirasi; row++) {
        StringGrid1->Cells[0][row] = "";
        StringGrid1->Cells[1][row] = "";
        StringGrid1->Cells[2][row] = "";
        StringGrid1->Cells[3][row] = "";
    }
    kesilecekLevhaSirasi = 1;
}

//---------------------------------------------------------------------------
//kaynak levha stringgrid ini boþaltmak için yapýlacaklar
void __fastcall TForm1::sifirla2Click(TObject *Sender)
{
    for(int row=1; row<kaynakLevhaSirasi; row++) {
        StringGrid2->Cells[0][row] = "";
        StringGrid2->Cells[1][row] = "";
        StringGrid2->Cells[2][row] = "";
    }
    kaynakLevhaSirasi = 1;
}
//---------------------------------------------------------------------------
//kaynak levha eklemesi
void __fastcall TForm1::ekle2Click(TObject *Sender)
{
        lblHata->Caption="";
        int row = kaynakLevhaSirasi;
        if( (txtTane->Text!= "") &&(txtEn->Text != "") &&(txtBoy->Text != "") )
        {
               lblHata->Caption="";
               Is Is1;

               if( (Is1.Number(txtTane->Text.c_str(), txtTane->Text.Length())) && (Is1.Number(txtEn->Text.c_str(), txtEn->Text.Length())) && (Is1.Number(txtBoy->Text.c_str(), txtBoy->Text.Length())) )
               {
                   StringGrid2->Cells[0][row] = txtTane->Text;
                   StringGrid2->Cells[1][row] = txtEn->Text;
                   StringGrid2->Cells[2][row] = txtBoy->Text;
                   row++;
                   kaynakLevhaSirasi = row;
                   txtTane->Text = "";
                   txtEn->Text = "";
                   txtBoy->Text = "";
                   txtTane->SetFocus();
               }
               else
                   lblHata->Caption = hataSadeceSayi;
        }
        else
                lblHata->Caption = hataKaynakLevhaBos;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Yardm1Click(TObject *Sender)
{
        //help dosyasý aç
        SHELLEXECUTEINFO ShellInfo; // Name structure
        memset(&ShellInfo, 0, sizeof(ShellInfo)); // Set up memory block
        ShellInfo.cbSize = sizeof(ShellInfo); // Set up structure size
        ShellInfo.hwnd = Handle; // Calling window handle
        ShellInfo.lpVerb = "open"; // Open the file with default program
        ShellInfo.lpFile = "yardim.chm"; // File to open
        ShellInfo.nShow = SW_NORMAL; // Open in normal window
        ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS; // Necessary if you want to wait for spawned process
        bool res = ShellExecuteEx(&ShellInfo); // Call to function
        //kaynak: http://www.tek-tips.com/viewthread.cfm?qid=604994
}
//---------------------------------------------------------------------------

void __fastcall TForm1::dosyaacClick(TObject *Sender)
{
            //eðer ki daha önceden dosyadan okunmuþ ve oluþturulmuþ paneller varsa temizle
            for(unsigned int i=0; i<panelKesilmis.size(); i++)
                 panelKesilmis[i]->Free();
            for(unsigned int i=0; i<panelVector.size(); i++)
                 panelVector[i]->Free();

            panelVector.clear();
            panelKesilmis.clear();

            dosyadan = true;
            od->Filter = "Grup19 Dosyasý (*.g19)|*.g19|";
            od->Execute();

            fstream file_op(od->FileName.c_str(),ios::in);

            file_op.getline(str,10);
            int count1 = StrToInt((AnsiString)str);
            
            for(int i=0; i<count1;i++){
                pnl = new TPanel(this);
                pnl->Parent = this;
                file_op.getline(str,10);
                pnl->Width = StrToInt((AnsiString)str);
                file_op.getline(str,10);                                                 //panellerin eni ve boyu mevcut çözünürlüðün eninin yarýsý olarak seçildi
                pnl->Height = StrToInt((AnsiString)str);                                //duruma göre ölçeklenen kaynak levhanýn oranýnda yeniden en/boy oraný belirlenmiþ olacak
                pnl->Top = 10;
                file_op.getline(str,10);
                pnl->Left = StrToInt((AnsiString)str);
                pnl->Color = clWhite;
               /* pnl->OnDragOver = myDragOver;
                pnl->OnDragDrop = myDragDrop;*/
                pnl->Visible = false;
                panelVector.push_back(pnl);
            }
            file_op.getline(str,10);
            int count2 = StrToInt((AnsiString)str);
            int levhaNo,rotate;
            bool rotate1;

            for(int l=0; l<count2;l++){
                file_op.getline(str,10);
                levhaNo = StrToInt((AnsiString)str);
                file_op.getline(str,10);
                rotate = StrToInt((AnsiString)str);
                if(rotate == 0)
                        rotate1 = false;
                else
                        rotate1 = true;

                mpnl = new mehmetPanel(this, 0, levhaNo, rotate1 );

                file_op.getline(str,10);
                 mpnl->Width = StrToInt((AnsiString)str);

                file_op.getline(str,10);
                mpnl->Height = StrToInt((AnsiString)str);

                file_op.getline(str,10);
                mpnl->Top = StrToInt((AnsiString)str);

                file_op.getline(str,10);
                mpnl->Left = StrToInt((AnsiString)str);

                file_op.getline(str,10);
                mpnl->Caption = StrToInt((AnsiString)str);
                /*mpnl->Color = clBlue;
                mpnl->DragMode = dmAutomatic;
                mpnl->PopupMenu = popUpMenu;*/
                mpnl->Visible = false;
                panelKesilmis.push_back(mpnl);

            }
            Form2->ShowModal();

}
//---------------------------------------------------------------------------

