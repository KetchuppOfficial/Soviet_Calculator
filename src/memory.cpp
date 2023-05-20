#include <iostream>
#include "memory.hpp"

namespace ussr
{

typename Memory::arifmetic_type Memory::operator[](std::size_t i) const
{
    return regs_[i];
}

void Memory::negate_x()
{
	 x_reg_ = -x_reg_;
}

void Memory::reset_x () 
{ 
	x_reg_ = 0; 
}

void Memory::set_y_from_x()
{
	y_reg_ = x_reg_;
}

void Memory::swap_xy () 
{
	std::swap (x_reg_, y_reg_); 
}

void Memory::set_x (arifmetic_type val) 
{ 
	x_reg_ = val; 
}

typename Memory::arifmetic_type Memory::get_x () const
{ 
	return x_reg_; 
}

void Memory::set_y (arifmetic_type val) 
{ 
	y_reg_ = val; 
}

Memory::arifmetic_type Memory::get_y () const 
{ 
	return y_reg_; 
}

void Memory::set_Pregs (std::size_t regnum, arifmetic_type val)
{
	regnum+=6;
    if ((regnum > 15) || (regnum < 8))
		return;
    regs_[regnum] = val;
}

Memory::arifmetic_type Memory::get_Pregs (std::size_t regnum) const
{
	regnum += 6;
    if ((regnum > 15) || (regnum < 8))
		return 0;
    return regs_[regnum];	
}
  
void Memory::left_rotate () 
{
    std::rotate (regs_.begin(), regs_.begin() + 1, regs_.end() - 9);
}  

void Memory::right_rotate () 
{
    std::rotate (regs_.rbegin() + 9, regs_.rbegin() + 10, regs_.rend());
}

size_t Memory::n_regs() const
{
    return regs_.size();
}

void mem_print(const Memory& memory)
{
	for (auto i = 0; i < memory.n_regs(); i++)
		std::cout << memory[i] << " "; 
	std::cout << '\n';	
}

} // namespace ussr
