#ifndef INCLUDE_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_HPP

#include <array>

#include "memory.hpp"
#include "buttons.hpp"

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

    void handle_button (Button_ID id);

    bool get_P_flag();
    bool get_F_flag();

    void set_P_flag();
    void set_F_flag();

    void reset_P_flag ();
    void reset_F_flag ();
};

} // namespace ussr

#endif // INCLUDE_CALCULATOR_HPP
