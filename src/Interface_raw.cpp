#include "Interface_raw.hpp"

#include <limits>
#include <string>
#include <algorithm>

namespace ussr
{

namespace
{

struct Button
{
    Button_ID id;
    const char *file;
    wxPoint pos;
    std::pair<unsigned, unsigned> scale;
};

constexpr std::array<Button, Button_ID::END_ - Button_ID::BEGIN_ - 1> buttons
{
    {Button_ID::PLUS,    "Calc_pict/plus.png",    wxPoint{420, 529}, {1, 1}},
    {Button_ID::MINUS,   "Calc_pict/minus.png",   wxPoint{420, 643}, {1, 1}},
    {Button_ID::MULT,    "Calc_pict/mult.png",    wxPoint{333, 529}, {1, 1}},
    {Button_ID::DIV,     "Calc_pict/delen.png",   wxPoint{333, 643}, {1, 1}},
    {Button_ID::SWAP,    "Calc_pict/swap.png",    wxPoint{333, 414}, {68, 68}},
    {Button_ID::ARROWUP, "Calc_pict/arrowup.png", wxPoint{420, 414}, {68, 68}},
    {Button_ID::SIGN,    "Calc_pict/sign.png",    wxPoint{256, 770}, {68, 68}},
    {Button_ID::VP,      "Calc_pict/vp.png",      wxPoint{360, 770}, {68, 68}},
    {Button_ID::F,       "Calc_pict/f.png",       wxPoint{464, 770}, {68, 68}},
    {Button_ID::POINT,   "Calc_pict/pnt.png",     wxPoint{152, 770}, {68, 68}},
    {Button_ID::LSTEP,   "Calc_pict/shgL.png",    wxPoint{164, 193}, {68, 68}},
    {Button_ID::RSTEP,   "Calc_pict/shgR.png",    wxPoint{246, 193}, {68, 68}},
    {Button_ID::VO,      "Calc_pict/vo.png",      wxPoint{328, 193}, {68, 68}},
    {Button_ID::SP,      "Calc_pict/sp.png",      wxPoint{410, 193}, {68, 68}},
    {Button_ID::P,       "Calc_pict/p.png",       wxPoint{158, 303}, {68, 68}},
    {Button_ID::POW,     "Calc_pict/x^y.png",     wxPoint{246, 303}, {68, 68}},
    {Button_ID::BP,      "Calc_pict/bp.png",      wxPoint{328, 303}, {68, 68}},
    {Button_ID::PP,      "Calc_pict/pp.png",      wxPoint{410, 303}, {68, 68}},
    {Button_ID::CX,      "Calc_pict/cx.png",      wxPoint{36, 296},  {68, 68}},
    {Button_ID::ZERO,    "Calc_pict/k0.png",      wxPoint{48, 770},  {68, 68}},
    {Button_ID::ONE,     "Calc_pict/k1.png",      wxPoint{55, 639},  {68, 68}},
    {Button_ID::TWO,     "Calc_pict/k2.png",      wxPoint{138, 639}, {68, 68}},
    {Button_ID::THREE,   "Calc_pict/k3.png",      wxPoint{221, 639}, {68, 68}},
    {Button_ID::FOUR,    "Calc_pict/k4.png",      wxPoint{55, 530},  {68, 68}},
    {Button_ID::FIVE,    "Calc_pict/k5.png",      wxPoint{138, 530}, {68, 68}},
    {Button_ID::SIX,     "Calc_pict/k6.png",      wxPoint{221, 530}, {68, 68}},
    {Button_ID::SEVEN,   "Calc_pict/k7.png",      wxPoint{55, 416},  {68, 68}},
    {Button_ID::EIGHT,   "Calc_pict/k8.png",      wxPoint{138, 416}, {68, 68}},
    {Button_ID::NINE,    "Calc_pict/k9.png",      wxPoint{221, 416}, {68, 68}},
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

BackPanel::BackPanel (wxFrame *parent, wxString file, wxBitmapType format, wxString file2)
                     : wxPanel(parent)
{
    image.LoadFile (file, format);
    image2.LoadFile (file2, format);
    Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
}

void BackPanel::paintEvent (wxPaintEvent &evt)
{
    wxPaintDC dc (this);
    setImage(dc);
}

void BackPanel::paintBack ()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    setImage(dc);
}

void BackPanel::setImage (wxDC &dc)
{
    dc.DrawBitmap (image, 0, 0, false);
    dc.DrawBitmap (image2, 630, 450, false);
}

CalcFrame::CalcFrame (const wxString &title)
                     : wxFrame (nullptr, wxID_ANY, title, wxPoint(50, 50), wxSize(800, 1000)),
                       main_sizer{new wxBoxSizer (wxHORIZONTAL)};
{
    wxInitAllImageHandlers ();
    drawPane = new BackPanel (this, wxT("Calc_pict/calcApp.png"), wxBITMAP_TYPE_PNG, wxT("Calc_pict/mem.png"));
    main_sizer->Add (drawPane, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 0);
    SetSizer(main_sizer);

    screen_text = new wxTextCtrl (this, Button_ID::SCREEN, wxT(""), wxPoint(57, 20), wxSize(492, 90), wxTE_LEFT | wxTE_READONLY);
	screen_text->SetFont(wxFontInfo(40));
	screen_text->SetBackgroundColour(*wxBLACK);
	screen_text->SetForegroundColour(*wxRED);

    turn_button = new wxButton (this, Button_ID::TURN, wxT("Turn"), wxPoint (36, 195));
    turn_button->SetForegroundColour (*wxRED);
    turn_button->SetBackgroundColour(*wxBLACK);
    Connect (Button_ID::TURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::Click_turn));

