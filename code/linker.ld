OUTPUT_ARCH( "riscv" )
ENTRY(_start)

SECTIONS
{
  . = 0x80000000;
  __global_pointer$ = 0x80040000;

  PROVIDE (__TEXT_START = .);
  .text : ALIGN(256) { 
      *(.text.init) 
      *(.text) *(.text.*) *(.device_code) . = ALIGN(256); . = 0x10000; }
  PROVIDE (__TEXT_END = .);

  .tohost : { *(.tohost); . = 0x1000; }
  .rodata : ALIGN(256) { *(.rodata) *(.rodata.*) }
  .sdata  : ALIGN(256) {
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }

  /* bss segment */
  .sbss : {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  }
  .bss : { *(.bss) }
  
  /* 
    * thread-local data segment. 
    * Copied to TCM<n> at start by init_tls().
    */
  .tdata : ALIGN(256) {
    _tdata_begin = .;
    *(.tls_start) *(.tdata) *(.tdata.*) 
    _tdata_end = .;
  }
  .tbss :
  {
    *(.tbss) *(.tbss.*)
    _tbss_end = .;
  }
  
  /* data sections, mostly for host to deal with input and output data */
  . = 0x80200000;
  PROVIDE (__DATA_START = .);
  .data : {LONG(0xabcdabcd) *(.data) }
}