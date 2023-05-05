#include <array>
#include <algorithm>
#include <cmath>

namespace ct
{

// buffered input

struct Button {};

struct Digit : public Button
{
    double digit_;
};

struct Biniary_Op : public Button
{
    virtual double operation (double x, double y) = 0;
};

struct Plus : public Biniary_Op
{
    double operation (double x, double y) override { return x + y; }
};

struct Minus : public Biniary_Op
{
    double operation (double x, double y) override { return x - y; }
};

struct Mult : public Biniary_Op
{
    double operation (double x, double y) override { return x * y; }
};

struct Div : public Biniary_Op
{
    double operation (double x, double y) override { return x / y; }
};

struct X_Pow_Y : public Biniary_Op
{
    double operation (double x, double y) override { return std::pow (x, y); }
};

struct Unary_Op : public Button
{
    virtual double operation (double x) = 0;
};

struct Swap_XY : public Button {};
struct Order : public Button {};
struct Point : public Button {};
struct UMinus : public Button {};
struct Move_To_Y : public Button {};

enum class Buttons
{
    nothing, // default value; no button has been pressed

    up_arrow,
    
    jump,
    stop_run,
    
    addr_inc,
    addr_dec
};

enum class Opcode
{

};

class Memory final
{
    using arithmetic_type = double;
    
    std::array<arithmetic_type, 7> enumerated_regs_;
    std::array<arithmetic_type, 7> cyclic_buffer_;
    arithmetic_type &x_reg_ = cyclic_buffer_[0];
    arithmetic_type &y_reg_ = enumerated_regs_[0];

public:

    void negate_x () noexcept { x_reg_ = -x_reg_; }
    void reset_x () noexcept { x_reg_ = 0; }

    void swap_xy () noexcept { std::swap (x_reg_, y_reg_); }

    void set_y (arithmetic_type val) noexcept { y_reg_ = val; }

    void left_rotate ()
    {
        std::rotate (cyclic_buffer_.begin(), cyclic_buffer_.begin() + 1, cyclic_buffer_.end());
    }

    void right_rotate ()
    {
        std::rotate (cyclic_buffer_.rbegin(), cyclic_buffer_.rbegin() + 1, cyclic_buffer_.rend());
    }
};

class Calculator final
{
    bool F_flag = false;
    bool P_flag = false; 
    
    void press_button (Buttons button)
    {

    }
};

} // namespace ct
