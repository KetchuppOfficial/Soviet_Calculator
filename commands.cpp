#include <cmath>

#include "commands.hpp"

namespace ct
{

void Plus_instruction::execute(Memory& memory)
{
    memory.set_x(memory.get_x() + memory.get_y());
}

void Minus_instruction::execute(Memory& memory)
{
    memory.set_x(memory.get_y() - memory.get_x());
}

void Mult_instruction::execute(Memory& memory)
{
    memory.set_x(memory.get_y() * memory.get_x());
}

void Div_instruction::execute(Memory& memory)
{
    memory.set_x(memory.get_y() / memory.get_x());
}

void Pow_instruction::execute(Memory& memory)
{
    memory.set_x(pow(memory.get_x(), memory.get_y()));
}

void Swap_x_y_instruction::execute(Memory& memory)
{
    memory.swap_xy();
}

void Up_arrow_instruction::execute(Memory& memory)
{
    memory.set_y(memory.get_x());
}

void Clear_instruction::execute(Memory& memory)
{
    memory.reset_x();
}

void Negate_instruction::execute(Memory& memory)
{
    memory.negate_x();
}

void P_instruction::execute(Memory& memory)
{
    memory.set_P();
}

void F_instruction::execute(Memory& memory)
{
    memory.set_F();
}

void Step_left_instruction::execute(Memory& memory)
{
    memory.left_rotate();
}

void Step_right_instruction::execute(Memory& memory)
{
    memory.right_rotate();
}

void Reverse_instruction::execute(Memory& memory)
{
    double x = memory.get_x();
    if (!x)
    {
        memory.set_x(1 / x);
    }
}

void Squaring_instruction::execute(Memory& memory)
{
    double x = memory.get_x();
    memory.set_x(x * x);
}

void Sqrt_instruction::execute(Memory& memory)
{
    double x = memory.get_x();
    if (x > 0)
    {
        memory.set_x(sqrt(x));
    }
}

} //namecpace ct
