#include "calculator.hpp"

#include <cmath>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ussr
{

void Soviet_Calculator::reset_flags ()
{
    P_flag_ = false;
    F_flag_ = false;
    comma_flag_ = false;
    exp_flag_ = false;
    prog_flag_ = false;
    prev_op_flag_ = false;
    significand_digits_ = 0;
    after_comma_ = 0;
    exp_digits_ = 0;
    exp_ = 0;
}

static constexpr int offset = 30;
void Soviet_Calculator::add_cmd (const int base_id)
{
    static constexpr int nums_offset = 20;
    auto id = base_id;
    if (base_id >= handlers_.size ())
        id += nums_offset - handlers_.size(); 

    id += offset * P_flag_ + 2 * offset * F_flag_;

    mem_.set_cmd(id);
    mem_.inc_step_ptr();

    P_flag_ = false;
    F_flag_ = false;
}

void Soviet_Calculator::plus ()
{    
    #ifdef DEBUG
    std::cout << "PLUS pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(0);
    }
    else if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::sin(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_x() + mem_.get_y());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::minus ()
{
    #ifdef DEBUG
    std::cout << "MINUS pressed" << std::endl;
    #endif // DEBUG
    if (prog_flag_) {
        add_cmd(1);
    }
    else if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::cos(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() - mem_.get_x());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::mult ()
{
    #ifdef DEBUG
    std::cout << "MULT pressed" << std::endl;
    #endif // DEBUG
    
    constexpr double pi = 3.14159265359;
    
    if (prog_flag_) {
        add_cmd(2);
    }
    else if (P_flag_) {
        mem_.set_x(pi);
        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() * mem_.get_x());
        F_flag_ = false;
    }

    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::div ()
{
    #ifdef DEBUG
    std::cout << "DIV pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(3);
    }
    else if (P_flag_) {
        auto x = mem_.get_x();
        mem_.set_x(std::exp(x));

        P_flag_ = false;
    }
    else {
        mem_.set_x(mem_.get_y() / mem_.get_x());
        F_flag_ = false;
    }
    
    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::pow ()
{
    #ifdef DEBUG
    std::cout << "POW pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(4);
    }
    else if (P_flag_) { 
        //НОП
        P_flag_ = false;
    }
    else {
        mem_.set_x(std::pow(mem_.get_x(), mem_.get_y()));
        F_flag_ = false;
    }

    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::swap_x_y ()
{
    #ifdef DEBUG
    std::cout << "SWAP pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(5);
    }
    else if (P_flag_) {
        mem_.set_x(std::log(mem_.get_x()));
        P_flag_ = false;
    }
    else {
        mem_.swap_xy();
        F_flag_ = false;
    }

    comma_flag_ = false;
    prev_op_flag_ = true;
}

void Soviet_Calculator::up_arrow ()
{
    #ifdef DEBUG
    std::cout << "UPARROW pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(6);
    }
    else if (P_flag_) { 
        auto x = mem_.get_x();
        mem_.set_x(std::cos(x));
        mem_.set_y(std::sin(x));

        P_flag_ = false;
    }
    else {
        mem_.set_y(mem_.get_x());
    }

    prev_op_flag_ = true;
    comma_flag_ = false;
}

void Soviet_Calculator::clear ()
{
    #ifdef DEBUG
    std::cout << "CX pressed" << std::endl;
    #endif // DEBUG

    if (prog_flag_) {
        add_cmd(7);
    } 
    else {
        mem_.reset_x();
        reset_flags();
    }
}

void Soviet_Calculator::negate ()
{
    #ifdef DEBUG
    std::cout << "SIGN pressed" << std::endl;
    #endif // DEBUG

    if (prog_flag_) {
        add_cmd(8);
    }
    else if (F_flag_) { 
        auto x = mem_.get_x();
        mem_.set_x(x * x);

        F_flag_ = false;
        prev_op_flag_ = true;
    }
    else if (P_flag_) {
        mem_.right_rotate();
        P_flag_ = false;
    }
    else {
        if (exp_flag_)
            exp_ = -exp_;
        else
            mem_.negate_x();

        P_flag_ = false;
    }
}

