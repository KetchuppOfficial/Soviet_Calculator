#include <limits>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#include <sstream>

#include "interface.hpp"

namespace ussr
{

namespace
{

struct Button
{
    Button_ID id;
    const char *file;
    wxPoint pos;
};

const std::array<Button, Button_ID::END_ - Button_ID::BEGIN_ - 3> buttons
{
    Button{Button_ID::PLUS,    "plus.png",    wxPoint{420, 529}},
    Button{Button_ID::MINUS,   "minus.png",   wxPoint{420, 643}},
    Button{Button_ID::MULT,    "mult.png",    wxPoint{333, 529}},
    Button{Button_ID::DIV,     "div.png",     wxPoint{333, 643}},
    Button{Button_ID::POW,     "x^y.png",     wxPoint{246, 303}},
    Button{Button_ID::SWAP,    "swap.png",    wxPoint{333, 414}},
    Button{Button_ID::ARROWUP, "arrowup.png", wxPoint{420, 414}},
    Button{Button_ID::CX,      "cx.png",      wxPoint{36, 296}},
    Button{Button_ID::SIGN,    "sign.png",    wxPoint{256, 770}},
    Button{Button_ID::COMMA,   "pnt.png",     wxPoint{152, 770}},
    Button{Button_ID::P,       "p.png",       wxPoint{158, 303}},
    Button{Button_ID::F,       "f.png",       wxPoint{464, 770}},
    Button{Button_ID::LSTEP,   "shgL.png",    wxPoint{164, 193}},
    Button{Button_ID::RSTEP,   "shgR.png",    wxPoint{246, 193}},
    Button{Button_ID::VP,      "vp.png",      wxPoint{360, 770}},
    Button{Button_ID::VO,      "vo.png",      wxPoint{328, 193}},
    Button{Button_ID::SP,      "sp.png",      wxPoint{410, 193}},
    Button{Button_ID::BP,      "bp.png",      wxPoint{328, 303}},
    Button{Button_ID::PP,      "pp.png",      wxPoint{410, 303}},
    Button{Button_ID::ZERO,    "k0.png",      wxPoint{48, 770}},
    Button{Button_ID::ONE,     "k1.png",      wxPoint{55, 639}},
    Button{Button_ID::TWO,     "k2.png",      wxPoint{138, 639}},
    Button{Button_ID::THREE,   "k3.png",      wxPoint{221, 639}},
    Button{Button_ID::FOUR,    "k4.png",      wxPoint{55, 530}},
    Button{Button_ID::FIVE,    "k5.png",      wxPoint{138, 530}},
    Button{Button_ID::SIX,     "k6.png",      wxPoint{221, 530}},
    Button{Button_ID::SEVEN,   "k7.png",      wxPoint{55, 416}},
    Button{Button_ID::EIGHT,   "k8.png",      wxPoint{138, 416}},
    Button{Button_ID::NINE,    "k9.png",      wxPoint{221, 416}}
};

std::string dec_to_six (unsigned a)
{
    std::string number;
    number.reserve (std::numeric_limits<decltype(a)>::digits);

    while (a / 6)
    {
        number += std::to_string (a % 6);
        a /= 6;
    }

    number += std::to_string (a);
    std::reverse (number.begin(), number.end());
    
    return number;
}

} // unnamed namespace

auto set = [](auto *ptr, unsigned font, const wxColour &foreground,
                                        const wxColour &background)
{
    ptr->SetFont (wxFontInfo (font));
    ptr->SetForegroundColour (foreground);
    ptr->SetBackgroundColour (background);
};

void CalcFrame::init_prog_buttons ()
{
    auto i = 0;
    for (auto &&pair : prog_)
    {
        auto &prog_number = pair.first;
        auto &prog_code = pair.second;
        
        auto x = 650 + 120*(i % 6);
        auto y = 50 + 41*(i / 6);

        prog_number = new wxTextCtrl (this,
                                      Button_ID::SCREEN, wxString{dec_to_six (i)},
                                      wxPoint (x, y), wxSize (50, 40),
                                      wxTE_READONLY | wxTE_CENTRE);

        prog_code = new wxTextCtrl (this,
                                    Button_ID::SCREEN, wxT(""), 
                                    wxPoint (x + 51, y), wxSize (50, 40),
                                    wxTE_READONLY | wxTE_CENTRE);

        set (prog_number, 20, *wxRED, *wxBLACK);
        set (prog_code, 20, *wxRED, *wxBLACK);
        
        i++;
    }
}

void CalcFrame::init_reg_buttons ()
{
    regs_[0] = new wxTextCtrl (this,
                               Button_ID::SCREEN, wxT(""),
                               wxPoint{710, 731}, wxSize{155, 39},
                               wxTE_READONLY | wxTE_CENTRE);

    for (auto i = 1; i != 4; ++i)
        regs_[i] = new wxTextCtrl (this,
                                   Button_ID::SCREEN, wxT(""),
                                   wxPoint{923 + (i - 1)*179, 564}, wxSize{156, 43},
                                   wxTE_READONLY | wxTE_CENTRE);

    for (auto i = 4; i != 7; ++i)
        regs_[i] = new wxTextCtrl (this,
                                   Button_ID::SCREEN, wxT(""),
                                   wxPoint{942 + (i - 4)*179, 719}, wxSize{156, 43},
                                   wxTE_READONLY | wxTE_CENTRE);
                               
    for (auto i = 7; i != regs_.size(); ++i)
        regs_[i] = new wxTextCtrl (this,
                                   Button_ID::SCREEN, wxT(""),
                                   wxPoint{710, 691 - 40*(i - 7)}, wxSize{155, 39},
                                   wxTE_READONLY | wxTE_CENTRE);

    for (auto &&reg : regs_)
        set (reg, 16, *wxBLUE, wxColour{223, 136, 136});
}

void CalcFrame::init_calc_buttons ()
{
    auto i = 0;
    for (auto &&button : buttons)
    {
        auto file_name = std::string{"images/"} + std::string{button.file};
        calc_buttons_[i] = new wxBitmapButton (background_,
                                               button.id,
                                               wxBitmap (wxImage (wxString{file_name}, wxBITMAP_TYPE_PNG).Scale (68, 68)),
                                               button.pos);
        Connect (button.id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::click));
        i++;
    }
}

