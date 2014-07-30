int main()
{
    // Use -masm=intel to compile.
    asm("mov eax, 1");
    asm("mov ebx, 0");
    asm("int 128");
}
