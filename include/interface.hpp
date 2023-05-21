#include <array>
#include <utility>

#include "back_panel.hpp"
#include "calculator.hpp"

namespace ussr
{

class CalcFrame : public wxFrame
{
    Soviet_Calculator calc_;
    std::array <std::pair<wxTextCtrl *, wxTextCtrl *>, 36> prog_;
    // first subarray used to be called prog_number
    // second subarray used to be called prog_code
    std::array <wxTextCtrl*, 14> reg_value;
    std::array <wxBitmapButton*, Button_ID::END_ - Button_ID::BEGIN_ - 1> calc_buttons_;

    BackPanel *drawPane;

    wxBoxSizer *main_sizer;
    wxTextCtrl *screen_text;
    wxTextCtrl *number_scr;
    wxButton* turn_button;

    bool turn_pressed = false;

public:

    CalcFrame (const wxString &title);

    void OnExit(wxCommandEvent &event);
    void ButtonClick (wxCommandEvent &event);
    void Click_turn (wxCommandEvent &event);
    void null_everything ();
    void init_everything ();
    void cursor_set (int cursor_position);
    void cursor_delete_null ();

private:

    void init_prog_buttons ();
    void init_reg_buttons ();
    void init_calc_buttons ();
};

} //namespace ussr
