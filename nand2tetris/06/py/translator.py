#coding: utf-8

import re

from assembler import SymbolTable, Parser, Code


# command format
A_COMM_TMPL = '0{0:015b}'
C_COMM_TMPL = '111{0:07b}{1:03b}{2:03b}'

# init predefined symbol
PRE_DEFINED = SymbolTable([
    ('SP', 0x0000), ('LCL', 0x0001), ('ARG', 0x0002), ('KBD', 0x6000),
    ('THIS', 0x0003), ('THAT', 0x0004), ('SCREEN', 0x4000),
    ('R0', 0x0000), ('R1', 0x0001), ('R2', 0x0002), ('R3', 0x0003),
    ('R4', 0x0004), ('R5', 0x0005), ('R6', 0x0006), ('R7', 0x0007),
    ('R8', 0x0008), ('R9', 0x0009), ('R10', 0x000A), ('R11', 0x000B),
    ('R12', 0x000C), ('R13', 0x000D), ('R14', 0x000E), ('R15', 0x000F)
])


def init(stream):
    return Parser(stream)


def first_pass(parser):
    '''First pass: parse rom address and symbols'''
    rom_addr = -1
    last_symbols = []
    symbols = PRE_DEFINED.copy()

    parser.reset()
    while parser.hasMoreCommands:
        parser.advance()
        command_type = parser.commandType
        if command_type == 'A_COMMAND' or command_type == 'C_COMMAND':
            rom_addr = rom_addr + 1
            while last_symbols:
                symbols.addEntry(last_symbols.pop(), rom_addr)
        elif command_type == 'L_COMMAND':
            last_symbols.append(parser.symbol)

    return parser, symbols


def second_pass(parser, symbols):
    is_variable = re.compile(u'^[^\d]')
    variable_address = 15
    coder = Code()
    translated = []

    parser.reset()
    while parser.hasMoreCommands:
        parser.advance()
        command_type = parser.commandType

        if command_type == 'A_COMMAND':
            address = parser.symbol
            if is_variable.match(address):
                if symbols.contains(address):
                    address = symbols.GetAddress(address)
                else:
                    variable_address = variable_address + 1
                    symbols.addEntry(address, variable_address)
                    address = variable_address
            else:
                address = int(address)
            translated.append(A_COMM_TMPL.format(address)[0:16])

        if command_type == 'C_COMMAND':
            comp = coder.comp(parser.comp)
            dest = coder.dest(parser.dest)
            jump = coder.jump(parser.jump)
            translated.append(C_COMM_TMPL.format(comp, dest, jump)[0:16])

    return '\n'.join(translated)


def main(stream):
    parser = init(stream)
    return second_pass(*first_pass(parser))


if __name__ == '__main__':
    import sys
    fname = sys.argv[1]
    with open(fname) as f:
        print main(f)
