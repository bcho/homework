/// <reference path="../_ref.d.ts" />

var sys_chdir = (entry: FileEntryModel): number =>  {
    FilesTree.getInstance().chdirByEntry(entry);

    return 0;
}
