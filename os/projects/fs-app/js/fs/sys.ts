/// <reference path="../_ref.d.ts" />

// Change working dir.
var sys_chdir = (entry: FileEntryModel): number =>  {
    FilesTree.getInstance().chdirByEntry(entry);

    return 0;
}

// Open a file and return file descriptor.
var sys_open = (entry: FileEntryModel, mode: number): number => {
    return 0;
}

// Close a file descriptior.
var sys_close = (fd: number): number => {
    return 0;
}

// Read from file descriptor.
var sys_read = (fd: number): string => {
    return '';
}

// Write to file descriptor.
var sys_write = (fd: number, content: string): number => {
    return 0;
}

// Create an entry.
var sys_create = (parent: FileEntryModel, name: string,
                  ownerPerm: number, otherPerm: number): number =>
{
    return 0;
}

// Delete an entry.
var sys_delete = (entry: FileEntryModel): number => {
    return 0;
}
