#include "calculator.hpp"

namespace ussr
{

namespace
{

void plus (Soviet_Calculator &calc)
{
    calc.mem_.set_x(calc.mem_.get_x() + calc.mem_.get_y());
}

void plus (Soviet_Calculator &calc)
{
    memory.set_x(memory.get_y() - memory.get_x());
}

void Mult::execute(Memory &memory)
{
    memory.set_x(memory.get_y() * memory.get_x());
}

void Div::execute(Memory &memory)
{
    memory.set_x(memory.get_y() / memory.get_x());
}

void Pow::execute(Memory &memory)
{
    memory.set_x(pow(memory.get_x(), memory.get_y()));
}

void Swap_x_y::execute(Memory &memory)
{
    memory.swap_xy();
}

void Up_arrow::execute(Memory &memory)
{
    memory.set_y(memory.get_x());
}

void Clear::execute(Memory &memory)
{
    memory.reset_x();
}

void Negate::execute(Memory &memory)
{
    memory.negate_x();
}

void set_P::execute(Memory &memory)
{
    memory.set_P_flag(true);
}

void set_F::execute(Memory &memory)
{
    memory.set_F_flag(true);
}

void Step_left::execute(Memory &memory)
{
    memory.left_rotate();
}

void Step_right::execute(Memory &memory)
{
    memory.right_rotate();
}

void Reverse::execute(Memory &memory)
{
    auto x = memory.get_x();
    if (!x) {
        memory.set_x(1 / x);
    }
}

void Squaring::execute(Memory &memory)
{
    auto x = memory.get_x();
    memory.set_x(x * x);
}

void Sqrt::execute(Memory &memory)
{
    auto x = memory.get_x();
    if (x > 0) {
        memory.set_x(std::sqrt(x));
    }
}

void Logariphm::execute(Memory &memory)
{
    auto x = memory.get_x();
    memory.set_x(std::log(x));
}

void Sin::execute(Memory &memory)
{
    auto x = memory.get_x();
    memory.set_x(std::sin(x));
}

void Cos::execute(Memory &memory)
{
    auto x = memory.get_x();
    memory.set_x(std::cos(x));
}

void Exponent::execute(Memory &memory)
{
    auto x = memory.get_x();
    memory.set_x(std::exp(x));
}

} // unnamed namespace

Soviet_Calculator::Soviet_Calculator ()
{
    handlers_[0] = plus;
    handlers_[0] = minus;
    handlers_[0] = mult;
    handlers_[0] = div;
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
    handlers_[0] = 
}

Soviet_Calculator::handle_button (BUTTONS_ids id)
{
    auto handler = handlers_[id];
    handler();
}


} // namespace ussr
