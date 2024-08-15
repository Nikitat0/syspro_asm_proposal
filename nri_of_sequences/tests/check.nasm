default rel

extern yield

section .text
global aligmentCheck
aligmentCheck:
  push qword 0
  test rsp, 0xf
  setz byte [rsp]
  mov rdi, rsp
  call yield
  add rsp, 8
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
