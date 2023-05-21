#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <cmath>

#include "calculator.hpp"

namespace ussr
{

void Soviet_Calculator::reset_flags ()
{
    P_flag_ = false;
    F_flag_ = false;
    comma_flag_ = false;
    exp_flag_ = false;
    prev_op_flag_ = false;
    significand_digits_ = 0;
    after_comma_ = 0;
    exp_digits_ = 0;
    exp_ = 0;
}

void Soviet_Calculator::plus ()
{    
    #ifdef DEBUG
    std::cout << "PLUS pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::sin(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_x() + mem_.get_y());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
}

void Soviet_Calculator::minus ()
{
    #ifdef DEBUG
    std::cout << "MINUS pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::cos(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() - mem_.get_x());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
}

void Soviet_Calculator::mult ()
{
    #ifdef DEBUG
    std::cout << "MULT pressed" << std::endl;
    #endif // DEBUG
    
    constexpr double pi = 3.14159265359;
    
    if (P_flag_) {
        mem_.set_x(pi);
        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() * mem_.get_x());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
}

void Soviet_Calculator::div ()
{
    #ifdef DEBUG
    std::cout << "DIV pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::exp(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() / mem_.get_x());
        F_flag_ = false;
    }
    
    prev_op_flag_ = true;
}

void Soviet_Calculator::pow ()
{
    #ifdef DEBUG
    std::cout << "POW pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) { 
        //НОП
        P_flag_ = false;
    }
    else {
        mem_.set_x(std::pow(mem_.get_x(), mem_.get_y()));
        F_flag_ = false;
        prev_op_flag_ = true;
    }
}

void Soviet_Calculator::swap_x_y ()
{
    #ifdef DEBUG
    std::cout << "SWAP pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) {
        mem_.set_x(std::log(mem_.get_x()));
        P_flag_ = false;
    }
    else {
        mem_.swap_xy();
        F_flag_ = false;
    }

    prev_op_flag_ = true;
}

void Soviet_Calculator::up_arrow ()
{
    #ifdef DEBUG
    std::cout << "UPARROW pressed" << std::endl;
    #endif // DEBUG
    
    if (P_flag_) { 
        //e^ix
        P_flag_ = false;
    }
    else {
        mem_.set_y(mem_.get_x());
        prev_op_flag_ = true;
    }
}

void Soviet_Calculator::clear ()
{
    #ifdef DEBUG
    std::cout << "CX pressed" << std::endl;
    #endif // DEBUG
    
    mem_.reset_x();
    reset_flags();
}

void Soviet_Calculator::negate ()
{
    #ifdef DEBUG
    std::cout << "SIGN pressed" << std::endl;
    #endif // DEBUG
    
    if (F_flag_) { 
        auto x = mem_.get_x();
        mem_.set_x(x * x);

        F_flag_ = false;
        prev_op_flag_ = true;
    }
    else {
        if (exp_flag_)
            exp_ = -exp_;
        else
            mem_.negate_x();

        P_flag_ = false;
        comma_flag_ = false;
    }
}

void Soviet_Calculator::comma ()
{
    #ifdef DEBUG
    std::cout << "COMMA pressed" << std::endl;
    #endif // DEBUG
    
    if (F_flag_) { 
        auto x = mem_.get_x();
        if (x != 0)
            mem_.set_x(1 / x);

        F_flag_ = false;
        prev_op_flag_ = true;
    }
    else {
        comma_flag_ = true;
        P_flag_ = false;
    }
}

void Soviet_Calculator::set_P ()
{
    P_flag_ = true;
    F_flag_ = false;
}

void Soviet_Calculator::set_F ()
{
    F_flag_ = true;
    P_flag_ = false;
}

void Soviet_Calculator::step_left ()
{
    if (P_flag_) { 
        //PП
        P_flag_ = false;
    }
    else {
        mem_.left_rotate();
        F_flag_ = false;
    }
}

void Soviet_Calculator::step_right ()
{
    if (P_flag_) { 
        //PP
        P_flag_ = false;
    }
    else {
        mem_.right_rotate();
        F_flag_ = false;
    }
}

