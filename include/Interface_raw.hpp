#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/string.h>
#include <cstring>
#include <iostream>
#include <cstdlib>

class BackPanel:public wxPanel {
    wxBitmap image;
    wxBitmap image2;
public:
    BackPanel (wxFrame *parent, wxString file, wxBitmapType format, wxString file2);
    void paintEvent (wxPaintEvent &evt);
    void paintBack ();
    void setImage (wxDC &dc);
};

class CalcFrame:public wxFrame {//main frame
    //  Здесь используются указатели, для того, чтобы wx мог их потом спокойно
    // удалить. Указатели,  объявленные в функциях wx не удалаяет сам
    wxBoxSizer *main_sizer; //sizer for panel placement
    wxTextCtrl *screen_text;
    wxTextCtrl *prog_number [6][6];
    wxTextCtrl *prog_code [6][6];
    wxTextCtrl *reg_value [8];
    wxTextCtrl *rotate_reg_value [6]; 
    BackPanel *drawPane;
    wxButton* turn_button;
    wxBitmapButton* calc_button [31];
    bool turn_pressed = false;
    wxTextCtrl *number_scr; 
public:
    CalcFrame (const wxString &title);
    ~CalcFrame ();
    void ButtonClick (wxCommandEvent &event);
    void Click_turn (wxCommandEvent &event);
    void null_everything ();
    void init_everything ();
    void cursor_set (int cursor_position);
    void screen_set_values ();
};

std::string dec_to_six (int a);

//Индексы активных виждетов для связи с обработчиком,  событием и функцией
//все эти номера будут согласованы с теми, кто пишет мне обработчик
enum BUTTONS_ids {
    ID_BUT_PLUS = 1001,
    ID_BUT_MINUS,
    ID_BUT_MULT,
    ID_BUT_DELEN,
    ID_BUT_SWAP,
    ID_BUT_ARROWUP,
    ID_BUT_SIGN,
    ID_BUT_VP,
    ID_BUT_F,
    ID_BUT_NULL,
    ID_BUT_ONE,
    ID_BUT_TWO,
    ID_BUT_THREE,
    ID_BUT_FOUR,
    ID_BUT_FIVE,
    ID_BUT_SIX,
    ID_BUT_SEVEN,
    ID_BUT_EIGHT,
    ID_BUT_NINE,
    ID_BUT_POINT,
    ID_BUT_LSTEP,
    ID_BUT_RSTEP,
    ID_BUT_VO,
    ID_BUT_SP,
    ID_BUT_P,
    ID_BUT_DEG,
    ID_BUT_BP,
    ID_BUT_PP,
    ID_BUT_CX,
    ID_SCREEN,
    ID_BUT_TURN,
};

class CalcApp:public wxApp {//dont understand how this works
    CalcFrame *frame;
public:
    bool OnInit() {
        frame = new CalcFrame(wxT("БК-21"));
        frame->Show();
        SetTopWindow (frame);
        return true;
    }
    int OnExit() {
        return 0;
    }
};