void Soviet_Calculator::comma ()
{
    #ifdef DEBUG
    std::cout << "COMMA pressed" << std::endl;
    #endif // DEBUG

    if (prog_flag_) {
        add_cmd(9);
    }
    else if (F_flag_) { 
        auto x = mem_.get_x();
        if (x != 0)
            mem_.set_x(1 / x);

        F_flag_ = false;
        prev_op_flag_ = true;
    }
    else if (P_flag_) {
        mem_.left_rotate();
        P_flag_ = false;
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
    P_flag_ = false;
    F_flag_ = true;
}

int Soviet_Calculator::execute_command ()
{
    auto step_ptr = mem_.get_step_ptr();
    auto command_id = mem_.get_cmd(step_ptr);

    auto check_flags = command_id / offset;
    if (check_flags == 1)
        P_flag_ = true;
    else if (check_flags == 2)
        F_flag_ = true;

    auto id = command_id % offset;
    if (id >= 20) {
        digits_handler (id - 20);
        mem_.inc_step_ptr();
        return 0;
    } 
    else if (id == 16) {
        mem_.inc_step_ptr();
        return 16;
    }

    auto handler = handlers_[id];
    (this->*handler)();

    mem_.inc_step_ptr();
    return id;
}
void Soviet_Calculator::step_left ()
{
    if (P_flag_) { 
        prog_flag_ = false;
        P_flag_ = false;
    }
    else if (!prog_flag_) {
        execute_command ();
        mem_.set_step_ptr(mem_.get_step_ptr() - 2);
    }
    else {
        mem_.dec_step_ptr();
    }
}

void Soviet_Calculator::step_right ()
{
    if (P_flag_) { 
        prog_flag_ = true;
        P_flag_ = false;
    }
    else if (!prog_flag_) {
        execute_command ();
    }
    else {
        mem_.inc_step_ptr();
    }
}

void Soviet_Calculator::input_exp () 
{
    #ifdef DEBUG
    std::cout << "VP pressed" << std::endl;
    #endif // DEBUG
    
    if (prog_flag_) {
        add_cmd(14);
    }
    else if (F_flag_) { 
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

void Soviet_Calculator::vo ()
{
    if (prog_flag_) {
        add_cmd(15);
    }
    else if (P_flag_) { 
        auto x = mem_.get_x();
        if (x >= 0) {
            mem_.inc_step_ptr();
            mem_.set_step_ptr(mem_.get_cmd(mem_.get_step_ptr()) - 1);
        }
    }
    else {
        mem_.reset_step_ptr();
        F_flag_ = false;
    }
}

void Soviet_Calculator::sp ()
{
    if (prog_flag_) {
        add_cmd(16);
    }
    else if (P_flag_) { 
        auto x = mem_.get_x();
        if (x) {
            mem_.inc_step_ptr();
            mem_.set_step_ptr(mem_.get_cmd(mem_.get_step_ptr()) - 1);
        }
    }
    else {
        for (int i = 0; i != 36; ++i)
        {
            auto ex_id = execute_command ();
            if (ex_id == 16)
            {
                break;
            }
        }
    }
}

void Soviet_Calculator::bp ()
{
    if (prog_flag_) {
        add_cmd(17);
    }
    else if (P_flag_) { 
        auto x = mem_.get_x();
        if (!x) {
            mem_.inc_step_ptr();
            mem_.set_step_ptr(mem_.get_cmd(mem_.get_step_ptr()) - 1);
            P_flag_ = false;
        }
    }
    else {
        mem_.set_step_ptr(mem_.get_cmd(mem_.get_step_ptr() + 1) - 1); 

        F_flag_ = false;
    }
}

void Soviet_Calculator::pp ()
{
    if (prog_flag_) {
        add_cmd(18);
    }
    else if (P_flag_) { 
        auto x = mem_.get_x();
        if (x < 0) {
            mem_.inc_step_ptr();
            mem_.set_step_ptr(mem_.get_cmd(mem_.get_step_ptr()) - 1);
        }
    }
    else {
        //subprogramm
        F_flag_ = false;
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

    if (prog_flag_) { 
        add_cmd (digit + handlers_.size());
    }
    else if (P_flag_) {
        mem_.set_Pregs(digit, mem_.get_x());
        P_flag_ = false;
    }
    else if (F_flag_) {
        mem_.set_x (mem_.get_Pregs(digit));
        F_flag_ = false;
    }
    else
        digits_main_case (digit);
}

Soviet_Calculator::Soviet_Calculator ()
{
    mem_.reset ();
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
    handlers_[15] = &Soviet_Calculator::vo;
    handlers_[16] = &Soviet_Calculator::sp;
    handlers_[17] = &Soviet_Calculator::vo;
    handlers_[18] = &Soviet_Calculator::sp;
}

void Soviet_Calculator::handle_button (Button_ID id)
{
    if (Button_ID::ZERO <= id && id <= Button_ID::NINE)
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
