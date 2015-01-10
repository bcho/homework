/// <reference path="./_ref.d.ts" />

var pathNotFoundException = (path: string) => {
    throw new Error('Path: ' + path + ' not found.');
}

var invalidEntryTypeException = () => {
    throw new Error('Invalid entry type.');
}