void Soviet_Calculator::input_exp () //ВП = ввод порядка
{
    #ifdef DEBUG
    std::cout << "VP pressed" << std::endl;
    #endif // DEBUG
    
    if (F_flag_) { 
        auto x = mem_.get_x();
        if (x >= 0) {
            mem_.set_x(std::sqrt(x));
            prev_op_flag_ = true;   
        }

        F_flag_ = false;
    }
    else {
        exp_flag_ = true;
        P_flag_ = false;
        comma_flag_ = false;
    }
}

void Soviet_Calculator::digits_main_case (unsigned digit)
{
    if (prev_op_flag_)
    {
        mem_.set_y(mem_.get_x());
        clear();
    }
    
    if (exp_flag_ == false)
    {
        if (significand_digits_ < 8)
        {
            if (comma_flag_)
            {
                after_comma_++;
                mem_.set_x (mem_.get_x() + digit * std::pow (10, -after_comma_));
            }
            else
                mem_.set_x (mem_.get_x() * 10 + digit);

            significand_digits_++;
        }  
    }    
    else
    {
        if (exp_digits_ < 2)
        {
            exp_ = exp_ * 10 + digit;
            exp_digits_++;
        }
        else
        {
            exp_ = (std::abs (exp_) % 10) * 10 + digit;
            exp_digits_ = 1;
        }
    }
}

void Soviet_Calculator::digits_handler (unsigned digit)
{
    #ifdef DEBUG
    std::cout << digit << " pressed" << std::endl;
    #endif // DEBUG

    if (P_flag_)
    {
        mem_[digit] = mem_.get_x();
        P_flag_ = false;
    }
    else if (F_flag_)
    {
        mem_.set_x (mem_[digit]);
        F_flag_ = false;
    }
    else
        digits_main_case (digit);
}

Soviet_Calculator::Soviet_Calculator ()
{
    handlers_[0] = &Soviet_Calculator::plus;
    handlers_[1] = &Soviet_Calculator::minus;
    handlers_[2] = &Soviet_Calculator::mult;
    handlers_[3] = &Soviet_Calculator::div;
    handlers_[4] = &Soviet_Calculator::pow;
    handlers_[5] = &Soviet_Calculator::swap_x_y;
    handlers_[6] = &Soviet_Calculator::up_arrow;
    handlers_[7] = &Soviet_Calculator::clear;
    handlers_[8] = &Soviet_Calculator::negate;
    handlers_[9] = &Soviet_Calculator::comma;
    handlers_[10] = &Soviet_Calculator::set_P;
    handlers_[11] = &Soviet_Calculator::set_F;
    handlers_[12] = &Soviet_Calculator::step_left;
    handlers_[13] = &Soviet_Calculator::step_right;
    handlers_[14] = &Soviet_Calculator::input_exp;
}

void Soviet_Calculator::handle_button (Button_ID id)
{
    if (Button_ID::ZERO <= id && Button_ID::NINE)
        digits_handler (id - Button_ID::ZERO);
    else
    {
        auto handler = handlers_[id - Button_ID::BEGIN_ - 1];
        (this->*handler)();
    }
}

void Soviet_Calculator::reset ()
{
    reset_flags ();
    mem_.reset();
}

const Memory &Soviet_Calculator::get_memory () const { return mem_; }

int Soviet_Calculator::get_digits_after_comma () const { return after_comma_; }

bool Soviet_Calculator::get_comma_flag () const { return comma_flag_; }

bool Soviet_Calculator::get_prev_op_flag () const { return prev_op_flag_; }

#ifdef DEBUG

void Soviet_Calculator::debug_print ()
{
    std::cout << "x: " << mem_.get_x() << std::endl;
    std::cout << "y: " << mem_.get_y() << std::endl;
    std::cout << "exp: " << exp_ << std::endl;

    std::cout << "P_flag: " << std::boolalpha << P_flag_ << std::endl;
    std::cout << "F_flag: " << std::boolalpha << F_flag_ << std::endl;
    std::cout << "comma_flag_: " << std::boolalpha << comma_flag_ << std::endl;
    std::cout << "exp_flag_: " << std::boolalpha << exp_flag_ << std::endl;

    std::cout << "significand_digits: " << significand_digits_ << std::endl;
    std::cout << "after_comma: " << after_comma_ << std::endl;
    std::cout << "exp_digits: " << exp_digits_ << std::endl;

    std::cout << "memory: ";
    mem_print (mem_);
}

#endif // DEBUG

} // namespace ussr
