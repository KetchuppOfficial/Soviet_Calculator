#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <cstring>
#include <iostream>
#include <cstdlib>

// тут добавилась только лишь обработка нажатий мыши
//   Класс для фоновой картинки и дугого рисования
class BackPanel:public wxPanel {
    //  Изображение для фона
    wxBitmap image;
    wxBitmap image2;
public:
    //wxTextCtrl *screen_text; //можно ли этот текст привязать ко всему фрейму? 
    BackPanel (wxFrame *parent, wxString file, wxBitmapType format, wxString file2);
    // Все рисование происходит когда происходит событие перерисовки
    void paintEvent (wxPaintEvent &evt);
    void paintEvent2 (wxPaintEvent &evt);
    //  Эта функция собственно все и будет рисовать
    void paintBack ();
    void paintBack2 ();
    //  wxDC - абстрактный класс для рисования. У него есть реальные наследники:
    // wxPaintDC,  wxClientDC и wxMemoryDC
    void setImage (wxDC &dc);
    void setImage2 (wxDC &dc);
    void OnMouse (wxMouseEvent &event); // новая функция по сравнению с fon_image
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
    wxBoxSizer *main_sizer, *calc_sizer, *mem_and_prog_sizer; //делаем ещё 2 сайзера для размещения панели с калькулятором и панели с памятью
    wxGridSizer *prog_sizer; //это нужно, чтобы писать текст и выводить его на экран
    wxTextCtrl *screen_text;
    wxTextCtrl *prog_number [6][6];
    wxTextCtrl *prog_code [6][6];
    wxTextCtrl *reg_value [8]; //711, 451, 771
    wxTextCtrl *rotate_reg_value [6]; 
    // Панель для отрисовки калькулятора и других элементов
    BackPanel *drawPane;
    wxButton* turn_button;
    static bool turn_pressed;
    //wxPanel *panel; //возможно она не нужна
    // Примеры кнопок с картинками
    //wxBitmapButton *plus_button; //здесь возможно стоит создать массив указателей
    wxTextCtrl *number_scr; // текст для нужд вывода
    wxTimer *tm; // объект таймер, зачем он нужен пойму позже
public:
    CalcFrame (const wxString &title);
    ~CalcFrame ();
    //  функция при нажатии на кнопку +
    void pressOne (wxCommandEvent &event);
    //  функция при нажатии на кнопку -
    void pressSec (wxCommandEvent &event);
    void ButtonClick (wxCommandEvent &event);
    void Click_turn (wxCommandEvent &event);
    std::string dec_to_six (int a);
    void null_everything ();
    // void OnTimer(wxCommandEvent& event);                      // изменение параметров при истечении момента времени
    //  вызывается при обработке сигнала от мыши
};
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
    //Загрузка файла с изображением. Хорошо бы еще проверить на пердмет
    //успешно или нет
    image.LoadFile (file, format);
    image2.LoadFile (file2, format);
    //Связывание функции paintEvent событием перерисовки панели
    Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
    //Связываем событие мыши (нажатие на левую кнопку) с функцией OnMouse()
    //Так как мы связываем ее только в паненли BackPanel,  то события мыши будут перехватываться
    //только в этой панели
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(BackPanel::OnMouse));
}

void BackPanel::paintEvent(wxPaintEvent &evt) {
    // wxPaintDC - наследник wxDC. Самый простой планшет лоя рисования
    wxPaintDC dc (this);
    //  Загрузка изображения на планшет (реализована ниже)
    setImage(dc);
}

//  Можно и так. wxClientDC - позволяет оставлять рисовать на нем мышкой,
// например

void BackPanel::paintBack () {
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    setImage(dc);
}

void BackPanel::setImage (wxDC &dc) {
    //  Устанавливаем изображение на планшет
    dc.DrawBitmap(image, 0, 0, false);
    dc.DrawBitmap (image2, 630, 450, false);
}

void BackPanel::OnMouse (wxMouseEvent &event) {
    wxString answ;
    int x = event.GetX();
    int y = event.GetY();
    answ = answ.Format (wxT("(%d, %d)"), x, y);
    wxMessageBox(answ);
};

