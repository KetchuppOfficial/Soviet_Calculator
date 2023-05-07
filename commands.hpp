#include "memory.hpp"

namespace ct
{

struct Button {};

struct Digit : public Button
{
    double digit_;
};

enum class Buttons
{
    zero,
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

//TODO: numbers

struct Instruction 
{
    virtual void execute (Memory& memory) = 0;
};

struct Plus_instruction : public Instruction //+++
{
    void execute () override;
};

struct Minus_instruction : public Instruction //+++
{
    void execute () override;
};

struct Mult_instruction : public Instruction //+++
{
    void execute () override;
};

struct Div_instruction : public Instruction //+++
{
    void execute () override;
};

struct Pow_instruction : public Instruction //+++
{
    void execute () override;
};

struct Swap_x_y_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Up_arrow_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Clear_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Negate_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct P_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct F_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Step_left_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Step_right_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Reverse_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Squaring_instruction : public Instruction //+++ 
{
    void execute () override;
};

struct Sqrt_instruction : public Instruction //+++ 
{
    void execute () override;
};

