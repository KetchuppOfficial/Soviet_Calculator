#include "application.hpp"

namespace ussr
{

bool CalcApp::OnInit()
{
    frame = new CalcFrame{wxT("БК-21")};
    frame->Show();
    SetTopWindow (frame);

    return true;
}

} // namespace ussr

IMPLEMENT_APP (ussr::CalcApp)
