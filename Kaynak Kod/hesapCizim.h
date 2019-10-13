//---------------------------------------------------------------------------

#ifndef hesapCizimH
#define hesapCizimH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblHata;
        TLabel *lblKac;
        TMainMenu *MainMenu1;
        TMenuItem *islem;
        TMenuItem *sk;
        TSaveDialog *sd;
        TLabel *lblKesilmis;
        void __fastcall onClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Load(TObject *Sender);
        void __fastcall onShow(TObject *Sender);
        void __fastcall skClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
