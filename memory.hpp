#include <iostream>
#include <array>

class Memory final{

	using arifmetic_type =  double;
	std::array<arifmetic_type, 16> regs_;
	arifmetic_type &x_reg_ = regs_[0];
	arifmetic_type &y_reg_ = regs_[7];

		
public:
	void mem_print() { 
		for (int i = 0; i < 16; i++)
			std::cout << regs_[i] << " "; 
	}

	void negate_x () { x_reg_ = -x_reg_; }
	void reset_x () { x_reg_ = 0; }

   
   	void swap_xy () { std::swap (x_reg_, y_reg_); }
	
	void set_x (arifmetic_type val) { x_reg_ = val; }
  	void set_y (arifmetic_type val) { y_reg_ = val; }

  
  	void left_rotate ()
   
   	{
       
		std::rotate (regs_.begin(), regs_.begin() + 1, regs_.end() - 9);
   
   	 }

   
   	void right_rotate ()
   
        {
       
		std::rotate (regs_.rbegin() - 9, regs_.rbegin() + 1, regs_.rend());
   
        }
};