CalcFrame::CalcFrame (const wxString &title):wxFrame (NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(800, 1000)) {
    //  Включаем обработчик для всех типов изображений
    wxInitAllImageHandlers ();
    //  Создаем sizer для размещения планшета wxPanelDC
    main_sizer = new wxBoxSizer (wxHORIZONTAL);
    mem_and_prog_sizer = new wxBoxSizer (wxVERTICAL);
    calc_sizer = new wxBoxSizer (wxVERTICAL); //пока что под вопросом, но скорее всего нужен
    //  Создаем планшет,  привязываем его к текущему фрейму
    drawPane = new BackPanel (this, wxT("Calc_pict/calcApp.png"), wxBITMAP_TYPE_PNG, wxT("Calc_pict/mem.png"));
    //  Создаем еще одну панель. На нее также можно будет поместить sizer или gridsizer
    //  gridsizer нужен для равномерного размещения объектов по строкам и стобцам
    //  Добавляем к sizer планшет
    main_sizer->Add (drawPane, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 0);
    //  Устанавливаем sizer на окно
    SetSizer(main_sizer);

    screen_text = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint(57, 20), wxSize(492, 90), wxTE_LEFT);
	//Устанавливаем размер шрифта
	screen_text->SetFont(wxFontInfo(30));
	//Устанавливаем цвет фона
	screen_text->SetBackgroundColour(*wxBLACK);
	//Устанавливаем цвет текста
	screen_text->SetForegroundColour(*wxRED);

    turn_button = new wxButton (this, ID_BUT_TURN, wxT("Turn"), wxPoint (36, 195));
    turn_button->SetForegroundColour (*wxRED);
    turn_button->SetBackgroundColour(*wxBLACK);
    Connect (ID_BUT_TURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler (CalcFrame::Click_turn));

    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            prog_number[j][i] = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint (650+120*j, 50+41*i), wxSize (50, 40), wxTE_CENTRE);
            std::string command_number = dec_to_six (i+6*j);
            prog_number[j][i]->ChangeValue (command_number);
            prog_number[j][i]->SetFont (wxFontInfo (20));
            prog_number[j][i]->SetForegroundColour (*wxRED);
            wxString code_value = wxString::Format (wxT ("%d"), i+6*j+1);
            prog_code[j][i] = new wxTextCtrl (this, ID_SCREEN, wxT(""), wxPoint (701+120*j, 50+41*i), wxSize (50, 40), wxTE_CENTRE);
            //prog_code[j][i]->ChangeValue (command_number);
            prog_code[j][i]->SetFont (wxFontInfo (20));
            prog_code[j][i]->SetForegroundColour (*wxRED);
        }
    }

    wxColour* reg_fon_colour = new wxColour (223, 136, 136);
    for (int i = 0; i < 8; i++) {
        reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000"), wxPoint (710, 451+40*i), wxSize (155, 39), wxTE_CENTRE);
        reg_value[i]->SetFont (wxFontInfo (20));
        reg_value[i]->SetForegroundColour (*wxBLUE);
        reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    for (int i = 0; i < 3; i++) {
        rotate_reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000"), wxPoint (923+i*179, 564), wxSize (156, 43), wxTE_CENTRE);
        rotate_reg_value[i]->SetFont (wxFontInfo (20));
        rotate_reg_value[i]->SetForegroundColour (*wxBLUE);
        rotate_reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    for (int i = 3; i < 6; i++) {
        rotate_reg_value[i] = new wxTextCtrl (this, ID_SCREEN, wxT ("00000000"), wxPoint (942+(i-3)*179, 719), wxSize (156, 43), wxTE_CENTRE);
        rotate_reg_value[i]->SetFont (wxFontInfo (20));
        rotate_reg_value[i]->SetForegroundColour (*wxBLUE);
        rotate_reg_value[i]->SetBackgroundColour(*reg_fon_colour);
    }

    // Изображение для кнопки
    wxBitmapButton *anybutton; //пока что не понятно, нужнен ли этот указатель
    //wxImage plus_pict(wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG);
    new wxBitmapButton(drawPane, ID_BUT_PLUS, wxBitmap(wxImage (wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG)), wxPoint(420, 529));
    Connect (ID_BUT_PLUS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CalcFrame::ButtonClick));

    wxImage minus_pict(wxT("Calc_pict/minus.png"), wxBITMAP_TYPE_PNG);
    anybutton = new wxBitmapButton (drawPane, ID_BUT_MINUS, wxBitmap(minus_pict), wxPoint(420, 643));
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
    Maximize (true);
    Centre(); //окно раскроется в центре экрана
};

bool CalcFrame::turn_pressed = false;

CalcFrame::~CalcFrame() {
    //wxMessageBox(wxT("Деструктор работает"));
    //  Убираем панель
    drawPane->Destroy();
    //  Закрываем окно
    Close (true);
};

//  Функции при нажатии на кнопки
void CalcFrame::ButtonClick (wxCommandEvent &event) { //пока что обработчик нажатия делает разные вещи, чтобы мне разобраться во всём
    if (turn_pressed == false) {
        return;
    }
    int ID = event.GetId();
    //std::string IDnum = std::to_string (ID);
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
    if (turn_pressed == false) {
        turn_button->SetForegroundColour (*wxBLACK);
        turn_button->SetBackgroundColour (*wxRED);
        screen_text->ChangeValue ("0          +00");
        /*prog_number[0][0]->SetBackgroundColour (*wxWHITE);
        prog_code[0][0]->SetBackgroundColour (*wxWHITE);*/
        //в процессе уточнения как лучше сделать и нужно ли вообще менять цвет фона 
        //программы для того, чтобы ходить по ней, лучше добавить флаг, то есть номер программы
        //и по ней потом определять какой номер нужно подсветить
        turn_pressed = true;
        return;
    }
    if (turn_pressed == true) {
        null_everything ();
        turn_button->SetForegroundColour (*wxRED);
        turn_button->SetBackgroundColour (*wxBLACK);
        turn_pressed = false;
        return;
    }
}

std::string CalcFrame::dec_to_six (int a) { //если надо будет добавить нумерацию аля 00, 01, 02, то добавлю, это дело 2-х минут
    std::string number, ost;
    while (a / 6 != 0) {
        ost = std::to_string (a % 6);
        number = ost + number;
        a = a / 6;
    }
    ost = std::to_string (a);
    number = ost + number;
    return number;
}

void CalcFrame::null_everything () {
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            prog_code[j][i]->ChangeValue ("");
        }
    }
    for (int i = 0; i < 8; i++) {
        reg_value[i]->ChangeValue ("00000000");
    }
    for (int i = 0; i < 6; i++) {
        rotate_reg_value[i]->ChangeValue ("00000000");
    }
    screen_text->ChangeValue ("");
    return;
}

void CalcFrame::pressSec(wxCommandEvent &event) {
    wxMessageBox(wxT("Нажали на минус"));
}
// ----------------------------------------
// Приложение

class CalcApp:public wxApp {
    CalcFrame *frame;
public:
    bool OnInit() {
        frame = new CalcFrame(wxT("БК-21"));
        frame->Show();
        //  Главное окно долно быть сверху и будет убираться последним
        SetTopWindow (frame);
        return true;
    }

    int OnExit() {
        //wxMessageBox(wxT("Все удалаяем"));
        return 0;
    }
};

IMPLEMENT_APP (CalcApp)
