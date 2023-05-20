#ifndef INCLUDE_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_HPP

#include <array>

#include "memory.hpp"
#include "buttons.hpp"

namespace ussr
{

class Soviet_Calculator final
{
    using handler = void (*) (Soviet_Calculator &);
    
    Memory mem_;
    int exp_;

    bool P_flag_ = false;
	bool F_flag_ = false;
    bool comma_flag_ = false;
    bool exp_flag_ = false;

    std::pair<unsigned, unsigned> digits_{};

    std::array<handler, Button_ID::END_ - Button_ID::BEGIN_ - 11> handlers_;

public:

    Soviet_Calculator ();

    void handle_button (Button_ID id);

    bool get_P_flag() const;
    void set_P_flag();
    void reset_P_flag ();

    bool get_F_flag() const;
    void set_F_flag();
    void reset_F_flag ();

    bool get_comma_flag() const;
    void set_comma_flag();
    void reset_comma_flag();

    bool get_exp_flag() const;
    void set_exp_flag();
    void reset_exp_flag();

    unsigned get_significand_digits () const;
    void inc_significand_digits ();
    void reset_significand_digits ();

    unsigned get_exp_digits () const;
    void inc_exp_digits ();
    void reset_exp_digits ();

    int get_exp () const;
    void set_exp (int exp);
    void negate_exp ();

    Memory &get_memory();
    const Memory &get_memory() const;
};

} // namespace ussr

#endif // INCLUDE_CALCULATOR_HPP
