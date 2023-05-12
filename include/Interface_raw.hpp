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

//  Основное окно
class CalcFrame:public wxFrame {
    //  Здесь используются указатели, для того, чтобы wx мог их потом спокойно
    // удалить. Указатели,  объявленные в функциях wx не удалаяет сам
    /*
    * wxBoxSizer - это самый простой разместитель, доступный в wxWidgets. Его
  назначение заключается в том, чтобы выровнять компоненты в одной строке - один
  рядом с другим - горизонтально или вертикально.
    */
    wxBoxSizer *main_sizer; //sizer for panel placement
    wxTextCtrl *screen_text;
    wxTextCtrl *prog_number [6][6];
    wxTextCtrl *prog_code [6][6];
    wxTextCtrl *reg_value [8];
    wxTextCtrl *rotate_reg_value [6]; 
    BackPanel *drawPane;
    wxButton* turn_button;
    wxBitmapButton* calc_button [31];
    static bool turn_pressed;
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
    struct Data {
        std::string prog_code_val [6][6];
        std::string reg_value_val [8];
        std::string rotate_reg_value_val [6];
        std::string text_screen_val;
        //std::string degree_val; //о формате необходимо договориться, и вообще будет ли это в 2 строчки
        int cursor_position; //нужно, чтобы подсвечивать курсор для программы
        //bool null_flag; //понадобится, если не будет перехвата с помощью try: catch
    };
};

std::string dec_to_six (int a);

//Индексы активных виждетов для связи с обработчиком,  событием и функцией
//все эти номера будут согласованы с теми, кто пишет мне обработчик
const int ID_BUT_PLUS = 1001;
const int ID_BUT_MINUS = 1002;
const int ID_BUT_MULT = 1003;
const int ID_BUT_DELEN = 1004;
const int ID_BUT_SWAP = 1005;
const int ID_BUT_ARROWUP = 1006;
const int ID_BUT_SIGN = 1007;
const int ID_BUT_VP = 1008;
const int ID_BUT_F = 1009;
const int ID_BUT_NULL = 1010;
const int ID_BUT_ONE = 1011;
const int ID_BUT_TWO = 1012;
const int ID_BUT_THREE = 1013;
const int ID_BUT_FOUR = 1014;
const int ID_BUT_FIVE = 1015;
const int ID_BUT_SIX = 1016;
const int ID_BUT_SEVEN = 1017;
const int ID_BUT_EIGHT = 1018;
const int ID_BUT_NINE = 1019;
const int ID_BUT_POINT = 1020;
const int ID_BUT_LSTEP = 1021;
const int ID_BUT_RSTEP = 1022;
const int ID_BUT_VO = 1023;
const int ID_BUT_SP = 1024;
const int ID_BUT_P = 1025;
const int ID_BUT_DEG = 1026;
const int ID_BUT_BP = 1027;
const int ID_BUT_PP = 1028;
const int ID_BUT_CX = 1029;
const int ID_SCREEN = 1030;
const int ID_BUT_TURN = 1031;

BackPanel::BackPanel (wxFrame *parent, wxString file, wxBitmapType format, wxString file2):wxPanel(parent) {
    //Загрузка файла с изображением. Хорошо бы еще проверить на загрузилось или нет
    image.LoadFile (file, format);
    image2.LoadFile (file2, format);
    Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
}

void BackPanel::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc (this);
    setImage(dc);
}

void BackPanel::paintBack () {
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    setImage(dc);
}

void BackPanel::setImage (wxDC &dc) {
    dc.DrawBitmap (image, 0, 0, false);
    dc.DrawBitmap (image2, 630, 450, false);
}

