#include <iostream>
#include <algorithm>

#include "memory.hpp"

namespace ussr
{

//----------------------------work mode----------------------------//

typename Memory::arifmetic_type Memory::operator[](std::size_t i) const
{
    return regs_[i];
}

void Memory::negate_x ()
{
	 x_reg_ = -x_reg_;
}

void Memory::reset_x () 
{ 
	x_reg_ = 0; 
}

void Memory::set_y_from_x ()
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

std::size_t Memory::n_work_regs () const
{
    return regs_.size();
}

//--------------------------programming mode-------------------------//

std::size_t Memory::get_cmd (std::size_t ptr) const
{
	if (!ptr_check(ptr))
		return 0;
    return cmd_stack_regs_[(ptr)];
}

void Memory::set_cmd (std::size_t cmd)
{
	if (!ptr_check(step_ptr_))
		return;
	cmd_stack_regs_[step_ptr_] = cmd;
}

std::size_t Memory::set_step_ptr (std::size_t ptr)
{
	if (ptr_check(ptr))
	{
		step_ptr_ = ptr;
		return 1;
	}
	else
		return 0;
}

void Memory::reset_step_ptr ()
{
	step_ptr_ = 0;
}

std::size_t Memory::get_step_ptr () const
{
    return step_ptr_;
}

void Memory::inc_step_ptr()
{
	step_ptr_++;
}

void Memory::dec_step_ptr()
{
	step_ptr_--;
}

std::size_t Memory::n_prog_regs() const
{
    return cmd_stack_regs_.size();
}

std::size_t ptr_check(std::size_t ptr)
{
    if ((ptr >= 0) && (ptr < 60))
		return 1;
	else
		return 0;
}

void mem_print (const Memory& memory)
{
	std::cout << "common regs_:\n";
	for (auto i = 0; i < memory.n_work_regs(); i++)
		std::cout << memory[i] << " "; 
	std::cout << '\n';	
	
	std::cout << "cmd_stack_regs_:\n";
	for (auto i = 0; i < memory.n_prog_regs(); i++)
	{
		std::cout << memory.get_cmd(i) << " ";
		if (!((i+1)%6))
			std::cout<<'\n'; 
	}
}

}// namespace ussr