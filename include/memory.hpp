#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <vector>

namespace ussr
{

class Memory final
{
	using arifmetic_type = double;
	std::array<arifmetic_type, 16> regs_;
	arifmetic_type &x_reg_ = regs_[0];
	arifmetic_type &y_reg_ = regs_[7];

	std::array<std::size_t, 60> cmd_stack_regs_;
	size_t step_ptr_ = 0;

public:
	//----------------------------work mode----------------------------//

	arifmetic_type operator [] (std::size_t i) const;
	void negate_x ();
	void reset_x ();
	void set_y_from_x();
   	void swap_xy ();
	
	void set_x (arifmetic_type val);
	arifmetic_type get_x () const;

  	void set_y (arifmetic_type val);
	arifmetic_type get_y () const;

	void set_Pregs (std::size_t regnum, arifmetic_type val);
	arifmetic_type get_Pregs (std::size_t regnum) const;

  	void left_rotate ();
   	void right_rotate ();	

	std::size_t n_work_regs () const;
	
	//--------------------------programming mode-------------------------//

	std::size_t get_cmd (std::size_t ptr) const;
	void set_cmd (std::size_t cmd);

	std::size_t set_step_ptr (std::size_t ptr);
	void reset_step_ptr ();
	std::size_t get_step_ptr () const;
	void inc_step_ptr ();
	void dec_step_ptr ();

	std::size_t n_prog_regs () const;
};

void mem_print (const Memory& memory);
std::size_t ptr_check (std::size_t ptr);

} // namespace ussr

#endif