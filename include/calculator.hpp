#ifndef INCLUDE_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_HPP

#include <array>

#include "memory.hpp"
#include "buttons.hpp"

namespace ussr
{

class Soviet_Calculator final
{
    using handler = void (Soviet_Calculator::*) ();
    
    Memory mem_;
    int exp_;

    bool P_flag_ = false;
	bool F_flag_ = false;
    bool comma_flag_ = false;
    bool exp_flag_ = false;

    unsigned significand_digits_ = 0;
    unsigned exp_digits_ = 0;

    std::array<handler, Button_ID::END_ - Button_ID::BEGIN_ - 11> handlers_;

public:

    Soviet_Calculator ();

    void handle_button (Button_ID id);

    #ifdef DEBUG
    void debug_print ();
    #endif // DEBUG

private:

    void reset ();

    void plus ();
    void minus ();
    void mult ();
    void div ();
    void pow ();
    void swap_x_y ();
    void up_arrow ();
    void clear ();
    void negate ();
    void comma ();
    void set_P ();
    void set_F ();
    void step_left ();
    void step_right ();
    void input_exp ();
    void digits_handler (unsigned digit);
};

} // namespace ussr

#endif // INCLUDE_CALCULATOR_HPP
