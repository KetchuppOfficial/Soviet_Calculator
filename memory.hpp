#include <array>

class Memory final{
	using arifmetic_type =  double;
	std::array<arifmetic_type, 16> regs_;
	arifmetic_type &x_reg_ = regs_[0];
	arifmetic_type &y_reg_ = regs_[7];

public:
	void mem_print();
	void drum_print();
	
	void negate_x ();
	void reset_x ();

   	void swap_xy ();
	
	void set_x (arifmetic_type val);
  	void set_y (arifmetic_type val);
	void set_Pregs (int regnum, arifmetic_type val);
	
	arifmetic_type get_Pregs (int regnum);

  	void left_rotate ();
   	void right_rotate ();
};


