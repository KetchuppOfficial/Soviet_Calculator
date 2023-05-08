#ifndef BUTTONS_HPP
#define BUTTONS_HPP

namespace ct {

enum class Buttons
{
    zero = 0,
    one,
    two, 
    three, 
    four,
    five,
    six,
    seven,
    eight,
    nine,
    comma,
    negate,
    input_programm, //ВП
    F,
    div,
    minus,
    plus,
    multiple,
    swap_x_y,
    up_arrow, //стрелочка (in reg Y)
    clear,
    P,
    pow,
    unconditional_jump, // БП
    subprogramm, // ПП/Т
    start_stop, // СТ
    reset_address, // ВО
    step_left,
    step_right,
    on_off
};

} //namespace ct

#endif
