/// <reference path="../_ref.d.ts" />

// TODO record mode (read or write).
var OPENED_FILES: FileEntryModel[] = [
    null,
    null,   // stdin
    null,   // stdout
    null,   // stderr
],
    OPENED_FILES_STARTS_AT = 4;  // XXX oops

// Change working dir.
var sys_chdir = (entry: FileEntryModel): number =>  {
    FilesTree.getInstance().chdirByEntry(entry);

    return 0;
}

// Open a file and return file descriptor.
//
// TODO record mode.
var sys_open = (entry: FileEntryModel, mode?: number): number => {
    // TODO check permission

    for (var i = OPENED_FILES_STARTS_AT; i < OPENED_FILES.length; i++) {
        if (OPENED_FILES[i] === null) {
            OPENED_FILES[i] = entry;
            return i;
        }
    }

    OPENED_FILES.push(entry);
    return OPENED_FILES.length - 1;
}

// Close a file descriptior.
var sys_close = (fd: number): number => {
    OPENED_FILES[fd] = null;

    return 0;
}

// Read from file descriptor.
var sys_read = (fd: number): string => {
    if (! OPENED_FILES[fd]) {
        ioFailedException('cannot read from: ' + fd);
    }

    return OPENED_FILES[fd].read();
}

// Write to file descriptor.
var sys_write = (fd: number, content: string): number => {
    if (! OPENED_FILES[fd]) {
        ioFailedException('cannot write to: ' + fd);
    }

    return OPENED_FILES[fd].write(content);
}

// Create an entry.
var sys_create = (parent: FileEntryModel,
                  name: string,
                  entryType: number,
                  owner: UserModel,
                  ownerPerm: number,
                  otherPerm: number
                 ): FileEntryModel =>
{
    return FileEntryModel.create(parent, name, entryType, owner, ownerPerm, otherPerm);
}

// Delete an entry.
var sys_delete = (entry: FileEntryModel): number => {
    var parentEntry = entry.getParentEntry();

    if (parentEntry) {
        parentEntry.unlink(entry);
    } else {
        ioFailedException('cannot unlinked root');   // XXX
    }

    return 0;
}
