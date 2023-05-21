#include "back_panel.hpp"

namespace ussr
{

BackPanel::BackPanel (wxFrame *parent, wxString file, wxString file2, wxBitmapType format)
                     : wxPanel(parent)
{
    image.LoadFile (file, format);
    image2.LoadFile (file2, format);
    Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
}

void BackPanel::setImage (wxDC &dc)
{
    dc.DrawBitmap (image, 0, 0, false);
    dc.DrawBitmap (image2, 630, 450, false);
}

void BackPanel::paintEvent (wxPaintEvent &evt)
{
    wxPaintDC dc (this);
    setImage(dc);
}

#if 0
void BackPanel::paintBack ()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    setImage(dc);
}
#endif

} // namespace ussr