    auto set = [](wxTextCtrl *ptr, unsigned font, const wxColour &foreground,
                                                  const wxColour &background)
    {
        ptr->SetFont (wxFontInfo (font));
        ptr->SetForegroundColour (foreground);
        ptr->SetBackgroundColour (background);
    };

    for (auto i = 0; auto &&pair : prog_)
    {
        auto &prog_number = pair.first;
        auto &prog_code = pair.second;

        prog_number = new wxTextCtrl (this, Button_ID::SCREEN, wxT(""), wxPoint (650 + 20*i, 50 + 41*(i % 6)), wxSize (50, 40), wxTE_READONLY | wxTE_CENTRE);
        prog_number->ChangeValue (dec_to_six (i));
        set (prog_number, 20, *wxRED, *wxBLACK);

        prog_code = new wxTextCtrl (this, Button_ID::SCREEN, wxT(""), wxPoint (701 + 20*i, 50 + 41*(i % 6)), wxSize (50, 40), wxTE_READONLY | wxTE_CENTRE);
        set (prog_code, 20, *wxRED, *wxBLACK);

        i++;
    }

    for (auto i = 0; auto &&reg : reg_value)
    {
        wxPoint pt;
        wxSize size;

        if (i < 8)
        {
            pt = wxPoint (710, 451+40*i);
            size.Set (155, 39);
        }
        else if (i < 11)
        {
            pt = wxPoint (923+i*179, 564);
            size.Set (156, 43);
        }
        else
        {
            pt = wxPoint (942+(i-3)*179, 719);
            size.Set (156, 43);
        }

        reg = new wxTextCtrl (this, Button_ID::SCREEN, wxT ("00000000000"), pt, size, wxTE_READONLY | wxTE_CENTRE);
        set (reg, 16, *wxBLUE, wxColour{223, 136, 136});

        i++;
    }

    for (auto i = 0; auto &&button : buttons)
    {
        auto x = button.scale.first;
        auto y = button.scale.second;
        Calc_buttons[i++] = new wxBitmapButton (drawPane,
                                                button.id,
                                                wxBitmap (wxImage (wxT (button.file), wxBITMAP_TYPE_PNG).Scale (x, y)),
                                                button.pos);
        Connect (button.id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    }

    Maximize (true); //full screen
    Centre(); //center
};

CalcFrame::~CalcFrame()
{
    drawPane->Destroy();
    Close (true);
};

void CalcFrame::ButtonClick (wxCommandEvent &event)
{ //пока что обработчик нажатия делает разные вещи, чтобы мне разобраться во всём
    if (turn_pressed == false)
        return;

    auto ID = event.GetId ();
    //back_end.get_button_num (ID);
    auto IDnum = wxT("Bttn pressed ") + wxString::Format(wxT("%d"), ID);
    screen_text->ChangeValue (IDnum);
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
    for (auto &&prog_code : prog_)
        prog_code->ChangeValue ("");

    for (auto &&val : reg_value)
        val->ChangeValue ("00000000000");

    screen_text->Clear ();
    cursor_set (0);
    cursor_delete_null ();
}

void CalcFrame::init_everything () //initialization at calc turning on
{
    // There is a possibility only first 6 elements have to be cleared
    for (auto &&prog_code : prog_)
        prog_code->Clear ();

    for (auto &&val : reg_value)
        val->ChangeValue ("0.");

    screen_text->ChangeValue ("0.");
    screen_text->ChangeValue ("0.");
}

void CalcFrame::cursor_set (int pos) //get number of current position, makes it's Background blue
{
    std::transform (prog_.begin(), prog_.end(),
                    prog_.begin(),
                    [](auto &&elem){ elem.first->SetBackgroundColour (*wxBLACK);
                                     elem.second->SetBackgroundColour (*wxBLACK); });

    prog_[pos].first->SetBackgroundColour (*wxWHITE);
    prog_[pos].second->SetBackgroundColour (*wxWHITE);
}

void CalcFrame::cursor_delete_null ()
{
    prog_number[0]->SetBackgroundColour (*wxBLACK);
    prog_code[0]->SetBackgroundColour (*wxBLACK);
}

bool CalcApp::OnInit()
{
    frame = new CalcFrame(wxT("БК-21"));
    frame->Show();
    SetTopWindow (frame);
    return true;
}

int CalcApp::OnExit ()
{
    delete frame;
    return 0;
}

} // namespace ussr
