#ifndef INCLUDE_APPLICATION_HPP
#define INCLUDE_APPLICATION_HPP

#include "interface.hpp"

namespace ussr
{

class CalcApp : public wxApp
{
    CalcFrame *frame;

public:

    bool OnInit() override;
};

} // namespace ussr

#endif // INCLUDE_APPLICATION_HPP
