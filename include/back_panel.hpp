#ifndef INCLUDE_BACK_PANEL_HPP
#define INCLUDE_BACK_PANEL_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/string.h>

namespace ussr
{

class BackPanel : public wxPanel
{
    wxBitmap image;
    wxBitmap image2;

public:

    BackPanel (wxFrame *parent, wxString file, wxString file2, wxBitmapType format);
    void paintEvent (wxPaintEvent &evt);
    void setImage (wxDC &dc);
};

} // namespace ussr

#endif // INCLUDE_BACK_PANEL_HPP
