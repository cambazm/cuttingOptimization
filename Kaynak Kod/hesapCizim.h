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
        TMainMenu *MainMenu1;
        TMenuItem *islem;
        TMenuItem *sk;
        TSaveDialog *sd;
        TPopupMenu *popUpMenu;
        TMenuItem *kes;
        TMenuItem *cevir;
        TScrollBox *clipBoard;
        TScrollBox *kaynakAlani;
        void __fastcall onClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Load(TObject *Sender);
        void __fastcall onShow(TObject *Sender);
        void __fastcall skClick(TObject *Sender);
        void __fastcall kesClick(TObject *Sender);
        void __fastcall cevirClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int testerePayi;
        float olcek;
        int kac;
        int kesilmis;
        float screenW;
        float screenH;
        int clipBoardSolSeviye;
        __fastcall TForm2(TComponent* Owner);
        virtual void __fastcall myDragOver(TObject *Sender,
                                           TObject *Source,
                                           int X,
                                           int Y,
                                           TDragState State,
                                           bool &Accept);
        virtual void __fastcall myDragDrop(TObject *Sender,
                                           TObject *Source,
                                           int X,
                                           int Y);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
class mehmetPanel : public TPanel
{
private:

public:
        mehmetPanel( TComponent *Owner, int index1, int levhaNo1, bool rotate1  ): TPanel ( Owner ) { index = index1; levhaNo = levhaNo1; rotate = rotate1;}
        int index;
        int levhaNo;
        bool rotate;

};
#endif
