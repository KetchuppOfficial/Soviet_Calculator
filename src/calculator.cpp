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

void reset (Soviet_Calculator &calc)
{
    calc.reset_P_flag();
    calc.reset_F_flag();
    calc.reset_comma_flag();
    calc.reset_exp_flag();
    calc.reset_significand_digits();
    calc.reset_exp_digits();
    calc.set_exp (0);
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
        reset (calc);
    }
}

void clear (Soviet_Calculator &calc)
{
    calc.get_memory().reset_x();
    reset (calc);
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
        if (calc.get_exp_flag())
            calc.negate_exp();
        else
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
        calc.set_comma_flag();
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
        calc.set_exp_flag();
        calc.reset_P_flag();
    }
}

void digits_handler (Soviet_Calculator &calc, unsigned digit)
{
    auto &mem = calc.get_memory();

    if (calc.get_exp_flag() == false)
    {
        if (calc.get_significand_digits() < 8)
        {
            if (calc.get_comma_flag())
                mem.set_x (mem.get_x() + digit / 1.0);
            else
                mem.set_x (mem.get_x() * 10 + digit);

            calc.inc_significand_digits();
        }  
    }    
    else if (calc.get_exp_digits() < 2)
    {
        calc.set_exp (calc.get_exp() * 10 + digit);
        calc.inc_exp_digits();
    }
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
        digits_handler(*this, id - Button_ID::ZERO);
    else
    {
        auto handler = handlers_[id];
        handler (*this);
    }
}

bool Soviet_Calculator::get_P_flag() const { return P_flag_; }
void Soviet_Calculator::set_P_flag() { P_flag_ = true; }
void Soviet_Calculator::reset_P_flag() { P_flag_ = false; }

bool Soviet_Calculator::get_F_flag() const { return F_flag_;  }
void Soviet_Calculator::set_F_flag() { F_flag_ = true; }
void Soviet_Calculator::reset_F_flag() { F_flag_ = false; }

bool Soviet_Calculator::get_comma_flag() const { return comma_flag_; }
void Soviet_Calculator::set_comma_flag() { comma_flag_ = true; }
void Soviet_Calculator::reset_comma_flag() { comma_flag_ = false;}

bool Soviet_Calculator::get_exp_flag() const { return exp_flag_; }
void Soviet_Calculator::set_exp_flag() { exp_flag_ = true; }
void Soviet_Calculator::reset_exp_flag() { exp_flag_ = false;}

unsigned Soviet_Calculator::get_significand_digits () const { return digits_.first; }
void Soviet_Calculator::inc_significand_digits () { digits_.first++; }
void Soviet_Calculator::reset_significand_digits () { digits_.first = 0; }

unsigned Soviet_Calculator::get_exp_digits () const { return digits_.second; }
void Soviet_Calculator::inc_exp_digits () { digits_.second++; }
void Soviet_Calculator::reset_exp_digits () { digits_.second = 0; }

int Soviet_Calculator::get_exp () const { return exp_; }
void Soviet_Calculator::set_exp (int exp) { exp_ = exp; }
void Soviet_Calculator::negate_exp () { exp_ = -exp_; }

Memory &Soviet_Calculator::get_memory () { return mem_; }
const Memory &Soviet_Calculator::get_memory () const { return mem_; }

} // namespace ussr
