/*Make start sysmbol as the starting point*/

ENTRY(start)

/* Define various sections of the executable */

SECTIONS
{
  .text 0x100000 : /* By convention we begin by putting the first kernel section at 1 MiB*/
  {
    code = .; 
    *(.multiboot) /* Multiboot header is required to be kept at beginning to be recognised by bootlaoder */
    *(.text)
    . = ALIGN(4096);
  }

  .data :
  {
     data = .; 
     *(.data)
     *(.rodata)        /* Read only data */
     . = ALIGN(4096);
  }

  .bss :
  {
    bss = .; 
    *(.bss)
    . = ALIGN(4096);
  }

  end = .; 
}


