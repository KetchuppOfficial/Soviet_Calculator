#include <array>
#include <utility>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/string.h>

#include "calculator.hpp"

namespace ussr
{

class BackPanel : public wxPanel
{
    wxBitmap image;
    wxBitmap image2;

public:

    BackPanel (wxFrame *parent, wxString file, wxBitmapType format, wxString file2);
    void paintEvent (wxPaintEvent &evt);
    void paintBack ();
    void setImage (wxDC &dc);
};

class CalcFrame : public wxFrame
{
    std::array <std::pair<wxTextCtrl *, wxTextCtrl *>, 36> prog_;
    // first subarray used to be called prog_number
    // second subarray used to be called prog_code
    std::array <wxTextCtrl*, 14> reg_value;
    std::array <wxBitmapButton*, 31> Calc_buttons;

    BackPanel *drawPane;

    wxBoxSizer *main_sizer;
    wxTextCtrl *screen_text;
    wxTextCtrl *number_scr;
    wxButton* turn_button;

    bool turn_pressed = false;

public:

    CalcFrame (const wxString &title);
    ~CalcFrame ();

    void ButtonClick (wxCommandEvent &event);
    void Click_turn (wxCommandEvent &event);
    void null_everything ();
    void init_everything ();
    void cursor_set (int cursor_position);
    void cursor_delete_null ();
};

class CalcApp : public wxApp
{
    CalcFrame *frame;
public:
    bool OnInit(); 
    int OnExit();
};

} //namespace ussr
