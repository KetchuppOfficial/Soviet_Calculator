#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>

namespace ussr
{

class Memory final
{
	using arifmetic_type = double;
	std::array<arifmetic_type, 16> regs_;
	arifmetic_type &x_reg_ = regs_[0];
	arifmetic_type &y_reg_ = regs_[7];

	bool P_flag_ = false;
	bool F_flag_ = false;

public:
	arifmetic_type operator [] (std::size_t i) const;
	void negate_x ();
	void reset_x ();

   	void swap_xy ();
	
	void set_x (arifmetic_type val);
	arifmetic_type get_x () const;

  	void set_y (arifmetic_type val);
	arifmetic_type get_y () const;

	void set_P_flag (bool val);
	bool get_P_flag () const;

	void set_F_flag (bool val);
	bool get_F_flag () const;

	void set_Pregs (std::size_t regnum, arifmetic_type val);
	arifmetic_type get_Pregs (std::size_t regnum) const;

  	void left_rotate ();
   	void right_rotate ();	

	size_t n_regs () const;
};

void mem_print (const Memory& memory);

} // namespace ussr

#endif