CalcFrame::CalcFrame (const wxString &title):wxFrame (NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(800, 1000)) {
    //  Включаем обработчик для всех типов изображений
    wxInitAllImageHandlers ();
    main_sizer = new wxBoxSizer (wxHORIZONTAL);
    drawPane = new BackPanel (this, wxT("Calc_pict/calcApp.png"), wxBITMAP_TYPE_PNG, wxT("Calc_pict/mem.png"));
    //  Добавляем к sizer планшет
    main_sizer->Add (drawPane, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 0);
    //  Устанавливаем sizer на окно
    SetSizer(main_sizer);

    screen_text = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint(57, 20), wxSize(492, 90), wxTE_LEFT | wxTE_READONLY);
	//text size
	screen_text->SetFont(wxFontInfo(40));
	//Background colour
	screen_text->SetBackgroundColour(*wxBLACK);
	//Text colour
	screen_text->SetForegroundColour(*wxRED);

    turn_button = new wxButton (this, ID_BUT_TURN, wxT("Turn"), wxPoint (36, 195));
    turn_button->SetForegroundColour (*wxRED);
    turn_button->SetBackgroundColour(*wxBLACK);
    Connect (ID_BUT_TURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::Click_turn));

    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            prog_number[j][i] = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint (650+120*j, 50+41*i), wxSize (50, 40), wxTE_READONLY | wxTE_CENTRE);
            std::string command_number = dec_to_six (i+6*j);
            prog_number[j][i]->ChangeValue (command_number);
            prog_number[j][i]->SetFont (wxFontInfo (20));
            prog_number[j][i]->SetForegroundColour (*wxRED);
            wxString code_value = wxString::Format (wxT ("%d"), i+6*j+1);
            prog_code[j][i] = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint (701+120*j, 50+41*i), wxSize (50, 40), wxTE_READONLY | wxTE_CENTRE);
            prog_code[j][i]->SetFont (wxFontInfo (20));
            prog_code[j][i]->SetForegroundColour (*wxRED);
        }
    }

    wxColour* reg_fon_colour = new wxColour (223, 136, 136);
    for (int i = 0; i < 8; i++) {
        reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000000"), wxPoint (710, 451+40*i), wxSize (155, 39), wxTE_READONLY | wxTE_CENTRE);
        reg_value[i]->SetFont (wxFontInfo (16));
        reg_value[i]->SetForegroundColour (*wxBLUE);
        reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    for (int i = 0; i < 3; i++) {
        rotate_reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000000"), wxPoint (923+i*179, 564), wxSize (156, 43), wxTE_READONLY | wxTE_CENTRE);
        rotate_reg_value[i]->SetFont (wxFontInfo (16));
        rotate_reg_value[i]->SetForegroundColour (*wxBLUE);
        rotate_reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    for (int i = 3; i < 6; i++) {
        rotate_reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000000"), wxPoint (942+(i-3)*179, 719), wxSize (156, 43), wxTE_READONLY | wxTE_CENTRE);
        rotate_reg_value[i]->SetFont (wxFontInfo (16));
        rotate_reg_value[i]->SetForegroundColour (*wxBLUE);
        rotate_reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    // Изображение для кнопки
    wxBitmapButton *anybutton; //пока что не понятно, нужнен ли этот указатель
    //wxImage plus_pict(wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG);
    calc_button [1] = new wxBitmapButton(drawPane, ID_BUT_PLUS, wxBitmap(wxImage (wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG)), wxPoint(420, 529));
    Connect (ID_BUT_PLUS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CalcFrame::ButtonClick)); 

    anybutton = new wxBitmapButton (drawPane, ID_BUT_MINUS, wxBitmap(wxImage (wxT("Calc_pict/minus.png"), wxBITMAP_TYPE_PNG)), wxPoint(420, 643));
    Connect(ID_BUT_MINUS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_MULT, wxBitmap(wxImage (wxT("Calc_pict/mult.png"), wxBITMAP_TYPE_PNG)), wxPoint(333, 529));
    Connect(ID_BUT_MULT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_DELEN, wxBitmap (wxImage (wxT ("Calc_pict/delen.png"), wxBITMAP_TYPE_PNG)), wxPoint (333, 643));
    Connect (ID_BUT_DELEN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    
    new wxBitmapButton (drawPane, ID_BUT_SWAP, wxBitmap (wxImage (wxT ("Calc_pict/swap.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (333, 414));
    Connect (ID_BUT_SWAP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    
    new wxBitmapButton (drawPane, ID_BUT_ARROWUP, wxBitmap (wxImage (wxT ("Calc_pict/arrowup.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (420, 414));
    Connect (ID_BUT_ARROWUP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_SIGN, wxBitmap (wxImage (wxT ("Calc_pict/sign.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (256, 770));
    Connect (ID_BUT_SIGN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    
    new wxBitmapButton (drawPane, ID_BUT_VP, wxBitmap (wxImage (wxT ("Calc_pict/vp.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (360, 770));
    Connect (ID_BUT_VP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_F, wxBitmap (wxImage (wxT ("Calc_pict/f.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (464, 770));
    Connect (ID_BUT_F, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_NULL, wxBitmap (wxImage (wxT ("Calc_pict/k0.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (48, 770));
    Connect (ID_BUT_NULL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    
    new wxBitmapButton (drawPane, ID_BUT_POINT, wxBitmap (wxImage (wxT ("Calc_pict/pnt.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (152, 770));
    Connect (ID_BUT_POINT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_ONE, wxBitmap (wxImage (wxT ("Calc_pict/k1.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (55, 639));
    Connect (ID_BUT_ONE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_TWO, wxBitmap (wxImage (wxT ("Calc_pict/k2.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (138, 639));
    Connect (ID_BUT_TWO, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_THREE, wxBitmap (wxImage (wxT ("Calc_pict/k3.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (221, 639));
    Connect (ID_BUT_THREE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_FOUR, wxBitmap (wxImage (wxT ("Calc_pict/k4.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (55, 530));
    Connect (ID_BUT_FOUR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_FIVE, wxBitmap (wxImage (wxT ("Calc_pict/k5.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (138, 530));
    Connect (ID_BUT_FIVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_SIX, wxBitmap (wxImage (wxT ("Calc_pict/k6.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (221, 530));
    Connect (ID_BUT_SIX, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_SEVEN, wxBitmap (wxImage (wxT ("Calc_pict/k7.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (55, 416));
    Connect (ID_BUT_SEVEN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_EIGHT, wxBitmap (wxImage (wxT ("Calc_pict/k8.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (138, 416));
    Connect (ID_BUT_EIGHT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_NINE, wxBitmap (wxImage (wxT ("Calc_pict/k9.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (221, 416));
    Connect (ID_BUT_NINE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_LSTEP, wxBitmap (wxImage (wxT ("Calc_pict/shgL.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (164, 193));
    Connect (ID_BUT_LSTEP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_RSTEP, wxBitmap (wxImage (wxT ("Calc_pict/shgR.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (246, 193));
    Connect (ID_BUT_RSTEP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_VO, wxBitmap (wxImage (wxT ("Calc_pict/vo.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (328, 193));
    Connect (ID_BUT_VO, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_SP, wxBitmap (wxImage (wxT ("Calc_pict/sp.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (410, 193));
    Connect (ID_BUT_SP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_P, wxBitmap (wxImage (wxT ("Calc_pict/p.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (158, 303));
    Connect (ID_BUT_P, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_DEG, wxBitmap (wxImage (wxT ("Calc_pict/x^y.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (246, 303));
    Connect (ID_BUT_DEG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_BP, wxBitmap (wxImage (wxT ("Calc_pict/bp.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (328, 303));
    Connect (ID_BUT_BP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_PP, wxBitmap (wxImage (wxT ("Calc_pict/pp.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (410, 303));
    Connect (ID_BUT_PP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));

    new wxBitmapButton (drawPane, ID_BUT_CX, wxBitmap (wxImage (wxT ("Calc_pict/cx.png"), wxBITMAP_TYPE_PNG).Scale (68, 68)), wxPoint (36, 296));
    Connect (ID_BUT_CX, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::ButtonClick));
    Maximize (true); //full screen
    Centre(); //center
};

bool CalcFrame::turn_pressed = false;

CalcFrame::~CalcFrame() {
    for (int i = 0; i < 31; i++) {
        delete calc_button [i];
    }
    drawPane->Destroy();
    Close (true);
};

void CalcFrame::ButtonClick (wxCommandEvent &event) { //пока что обработчик нажатия делает разные вещи, чтобы мне разобраться во всём
    if (turn_pressed == false) {
        return;
    }
    int ID = event.GetId ();
    //back_end.get_button_num (ID);
    screen_set_values ();
    wxString IDnum = wxT("Button pressed ") + wxString::Format(wxT("%d"), ID);
    wxMessageBox(IDnum);
    screen_text->ChangeValue (IDnum);
    if (ID == 1020) {
        screen_text->SetForegroundColour (*wxBLUE);
    }
    else {
        screen_text->SetForegroundColour (*wxRED);
    }
}

void CalcFrame::Click_turn (wxCommandEvent &event) {
    if (turn_pressed == false) {//здесь также будет передача данных о том, что всё включилось, это нужно, чтобы при выключенном калькуляторе ничего не работало и не заполнялось
        turn_button->SetForegroundColour (*wxBLACK);
        turn_button->SetBackgroundColour (*wxRED);
        init_everything ();
        cursor_set (0);
        turn_pressed = true;
        return;
    }
    if (turn_pressed == true) { //здесь нужно скзать, чтобы всё занулили
        int ID = event.GetId ();
        //back_end.get_button_num (ID);
        null_everything ();
        turn_button->SetForegroundColour (*wxRED);
        turn_button->SetBackgroundColour (*wxBLACK);
        turn_pressed = false;
        return;
    }
}

std::string dec_to_six (int a) { //если надо будет добавить нумерацию аля 00, 01, 02, то добавлю, это дело 2-х минут
    std::string number, ost;
    while (a / 6 != 0) {
        ost = std::to_string (a % 6);
        number += ost;
        a = a / 6;
    }
    ost = std::to_string (a);
    number += ost;
    std::reverse (number.begin (), number.end ());
    return number;
}

void CalcFrame::null_everything () {
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            prog_code[j][i]->ChangeValue ("");
        }
    }
    for (int i = 0; i < 8; i++) {
        reg_value[i]->ChangeValue ("00000000000");
    }
    for (int i = 0; i < 6; i++) {
        rotate_reg_value[i]->ChangeValue ("00000000000");
    }
    screen_text->Clear ();
    return;
}

void CalcFrame::init_everything () {
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            prog_code[j][i]->Clear ();
        }
    }
    for (int i = 0; i < 8; i++) {
        reg_value[i]->ChangeValue ("0.");
    }
    for (int i = 0; i < 6; i++) {
        rotate_reg_value[i]->ChangeValue ("0.");
    }
    screen_text->ChangeValue ("0.");
    screen_text->ChangeValue ("0.");
    return;
}

void CalcFrame::cursor_set (int pos) {
    prog_number[pos][pos]->SetBackgroundColour (*wxWHITE);
    prog_code[pos][pos]->SetBackgroundColour (*wxWHITE);
    //в процессе уточнения как лучше сделать и нужно ли вообще менять цвет фона 
    //программы для того, чтобы ходить по ней, лучше добавить флаг, то есть номер программы
    //и по ней потом определять какой номер нужно подсветить
    return;
    for (int i = 0; i < 36; i++) {
        if (i != pos) {
            prog_number[i][i]->SetBackgroundColour (*wxBLACK);
        }
    }
}

void CalcFrame::screen_set_values () {//a.f.k.
    return;
}

class CalcApp:public wxApp {
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

