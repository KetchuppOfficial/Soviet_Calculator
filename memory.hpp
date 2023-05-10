#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <iostream>

class Memory final{
	using arifmetic_type =  double;
	std::array<arifmetic_type, 16> regs_;
	arifmetic_type &x_reg_ = regs_[0];
	arifmetic_type &y_reg_ = regs_[7];

	bool P_flag = 0;
	bool F_flag = 0;

public:
	void negate_x ();
	void reset_x ();

   	void swap_xy ();
	
	void set_x (arifmetic_type val);
	arifmetic_type get_x ();

  	void set_y (arifmetic_type val);
	arifmetic_type get_y ();

	void set_P_flag (bool val);
	bool get_P_flag ();

	void set_F_flag (bool val);
	bool get_F_flag ();

	void set_Pregs (int regnum, arifmetic_type val);
	arifmetic_type get_Pregs (int regnum);

  	void left_rotate ();
   	void right_rotate ();

	static void mem_print(Memory& memory);
	static void drum_print(Memory& memory);
};

#endif