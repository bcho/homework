/// <reference path="../_ref.d.ts" />

class FileEntryModel extends Backbone.Model {

    static TypeEmpty = 0;
    static TypeFile = 1;
    static TypeDir = 2;

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
            name: '',
            entryType: FileEntryModel.TypeEmpty,
            ctime: 0,
            mtime: 0,

            // Parent & Sub entries.
            parentEntry: null,
            subEntries: []
        }
    }

    getType(): number { return this.get('entryType'); }
    isDir(): boolean { return this.getType() === FileEntryModel.TypeDir; }
    isFile(): boolean { return this.getType() === FileEntryModel.TypeFile; }

    getSubEntryByName(name: string): FileEntryModel {
        return _.find(this.get('subEntries'), (e: FileEntryModel) => {
            return e.get('name') === name;
        });
    }

    getEntriesTo(): FileEntryModel[] {
        var path = [this],
            cur = this,
            parentEntry: FileEntryModel;

        while ((parentEntry = cur.get('parentEntry')) !== null) {
            cur = parentEntry;
            path.push(cur);
        }

        return path.reverse();
    }

    getPath(): string[] {
        var path = [this.get('name')],
            cur = this,
            parentEntry: FileEntryModel;

        while ((parentEntry = cur.get('parentEntry')) !== null) {
            cur = parentEntry;
            path.push(cur.get('name'));
        }

        return path.reverse();
    }

    getSubEntries(): FileEntryModel[] { return this.get('subEntries'); }

    addSubEntry(sub: FileEntryModel): FileEntryModel {
        if (! this.isDir()) {
            invalidEntryTypeException();
        }

        var subEntries = this.getSubEntries();
        // TODO Check circular reference.
        subEntries.push(sub);
        this.set('subEntries', subEntries);
        sub.setParentEntry(this);

        return this;
    }

    setParentEntry(p: FileEntryModel): FileEntryModel {
        this.set('parentEntry', p);

        return this;
    }
}

class FilesTree implements SerializableInterface {
    private static instance: FilesTree = null;

    protected rootEntry: FileEntryModel;
    protected currentDir: FileEntryModel;
    
    static getInstance(): FilesTree {
        if (! FilesTree.instance) {
            FilesTree.instance = new FilesTree();
        }

        return FilesTree.instance;
    }

    // Change current working directory.
    chdir(path: string): FilesTree {
        var found = this.findByAbsolutePath(path);
        if (! found) {
            pathNotFoundException(path);
        }

        this.currentDir = found;

        return this;    
    }

    // Set root entry.
    setRoot(root: FileEntryModel): FilesTree {
        this.rootEntry = root;

        return this;
    }

    // Get root entry.
    getRoot(): FileEntryModel { return this.rootEntry; }

    // Get current dir.
    getCurrentDir(): FileEntryModel { return this.currentDir; }

    // Find a entry from absolute path.
    protected findByAbsolutePath(path: string): FileEntryModel {
        var finder = (subs: string[], cur: FileEntryModel) => {
            if (subs.length === 0 || cur === null || ! cur.isDir()) {
                return cur;
            }

            var subDir = subs[0],
                remains = subs.slice(1);

            return finder(remains, cur.getSubEntryByName(subDir));
        };

        return finder(path.split('/').slice(1), this.rootEntry);
    }

    // Dump into files block.
    store(): string {
        return '';
    }

    // Restore from files block.
    restore(fileBlock: string): FilesTree {
        return this;
    }
}


class Disk implements SerializableInterface {

    private static instance: Disk = null;

    protected users: UserCollection;
    protected files: FilesTree;

    static getInstance(): Disk {
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
