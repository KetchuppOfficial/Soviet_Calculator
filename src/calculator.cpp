#include "calculator.hpp"

#include <cmath>

namespace ussr
{

namespace
{

constexpr double pi = 3.14159265359;

void plus (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) {
        auto x = mem.get_x();
        mem.set_x(std::sin(x));

        calc.reset_P_flag();
    }
    else {
        mem.set_x(mem.get_x() + mem.get_y());
        calc.reset_F_flag();
    }
}

void minus (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) {
        auto x = mem.get_x();
        mem.set_x(std::cos(x));

        calc.reset_P_flag();
    }
    else {
        mem.set_x(mem.get_y() - mem.get_x());
        calc.reset_F_flag();
    }
}

void mult (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) {
        mem.set_x(pi);
        calc.reset_P_flag();
    }
    else {
        mem.set_x(mem.get_y() * mem.get_x());
        calc.reset_F_flag();
    }
}

void div (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) {
        auto x = mem.get_x();
        mem.set_x(std::exp(x));

        calc.reset_P_flag();
    }
    else {
        mem.set_x(mem.get_y() / mem.get_x());
        calc.reset_F_flag();
    }
}

void pow (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) { 
        //НОП
        calc.reset_P_flag();
    }
    else {
        mem.set_x(std::pow(mem.get_x(), mem.get_y()));
        calc.reset_F_flag();
    }
}

void swap_x_y (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) { 
        auto x = mem.get_x();
        mem.set_x(std::log(x));

        calc.reset_P_flag();
    }
    else {
        mem.swap_xy();
        calc.reset_F_flag();
    }
}

void up_arrow (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) { 
        //e^ix
        calc.reset_P_flag();
    }
    else {
        mem.set_y(mem.get_x());
        calc.reset_F_flag();
    }
}

void clear (Soviet_Calculator &calc)
{
    calc.get_memory().reset_x();
    calc.reset_P_flag();
    calc.reset_F_flag();
}

void negate (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();

    if (calc.get_F_flag()) { 
        auto x = mem.get_x();
        mem.set_x(x * x);

        calc.reset_F_flag();
    }
    else {
        mem.negate_x();
        calc.reset_P_flag();
    }
}

void comma (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_F_flag()) { 
        auto x = mem.get_x();
        if (!x)
            mem.set_x(1 / x);

        calc.reset_F_flag();
    }
    else {
        //comma
        calc.reset_P_flag();
    }
}

void set_P (Soviet_Calculator &calc)
{
    calc.set_P_flag();
    calc.reset_F_flag();
}

void set_F (Soviet_Calculator &calc)
{
    calc.set_F_flag();
    calc.reset_P_flag();
}

void step_left (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();

    if (calc.get_P_flag()) { 
        //PП
        calc.reset_P_flag();
    }
    else {
        mem.left_rotate();
        calc.reset_F_flag();
    }
}

void step_right (Soviet_Calculator &calc)
{
    auto &mem = calc.get_memory();
    
    if (calc.get_P_flag()) { 
        //PP
        calc.reset_P_flag();
    }
    else {
        mem.right_rotate();
        calc.reset_F_flag();
    }
}

void input_exp (Soviet_Calculator &calc) //ВП = ввод порядка
{
    auto &mem = calc.get_memory();
    
    if (calc.get_F_flag()) { 
        auto x = mem.get_x();
        if (x >= 0) {
            mem.set_x(std::sqrt(x));
        }

        calc.reset_F_flag();
    }
    else {
        //ВП
        calc.reset_P_flag();
    }
}

void digits_handler (unsigned digit)
{
    // TBD
}

} // unnamed namespace

Soviet_Calculator::Soviet_Calculator ()
{
    handlers_[0] = plus;
    handlers_[1] = minus;
    handlers_[2] = mult;
    handlers_[3] = div;
    handlers_[4] = pow;
    handlers_[5] = swap_x_y;
    handlers_[6] = up_arrow;
    handlers_[7] = clear;
    handlers_[8] = negate;
    handlers_[9] = comma;
    handlers_[10] = set_P;
    handlers_[11] = set_F;
    handlers_[12] = step_left;
    handlers_[13] = step_right;
    handlers_[14] = input_exp;
}

void Soviet_Calculator::handle_button (Button_ID id)
{
    if (Button_ID::ZERO <= id && Button_ID::NINE)
        digits_handler(id - Button_ID::ZERO);
    else
    {
        auto handler = handlers_[id];
        handler (*this);
    }
}

bool Soviet_Calculator::get_P_flag()
{
    return P_flag_; 
}

bool Soviet_Calculator::get_F_flag()
{
    return F_flag_; 
}

void Soviet_Calculator::set_P_flag()
{
    P_flag_ = true; 
}

void Soviet_Calculator::set_F_flag()
{
    F_flag_ = true; 
}

void Soviet_Calculator::reset_P_flag()
{
    P_flag_ = false; 
}

void Soviet_Calculator::reset_F_flag()
{
    F_flag_ = false; 
}

Memory &Soviet_Calculator::get_memory () { return mem_; }
const Memory &Soviet_Calculator::get_memory () const { return mem_; }

} // namespace ussr
