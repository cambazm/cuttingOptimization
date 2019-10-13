//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "hakkinda.h"
#include "veriGirisi.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
        AboutBox->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::OnShow(TObject *Sender)
{
        if(Form1->dil == 0) {
            ProductName->Caption = "Bilgisayar Proje 1 Dersi";
            OKButton->Caption = "Tamam";
            Label3->Caption = "2. Proje - Grup 19";
        }
        else {
            ProductName->Caption = "Computer Project 1 Lesson";
            OKButton->Caption = "OK";
            Label3->Caption = "2. Project - Group 19";
        }
}
//---------------------------------------------------------------------------


