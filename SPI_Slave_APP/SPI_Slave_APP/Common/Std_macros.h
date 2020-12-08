/*
 * Std_macros.h
 *
 * Created: 11/7/2020 10:51:01 AM
 *  Author: ENG Mostafa
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define REG_SIZE 8
#define SET_BIT(reg,bit)			(reg|=(1<<bit))
#define SET_REG(reg)                (reg=0xff)
#define CLR_BIT(reg,bit)			(reg&=~(1<<bit))
#define CLR_REG(reg)                (reg=0x00)      
#define READ_BIT(reg,pin_num)		((reg&(1<<pin_num))>>pin_num)
#define TOG_BIT(reg,pin_num)		(reg ^=(1<<pin_num))
// Rotate
#define ROR(reg,num)				((reg>>num)|(reg<<(REG_SIZE-num)))
#define ROL(reg,num)				((reg<<num)|(reg>>(REG_SIZE-num)))

#endif /* STD_MACROS_H_ */