in main.o:
```
0000000000000000 <main>:
   0:   f3 0f 1e fa             endbr64 
   4:   55                      push   %rbp
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 83 ec 10             sub    $0x10,%rsp
   c:   b8 00 00 00 00          mov    $0x0,%eax
  11:   e8 00 00 00 00          call   16 <main+0x16>
  16:   48 89 45 f8             mov    %rax,-0x8(%rbp)
  1a:   48 83 7d f8 00          cmpq   $0x0,-0x8(%rbp)
  1f:   75 07                   jne    28 <main+0x28>
  21:   b8 ff ff ff ff          mov    $0xffffffff,%eax
  26:   eb 11                   jmp    39 <main+0x39>
  28:   48 8b 45 f8             mov    -0x8(%rbp),%rax
  2c:   48 89 c7                mov    %rax,%rdi
  2f:   e8 00 00 00 00          call   34 <main+0x34>
  34:   b8 00 00 00 00          mov    $0x0,%eax
  39:   c9                      leave  
  3a:   c3                      ret 
```

in a.out:
```
0000000000001189 <main>:
    1189:       f3 0f 1e fa             endbr64 
    118d:       55                      push   %rbp
    118e:       48 89 e5                mov    %rsp,%rbp
    1191:       48 83 ec 10             sub    $0x10,%rsp
    1195:       b8 00 00 00 00          mov    $0x0,%eax
    119a:       e8 25 00 00 00          call   11c4 <constructor>
    119f:       48 89 45 f8             mov    %rax,-0x8(%rbp)
    11a3:       48 83 7d f8 00          cmpq   $0x0,-0x8(%rbp)
    11a8:       75 07                   jne    11b1 <main+0x28>
    11aa:       b8 ff ff ff ff          mov    $0xffffffff,%eax
    11af:       eb 11                   jmp    11c2 <main+0x39>
    11b1:       48 8b 45 f8             mov    -0x8(%rbp),%rax
    11b5:       48 89 c7                mov    %rax,%rdi
    11b8:       e8 3f 00 00 00          call   11fc <print>
    11bd:       b8 00 00 00 00          mov    $0x0,%eax
    11c2:       c9                      leave  
    11c3:       c3                      ret  
```
