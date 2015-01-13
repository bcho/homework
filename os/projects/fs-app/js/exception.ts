/// <reference path="./_ref.d.ts" />

var pathNotFoundException = (path: string) => {
    throw new Error('Path: ' + path + ' not found.');
}

var invalidEntryTypeException = () => {
    throw new Error('Invalid entry type.');
}

var ioFailedException = (msg?: string) => {
    msg = msg || 'IO failed';

    throw new Error(msg);
}

var duplicatedFilesException = (name: string) => {
    throw new Error('Duplicated files: ' + name);
}