void CalcFrame::init_digits ()
{
    auto i = 0;
    for (auto &&digit : digits_)
    {
        digit = new wxTextCtrl (this,
                                Button_ID::SCREEN, wxT(""),
                                wxPoint(61 + i * 60, 30), wxSize(59, 67),
                                wxTE_LEFT | wxTE_READONLY);
        set (digit, 40, *wxRED, *wxBLACK);
        i++;
    }
}

void CalcFrame::init_power_button ()
{
    power_button_ = new wxButton (this, Button_ID::TURN, wxT("On"), wxPoint (36, 195));
    set (power_button_, 20, *wxRED, *wxBLACK);
    Connect (Button_ID::TURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::click_power_button));
}

CalcFrame::CalcFrame (const wxString &title)
                     : wxFrame (nullptr, wxID_ANY, title, wxPoint(50, 50), wxSize(800, 1000)),
                       main_sizer_{new wxBoxSizer (wxHORIZONTAL)}
{
    wxInitAllImageHandlers ();

    background_ = new BackPanel (this, wxT("images/calcApp.png"), wxT("images/mem.png"), wxBITMAP_TYPE_PNG);
    main_sizer_->Add (background_, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 0);
    SetSizer(main_sizer_);
    
    init_power_button();
    init_prog_buttons();
    init_reg_buttons();
    init_calc_buttons();
    init_digits();

    Maximize (true); //full screen
    Centre();
};

void CalcFrame::OnExit (wxCommandEvent &event)
{
    Close (true);
};

void CalcFrame::print_exp ()
{
    auto exp_digits = calc_.get_exp_digits();
    if (!calc_.get_exp_flag())
    {
        digits_[5]->ChangeValue ("");
        digits_[6]->ChangeValue ("");
        digits_[7]->ChangeValue ("");
    }
    else if (exp_digits == 0)
    {
        digits_[5]->ChangeValue ("");
        digits_[6]->ChangeValue ("0");
        digits_[7]->ChangeValue ("0");
    }
    else // if (exp_digits < 3)
    {
        auto exp = calc_.get_exp();
        
        if (exp < 0)
        {
            digits_[5]->ChangeValue ("-");
            exp = -exp;
        }
        else
            digits_[5]->ChangeValue ("");
            
        digits_[7]->ChangeValue (std::to_string (exp % 10));
        exp /= 10;
        digits_[6]->ChangeValue (std::to_string (exp));
    }
}

