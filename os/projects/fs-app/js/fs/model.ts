/// <reference path="../_ref.d.ts" />

class FileEntryModel extends Backbone.Model {

    defaults() {
        return {
            // Position in disk.
            startsAt: 0,
            endsAt: 0,

            // Ownership and permission.
            oid: 0,
            ownerPerm: 0,
            otherPerm: 0,

            // Type & stat.
            entryType: 0,
            ctime: 0,
            mtime: 0,

            // Sub entries.
            sub: []
        }
    }
}

class FS extends Backbone.Collection<FileEntryModel> implements
    SingletonInterface,
    SerializableInterface
{
    private static instance: FS = null;
    
    getInstance(): SingletonInterface {
        if (! FS.instance) {
            FS.instance = new FS();
        }

        return FS.instance;
    }

    // Dump into files block.
    store(): string {
        return '';
    }

    // Restore from files block.
    restore(fileBlock: string): FS {
        return this;
    }
}


class Disk implements SingletonInterface, SerializableInterface {

    private static instance: Disk = null;

    protected users: UserCollection;
    protected files: FS;

    getInstance(): SingletonInterface {
        if (Disk.instance) {
            Disk.instance = new Disk();
        }

        return Disk.instance;
    }

    // Dump disk.
    store(): string {
        return '';
    }

    // Restore disk.
    restore(disk: string): Disk {
        return this;
    }
}
