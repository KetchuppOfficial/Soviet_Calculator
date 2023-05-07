#include "memory.hpp"


void Memory::mem_print() { 
		for (int i = 0; i < 16; i++)
			std::cout << regs_[i] << " "; 
	}
void Memory::negate_x () { x_reg_ = -x_reg_; }

void Memory::reset_x () { x_reg_ = 0; }

void Memory::swap_xy () { std::swap (x_reg_, y_reg_); }

void Memory::set_x (arifmetic_type val) { x_reg_ = val; }

void Memory::set_y (arifmetic_type val) { y_reg_ = val; }

  
void Memory::left_rotate () {
		std::rotate (regs_.begin(), regs_.begin() + 1, regs_.end() - 9);}

   
void Memory::right_rotate () {
    std::rotate (regs_.rbegin() - 9, regs_.rbegin() + 1, regs_.rend());}

int main()
{
	Memory mem;
	mem.mem_print();
	mem.set_x(5);
	mem.mem_print();
	return 0;
}
	
