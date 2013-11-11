#coding: utf-8

import re
from cStringIO import StringIO


class SymbolTable(dict):

    def addEntry(self, symbol, address):
        if not isinstance(address, int):
            raise KeyError
        self[symbol] = address

    def contains(self, symbol):
        return symbol in self

    def GetAddress(self, symbol):
        return self[symbol]

    def copy(self):
        return SymbolTable(self.items())


class Code(object):
    _dest_symbols = SymbolTable([
        ('null', 0b000), ('M', 0b001), ('D', 0b010), ('MD', 0b011),
        ('A', 0b100), ('AM', 0b101), ('AD', 0b110), ('AMD', 0b111)
    ])

    _comp_symbols = SymbolTable([
        ('0', 0b0101010), ('1', 0b0111111), ('-1', 0b0111010),
        ('D', 0b0001100), ('A', 0b0110000), ('!D', 0b0001101),
        ('!A', 0b0110001), ('-D', 0b0001111), ('-A', 0b0110011),
        ('D+1', 0b0011111), ('A+1', 0b0110111), ('D-1', 0b0001110),
        ('A-1', 0b0110010), ('D+A', 0b0000010), ('D-A', 0b0010011),
        ('A-D', 0b0000111), ('D&A', 0b0000000), ('D|A', 0b0010101),
        ('M', 0b1110000), ('!M', 0b1110001), ('-M', 0b1110011),
        ('M+1', 0b1110111), ('M-1', 0b1110010), ('D+M', 0b1000010),
        ('D-M', 0b1010011), ('M-D', 0b1000111), ('D&M', 0b1000000),
        ('D|M', 0b1010101)
    ])

    _jump_symbols = SymbolTable([
        ('null', 0b000), ('JGT', 0b001), ('JEQ', 0b010), ('JGE', 0b011),
        ('JLT', 0b100), ('JNE', 0b101), ('JLE', 0b110), ('JMP', 0b111)
    ])

    def dest(self, raw):
        return Code._dest_symbols.GetAddress(raw)

    def comp(self, raw):
        raw = raw.replace(' ', '')  # remove whitespaces
        return Code._comp_symbols.GetAddress(raw)

    def jump(self, raw):
        return Code._jump_symbols.GetAddress(raw)


class Command(object):

    A_COMM_P = re.compile(u'^\\@([a-zA-Z0-9_\\.\\$]+)$')
    C_COMM_P = re.compile(
        u'^([a-zA-Z0-9_]+[\ ]*\\=[\ ]*)?'
        u'([a-zA-Z0-9\\+\\-\\|\\!\\&_]+)'
        u'([\ ]*\\;[\ ]*(JGT|JEQ|JGE|JLT|JNE|JLE|JMP))?$'
    )
    L_COMM_P = re.compile(u'^\\(([a-zA-Z_]{1}[a-zA-Z0-9_\\.\\$]*)\\)$')

    def __init__(self, raw):
        self.value, self.type = None, None

        # simple cases
        for pattern, type in [(Command.A_COMM_P, 'A_COMMAND'),
                              (Command.L_COMM_P, 'L_COMMAND'),
                              (Command.C_COMM_P, 'C_COMMAND')]:
            matched = pattern.findall(raw)
            if matched:
                self.value, self.type = matched[0], type
                break

        # C_COMMAND
        if self.type == 'C_COMMAND':
            _dest, comp, _jmp = self.value[0:3]
            self.value = None
            dest, jmp = _dest.strip('= '), _jmp.strip('; ')
            if comp:
                self.value = (dest or 'null', comp, jmp or 'null')

        if not self.value or not self.type:
            raise ValueError('command: %s cannot be parsed!' % raw)

    def __str__(self):
        return 'Command<%s>: (%r)' % (self.type, self.value)


class Parser(object):

    STRIP_COMMENT_P = re.compile(u'^([^\\/\\/]*)(\\/\\/)?([^\\/\\/]*)$')

    def __init__(self, stream):
        if isinstance(stream, str) or isinstance(stream, unicode):
            stream = StringIO(stream)

        cleaned_lines = [Parser.cleanLine(line) for line in stream.readlines()]
        self.stream = filter(None, cleaned_lines)
        self.content = '\n'.join(self.stream)
        self.current_command_idx = -1
        self.currentCommand = None

    @staticmethod
    def cleanLine(raw):
        for matched in Parser.STRIP_COMMENT_P.findall(raw):
            if matched[0]:
                return matched[0].strip()

    @property
    def hasMoreCommands(self):
        total_size = len(self.stream)
        return total_size > 0 and self.current_command_idx + 1 < total_size

    def advance(self):
        if not self.hasMoreCommands:
            raise EOFError
        self.current_command_idx = self.current_command_idx + 1
        self.currentCommand = Command(self.stream[self.current_command_idx])

    @property
    def commandType(self):
        return self.currentCommand.type

    @property
    def symbol(self):
        if self.commandType != 'A_COMMAND' and self.commandType != 'L_COMMAND':
            raise RuntimeError('current command type is not A_COMMAND '
                               'or L_COMMAND')
        return self.currentCommand.value

    @property
    def dest(self):
        if self.commandType != 'C_COMMAND':
            raise RuntimeError('current command type is not C_COMMAND')
        return self.currentCommand.value[0]

    @property
    def comp(self):
        if self.commandType != 'C_COMMAND':
            raise RuntimeError('current command type is not C_COMMAND')
        return self.currentCommand.value[1]

    @property
    def jump(self):
        if self.commandType != 'C_COMMAND':
            raise RuntimeError('current command type is not C_COMMAND')
        return self.currentCommand.value[2]

    def reset(self):
        self.current_command_idx, self.currentCommand = -1, None
