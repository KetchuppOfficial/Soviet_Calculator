#include <limits>
#include <string>
#include <algorithm>
#include <utility>


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
    std::reverse (number.begin (), number.end ());
    
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
    auto i = 0;
    for (auto &&reg : registers_)
    {
        wxPoint pt;
        wxSize size;

        if (i < 8) 
        {
            pt = wxPoint (710, 451 + 40*i);
            size.Set (155, 39);
        }
        else if (i < 11)
        {
            pt = wxPoint (923 + i*179, 564);
            size.Set (156, 43);
        }
        else
        {
            pt = wxPoint (942 + (i - 3)*179, 719);
            size.Set (156, 43);
        }

        reg = new wxTextCtrl (this,
                              Button_ID::SCREEN,
                              wxString{std::to_string(calc_.get_memory()[i])},
                              pt,
                              size,
                              wxTE_READONLY | wxTE_CENTRE);

        set (reg, 16, *wxBLUE, wxColour{223, 136, 136});
        i++;
    }
}

void CalcFrame::init_calc_buttons ()
{
    auto i = 0;
    for (auto &&button : buttons)
    {
        auto file_name = std::string{"images/"} + std::string{button.file};
        calc_buttons_[i] = new wxBitmapButton (drawPane,
                                               button.id,
                                               wxBitmap (wxImage (wxString{file_name}, wxBITMAP_TYPE_PNG).Scale (68, 68)),
                                               button.pos);
        Connect (button.id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
        i++;
    }
}

CalcFrame::CalcFrame (const wxString &title)
                     : wxFrame (nullptr, wxID_ANY, title, wxPoint(50, 50), wxSize(800, 1000)),
                       main_sizer{new wxBoxSizer (wxHORIZONTAL)}
{
    wxInitAllImageHandlers ();
    drawPane = new BackPanel (this, wxT("images/calcApp.png"), wxT("images/mem.png"), wxBITMAP_TYPE_PNG);
    main_sizer->Add (drawPane, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 0);
    SetSizer(main_sizer);

    screen_text = new wxTextCtrl (this, Button_ID::SCREEN, wxT(""), wxPoint(57, 20), wxSize(492, 90), wxTE_LEFT | wxTE_READONLY);
    set (screen_text, 40, *wxRED, *wxBLACK);

    turn_button = new wxButton (this, Button_ID::TURN, wxT("On"), wxPoint (36, 195));
    set (turn_button, 20, *wxRED, *wxBLACK);
    Connect (Button_ID::TURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::Click_turn));

    init_prog_buttons ();
    init_reg_buttons ();
    init_calc_buttons ();

    Maximize (true); //full screen
    Centre();
};

void CalcFrame::OnExit (wxCommandEvent &event)
{
    Close (true);
};

void CalcFrame::ButtonClick (wxCommandEvent &event)
{
    if (turn_pressed == false)
        return;

    auto ID = event.GetId ();
    calc_.handle_button (static_cast<Button_ID>(ID));
    screen_text->ChangeValue (std::to_string (calc_.get_memory().get_x()));
    cursor_set (ID - 1000);
}

void CalcFrame::Click_turn (wxCommandEvent &event)
{
    if (turn_pressed)
    {
        auto ID = event.GetId ();//how not to comment this code
        //back_end.get_button_num (ID);
        null_everything ();
        turn_button->SetForegroundColour (*wxRED);
        turn_button->SetBackgroundColour (*wxBLACK);
    }
    else
    {
        turn_button->SetForegroundColour (*wxBLACK);
        turn_button->SetBackgroundColour (*wxRED);
        init_everything ();
        cursor_set (0);
    }

    turn_pressed = !turn_pressed;
}

void CalcFrame::null_everything ()
{
    for (auto &&elem : prog_)
        elem.second->ChangeValue ("");

    for (auto &&val : registers_)
        val->ChangeValue ("00000000000");

    screen_text->Clear ();
    cursor_set (0);
    cursor_delete_null ();
}

void CalcFrame::init_everything () //initialization at calc turning on
{
    // There is a possibility only first 6 elements have to be cleared
    for (auto &&elem : prog_)
        elem.second->Clear ();

    for (auto &&val : registers_)
        val->ChangeValue ("0.");

    screen_text->ChangeValue ("0.");
    screen_text->ChangeValue ("0.");
}

void CalcFrame::cursor_set (int pos) //get number of current position, makes it's Background blue
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
