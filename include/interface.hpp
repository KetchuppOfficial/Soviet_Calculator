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
    std::array <wxTextCtrl*, 14> regs_;
    std::array <wxBitmapButton*, Button_ID::END_ - Button_ID::BEGIN_ - 1> calc_buttons_;
    std::array <wxTextCtrl *, 8> digits_;

    BackPanel *background_;

    wxBoxSizer *main_sizer_;
    wxButton* power_button_;

    bool power_on_ = false;

public:

    CalcFrame (const wxString &title);

    void OnExit (wxCommandEvent &event);
    void click (wxCommandEvent &event);
    void click_power_button (wxCommandEvent &event);

private:

    void init_power_button ();
    void init_prog_buttons ();
    void init_reg_buttons ();
    void init_calc_buttons ();
    void init_digits ();

    void print_number ();

    void null_everything ();
    void init_everything ();
    void cursor_set (int cursor_position);
    void cursor_delete_null ();
};

} // namespace ussr
