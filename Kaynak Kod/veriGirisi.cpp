//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "veriGirisi.h"
#include "hesapCizim.h"
#include "hakkinda.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}



//---------------------------------------------------------------------------

//form1 yüklenirken yapýlacaklar
void __fastcall TForm1::Load(TObject *Sender)
{
        StringGrid1->Cells[0][0] = "Kaç Tane";
        StringGrid1->Cells[1][0] = "En";
        StringGrid1->Cells[2][0] = "Boy";
        StringGrid1->Cells[3][0] = "Çevrilebilirlik";
        StringGrid1->ColWidths[0] = 69;
        StringGrid1->ColWidths[1] = 50;
        StringGrid1->ColWidths[2] = 50;
        StringGrid1->ColWidths[3] = 95;

        GroupBox1->Caption = "Kaynak Levhalar";
        GroupBox2->Caption = "Kesilecek Levhalar";
        lblKac->Caption = "Kaç Tane";
        lblEn->Caption = "En";
        lblBoy->Caption = "Boy";

        ekle->Caption = "Ekle";
        kes->Caption = "Kes";

        Ayarlar->Caption = "Ayarlar";
        Cikis->Caption = "Çýkýþ";
        Yardim->Caption = "Yardým";
        Dil->Caption = "Language";
        Hakkinda->Caption = "Hakkýnda";

        ComboBox1->Clear();
        ComboBox1->AddItem("Fark Etmez",Sender);
        ComboBox1->AddItem("Dik",Sender);
        ComboBox1->AddItem("Yatay",Sender);
        ComboBox1->ItemIndex = 0;
        
        cmbTesterePayi->Clear();
        for(int i=1;i<10;i++)
            cmbTesterePayi->AddItem(i,Sender);
        cmbTesterePayi->ItemIndex = 0;

}
//---------------------------------------------------------------------------

//verilen levhalarla kesim iþlemi yap dendiðinde yapýlacaklar
void __fastcall TForm1::kesClick(TObject *Sender)
{
        lblHata->Caption="";
        if((txtEn->Text != "")&&(txtEn->Text != "")&&(txtBoy->Text != "")) {
                Is Is1;
                if(lblRow->Caption.ToInt() > 1) {

                        if( (Is1.Number(txtTane->Text.c_str(), txtTane->Text.Length())) && (Is1.Number(txtEn->Text.c_str(), txtEn->Text.Length())) && (Is1.Number(txtBoy->Text.c_str(), txtBoy->Text.Length())) )
                                Form2->ShowModal();
                        else
                                lblHata->Caption = "HATA: Sadece sayýlar girilebilir";
                }
                else
                         lblHata->Caption = "HATA: Kesilecek Levha alanlarý boþ býrakýlamaz";
        }
        else
                lblHata->Caption = "HATA: Kaynak Levha alanlarý boþ býrakýlamaz";

}
//---------------------------------------------------------------------------

//dil ingilizce seçilince yapýlacaklar
void __fastcall TForm1::EnglishClick(TObject *Sender)
{
        GroupBox1->Caption = "Base tablet";
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
        kes->Caption = "Cut";
        sifirla->Caption = "Reset";

        StringGrid1->Cells[0][0] = "How Many";
        StringGrid1->Cells[1][0] = "Width";
        StringGrid1->Cells[2][0] = "Length";
        StringGrid1->Cells[3][0] = "Turnability";

        Ayarlar->Caption = "Settings";
        Form2->islem->Caption = "Operation";
        Form2->sk->Caption = "Save Results";
        Cikis->Caption = "Exit";
        Yardim->Caption = "Help";
        Dil->Caption = "Dil";
        Hakkinda->Caption = "About";

        ComboBox1->Clear();
        ComboBox1->AddItem("Not Matter",Sender);
        ComboBox1->AddItem("Perpendicular",Sender);
        ComboBox1->AddItem("Horizontal",Sender);

}
//---------------------------------------------------------------------------

//menüden çýkýþ yap diyince yapýlacaklar
void __fastcall TForm1::CikisClick(TObject *Sender)
{
        Form1->Close();
}
//---------------------------------------------------------------------------

//dil türkçe seçince yapýlacaklar
void __fastcall TForm1::TurkceClick(TObject *Sender)
{
        Form1->Load(Sender);
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
        int row = lblRow->Caption.ToInt();
        if( (txtTane2->Text!= "") &&(txtEn2->Text != "") &&(txtBoy2->Text != "") &&(ComboBox1->ItemIndex != -1) )
        {
               lblHata2->Caption="";
               Is Is1;

               if( (Is1.Number(txtTane2->Text.c_str(), txtTane2->Text.Length())) && (Is1.Number(txtEn2->Text.c_str(), txtEn2->Text.Length())) && (Is1.Number(txtBoy2->Text.c_str(), txtBoy2->Text.Length())) )
               {
                   StringGrid1->Cells[0][row] = txtTane2->Text;
                   StringGrid1->Cells[1][row] = txtEn2->Text;
                   StringGrid1->Cells[2][row] = txtBoy2->Text;
                   StringGrid1->Cells[3][row] = ComboBox1->ItemIndex;
                   row++;
                   lblRow->Caption = row;
                   txtTane2->Text = "";
                   txtEn2->Text = "";
                   txtBoy2->Text = "";
                   txtTane2->SetFocus();
               }
               else
                   lblHata2->Caption = "HATA: Sadece sayýlar girilebilir";
        }
        else
                lblHata2->Caption = "HATA: Kesilecek Levha bilgilerinin eksik verilemez";

        ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

//stringgrid i boþaltmak için yapýlacaklar
void __fastcall TForm1::sifirlaClick(TObject *Sender)
{
    int toplam = lblRow->Caption.ToInt();
    for(int row=1; row<toplam; row++) {
        StringGrid1->Cells[0][row] = "";
        StringGrid1->Cells[1][row] = "";
        StringGrid1->Cells[2][row] = "";
        StringGrid1->Cells[3][row] = "";
    }
    lblRow->Caption = IntToStr(1);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