void CalcFrame::input_mode (double x)
{
    auto is_negative = (x < 0);
    auto num = std::to_string (x);
    auto n_symbs = std::min (std::size_t{4},
                             num.find ('.') + calc_.get_comma_flag() + calc_.get_digits_after_comma());

    for (auto rit = std::next (digits_.rbegin(), 3), 
              rend = std::prev(digits_.rend()); rit != rend; ++rit)
    {
        if (n_symbs > 0)
            (*rit)->ChangeValue (wxString{num[--n_symbs + is_negative]});
        else
            (*rit)->ChangeValue ("");
    }

    print_exp();
}

void CalcFrame::output_mode (double x)
{
    std::stringstream ss;
    ss << std::scientific << x;
    auto num = ss.str();
    auto e_pos = num.find('e');

    if (num[e_pos + 1] == '-')
        digits_[5]->ChangeValue ("-");
    else
        digits_[5]->ChangeValue ("");
    
    auto i = 0;
    for (auto it = std::next (digits_.begin(), 1), 
              ite = std::prev (digits_.end(), 3); it != ite; ++it)
    {
        auto symb = num[i + (x < 0)];
        if (symb == 'e')
            break;
        (*it)->ChangeValue (wxString{symb});
        i++;
    }

    digits_[6]->ChangeValue (wxString{num[e_pos + 2]});
    digits_[7]->ChangeValue (wxString{num[e_pos + 3]});
}

void CalcFrame::print_number ()
{
    auto x = calc_.get_memory().get_x();

    if (x < 0)
        digits_[0]->ChangeValue ("-");

    if (calc_.get_input_mode_flag())
        input_mode (x);
    else
        output_mode (x);
}

void CalcFrame::print_regs ()
{
    auto &mem = calc_.get_memory();

    auto i = 0;
    std::for_each (regs_.begin(), regs_.end(),
                   [&mem, i](auto &&reg) mutable { reg->ChangeValue (std::to_string (mem[i++])); });
}

void CalcFrame::click (wxCommandEvent &event)
{
    if (power_on_ == false)
        return;

    auto ID = event.GetId ();
    calc_.handle_button (static_cast<Button_ID>(ID));

    print_number();
    print_regs();
    
    #if 0
    cursor_set (ID - 1000);
    #endif
}

void CalcFrame::click_power_button (wxCommandEvent &event)
{
    if (power_on_)
    {
        power_button_->SetForegroundColour (*wxRED);
        power_button_->SetBackgroundColour (*wxBLACK);
        null_everything ();
    }
    else
    {
        power_button_->SetForegroundColour (*wxBLACK);
        power_button_->SetBackgroundColour (*wxRED);
        init_everything ();
    }

    power_on_ = !power_on_;
}

void CalcFrame::null_everything ()
{
    std::for_each (prog_.begin(), prog_.end(),
                   [](auto &&pair){ pair.second->ChangeValue (""); });
    std::for_each (regs_.begin(), regs_.end(),
                   [](auto &&reg){ reg->ChangeValue (""); });
    std::for_each (digits_.begin(), digits_.end(),
                   [](auto &&digit){ digit->Clear (); });

    cursor_set (0);
    cursor_delete_null ();
    calc_.reset();
}

void CalcFrame::init_everything ()
{
    std::for_each (prog_.begin(), prog_.end(),
                   [](auto &&pair){ pair.second->Clear (); });
    std::for_each (regs_.begin(), regs_.end(),
                   [](auto &&reg){ reg->ChangeValue ("0"); });

    cursor_set (0);
}

void CalcFrame::cursor_set (int pos)
{
    for (auto &&elem : prog_)
    {
        elem.first->SetBackgroundColour (*wxBLACK);
        elem.second->SetBackgroundColour (*wxBLACK);
    }

    prog_[pos].first->SetBackgroundColour (*wxWHITE);
    prog_[pos].second->SetBackgroundColour (*wxWHITE);
}

void CalcFrame::cursor_delete_null ()
{
    prog_[0].first->SetBackgroundColour (*wxBLACK);
    prog_[0].second->SetBackgroundColour (*wxBLACK);
}

} // namespace ussr
