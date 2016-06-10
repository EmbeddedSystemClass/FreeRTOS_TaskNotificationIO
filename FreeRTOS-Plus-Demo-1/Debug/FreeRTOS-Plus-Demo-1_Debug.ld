/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-13
 * (c) NXP Semiconductors 2013-2016
 * Generated linker script file for LPC1769
 * Created from link_template.ld (7.8.0 ())
 * By LPCXpresso v7.8.0 [Build 426] [2015-05-28]  on Mon Jun 06 14:53:33 IST 2016
 */


INCLUDE "FreeRTOS-Plus-Demo-1_Debug_lib.ld"
INCLUDE "FreeRTOS-Plus-Demo-1_Debug_mem.ld"

_Privileged_Functions_Region_Size = 16K; 
_Privileged_Data_Region_Size = 256; 
 
__FLASH_segment_start__ = ORIGIN( MFlash512 ); 
__FLASH_segment_end__ = __FLASH_segment_start__ + LENGTH( MFlash512 ); 
 
__privileged_functions_start__ = ORIGIN( MFlash512 ); 
__privileged_functions_end__ = __privileged_functions_start__ + _Privileged_Functions_Region_Size; 
 
__SRAM_segment_start__ = ORIGIN( RamLoc32 ); 
__SRAM_segment_end__ = __SRAM_segment_start__ + LENGTH( RamLoc32 ); 
 
__privileged_data_start__ = ORIGIN( RamLoc32 ); 
__privileged_data_end__ = ORIGIN( RamLoc32 ) + _Privileged_Data_Region_Size;	 



ENTRY(ResetISR)

SECTIONS
{
    
    .text : ALIGN(4)
    {
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))

        
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */
        
        
        *(privileged_functions)
        
    } >MFlash512
    
    
    .text : ALIGN(4)    
    {
         . = ORIGIN(MFlash512) + _Privileged_Functions_Region_Size;
         *(.text*)
        
        
    } > MFlash512

    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this. 
     */
    .ARM.extab : ALIGN(4)
    {
    	*(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlash512
    __exidx_start = .;
    
    .ARM.exidx : ALIGN(4)
    {
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlash512
    __exidx_end = .;
    
    _etext = .;

	/* zero initialized data */		
	privileged_data :
	{
		_bss = .;
		*(privileged_data)
		/* Non kernel data is kept out of the first 256 bytes of SRAM. */
	} > RamLoc32	

    . = ORIGIN( RamLoc32 ) + _Privileged_Data_Region_Size;
    
    	.bss :
	{
	__privileged_data_end__ = ABSOLUTE(.) ;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > RamLoc32

     
		.data : AT (__exidx_end)
	{
		_data = .;	
		*(vtable)
		*(.data*)
		_edata = .;
	} > RamLoc32

PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc32 - 16);        
    
    /* DATA section for RamAHB32 */
    .data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM2 = .) ;
       *(.ramfunc.$RAM2)
       *(.ramfunc.$RamAHB32)
    	*(.data.$RAM2*)
    	*(.data.$RamAHB32*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM2 = .) ;
    } > RamAHB32 AT>MFlash512
	
	/* BSS section for RamAHB32 */
	.bss_RAM2 : ALIGN(4)
	{
	   PROVIDE(__start_bss_RAM2 = .) ;
		*(.bss.$RAM2*)
		*(.bss.$RamAHB32*)
	   . = ALIGN(4) ;
	   PROVIDE(__end_bss_RAM2 = .) ;
	} > RamAHB32



       
}
