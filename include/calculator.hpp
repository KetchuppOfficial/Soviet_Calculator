#ifndef INCLUDE_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_HPP

#include <array>

#include "memory.hpp"
#include "commands.hpp"
#include "interface_raw.hpp"

namespace ussr
{

class Soviet_Calculator final
{
    using handler = void (*) (Soviet_Calculator &);
    
    Memory mem_;

    bool P_flag_ = false;
	bool F_flag_ = false;

    std::array<handler, ID_END_ - ID_BEGIN_ - 1> handlers_;

public:

    Soviet_Calculator ();

    void handle_button (BUTTONS_ids id);
};

} // namespace ussr

#endif // INCLUDE_CALCULATOR_HPP
