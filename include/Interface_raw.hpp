#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/string.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "memory.hpp"

namespace ussr {

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
    wxBoxSizer *main_sizer; 
    wxTextCtrl *screen_text;
    std::array <wxTextCtrl*, 36> prog_number;
    std::array <wxTextCtrl*, 36> prog_code;
    std::array <wxTextCtrl*, 14> reg_value;
    BackPanel *drawPane;
    wxButton* turn_button;
    std::array <wxBitmapButton*, 31> Calc_buttons;
    bool turn_pressed = false;
    wxTextCtrl *number_scr; 
public:
    CalcFrame (const wxString &title);
    ~CalcFrame ();
    void ButtonClick (wxCommandEvent &event);
    void Click_turn (wxCommandEvent &event);
    //void Create_button (BackPanel drawPane, const int button_id, const std::string pict_name, const int x, const int y, int n);
    void null_everything ();
    void init_everything ();
    void cursor_set (int cursor_position);
    void screen_set_values ();
    void cursor_delete_null ();
    std::string value_convert ();
    std::string dec_to_six (int a);
};

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

/*std::array <const wxString, 3> pict_names {
    "Calc_pict/plus.png",
    "Calc_pict/minus.png", 
    "Calc_pict/mult.png"
};*/

class CalcApp:public wxApp {//dont understand how this works
    CalcFrame *frame;
public:
    bool OnInit(); 
    int OnExit();
};

} //namespace end