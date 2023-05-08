#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "memory.hpp"

namespace ct
{

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

#endif
