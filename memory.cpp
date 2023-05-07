#include "memory.hpp"


void Memory::mem_print() { 
	for (int i = 0; i < 16; i++)
		std::cout << regs_[i] << " "; 
	std::cout<<"\n";	
	}
void Memory::drum_print() {
	for (int i = 0; i < 7; i++)
			std::cout << regs_[i] << " ";	
	std::cout <<"\n";
}
void Memory::negate_x () { x_reg_ = -x_reg_; }

void Memory::reset_x () { x_reg_ = 0; }

void Memory::swap_xy () { std::swap (x_reg_, y_reg_); }

void Memory::set_x (arifmetic_type val) { x_reg_ = val; }

void Memory::set_y (arifmetic_type val) { y_reg_ = val; }

void Memory::set_Pregs (int regnum, arifmetic_type val){
	regnum+=6;
    if ((regnum > 15) || (regnum < 8))
		return;
    regs_[regnum] = val;
}
Memory::arifmetic_type Memory::get_Pregs (int regnum){
	regnum+=6;
    if ((regnum > 15) || (regnum < 8))
		return 0;
    return regs_[regnum];	
}
  
void Memory::left_rotate () {
    std::rotate (regs_.begin(), regs_.begin() + 1, regs_.end() - 9);}

   
void Memory::right_rotate () {
    std::rotate (regs_.rbegin() + 9, regs_.rbegin()+ 10, regs_.rend());}


		
