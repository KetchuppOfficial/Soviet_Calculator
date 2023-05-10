#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "memory.hpp"

namespace ct
{

//TODO: numbers

const double NUMBER_PI = 3.14159265359;

struct Instruction 
{
    virtual void execute(Memory& memory) = 0;
};

struct Plus : public Instruction 
{
    void execute(Memory& memory) override;
};

struct Minus : public Instruction 
{
    void execute(Memory& memory) override;
};

struct Mult : public Instruction 
{
    void execute(Memory& memory) override;
};

struct Div : public Instruction 
{
    void execute(Memory& memory) override;
};

struct Pow : public Instruction 
{
    void execute(Memory& memory) override;
};

struct Swap_x_y : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Up_arrow : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Clear : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Negate : public Instruction  
{
    void execute(Memory& memory) override;
};

struct set_P : public Instruction  
{
    void execute(Memory& memory) override;
};

struct set_F : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Step_left : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Step_right : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Reverse : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Squaring : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Sqrt : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Nop : public Instruction // 
{
    void execute(Memory& memory) override;
};

struct More_equal : public Instruction  //
{
    void execute(Memory& memory) override;
};

struct Equal : public Instruction  //
{
    void execute(Memory& memory) override;
};

struct Not_equal : public Instruction  //
{
    void execute(Memory& memory) override;
};

struct Less : public Instruction  //
{
    void execute(Memory& memory) override;
};

struct P_work : public Instruction // (PP) 
{
    void execute(Memory& memory) override;
};

struct P_prog : public Instruction  // (PП)
{
    void execute(Memory& memory) override;
};

struct Logariphm : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Pi : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Sin : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Cos : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Exponent : public Instruction  
{
    void execute(Memory& memory) override;
};

struct Return_clean : public Instruction  // (В/О)
{
    void execute(Memory& memory) override;
};

struct Stop_run : public Instruction  // (С/П)
{
    void execute(Memory& memory) override;
};

struct Jmp : public Instruction  // (БП)
{
    void execute(Memory& memory) override;
};

struct Subprog_step_run_in_work_mode : public Instruction  // (ПП/Т)
{
    void execute(Memory& memory) override;
};

struct Insert_exp : public Instruction  // (ВП)
{
    void execute(Memory& memory) override;
};

struct Comma : public Instruction  // (,)
{
    void execute(Memory& memory) override;
};

struct Power : public Instruction  // 
{
    void execute(Memory& memory) override;
};

#endif
