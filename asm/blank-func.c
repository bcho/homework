void should_exit()
{
    asm("mov eax, 1");
    asm("mov ebx, 0");
    asm("int 128");
    // Program exit here.
}

int main()
{
    should_exit();

    // Never reach here.
    return 0;
}
