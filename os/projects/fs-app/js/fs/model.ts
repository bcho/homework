/// <reference path="../_ref.d.ts" />

class FileEntryModel extends Backbone.Model implements SerializableInterface {

    static TypeEmpty = 0;
    static TypeFile = 1;
    static TypeDir = 2;

    defaults() {
        return {
            // File content & disk location.
            startsAt: 0,
            content: '',

            // Ownership and permission.
            oid: 0,
            ownerPerm: 0,
            otherPerm: 0,

            // Type & stat.
            name: '',
            entryType: FileEntryModel.TypeEmpty,
            ctime: new Date,
            mtime: new Date,

            // Parent & Sub entries.
            parentEntry: null,
            subEntries: []
        }
    }

    read(): string { return this.get('content'); }
    write(buffer: string): number {
        this.set({
            'content': buffer,
            'mtime': new Date
        });

        FilesTree.getInstance().flush();

        return buffer.length;
    }

    static create(parent: FileEntryModel, name: string, entryType: number,
                  owner: UserModel,
                  ownerPerm: number, otherPerm: number): FileEntryModel
    {
        var file = new FileEntryModel({
            name: name,
            entryType: entryType,
            oid: owner.getUid(),
            ownerPerm: ownerPerm,
            otherPerm: otherPerm,
            ctime: new Date()
        });

        if (parent) {
            if (parent.getSubEntryByName(name) != null) {
                duplicatedFilesException(name);
            }

            parent.addSubEntry(file);
        }

        FilesTree.getInstance().flush();
        return file;
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

    getPath(): string {
        var path = [this.get('name')],
            cur = this,
            parentEntry: FileEntryModel;

        while ((parentEntry = cur.get('parentEntry')) !== null) {
            cur = parentEntry;
            path.push(cur.get('name'));
        }

        return path.reverse().join('/');
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

    getParentEntry(): FileEntryModel { return this.get('parentEntry'); }

    unlink(subEntry: FileEntryModel): FileEntryModel {
        var entries = _(this.getSubEntries()).filter((e: FileEntryModel) => {
            return e !== subEntry;
        });

        this.set('subEntries', entries);
        FilesTree.getInstance().flush();

        return this;
    }

    toJSON(options?: any): any {
        var encoded = super.toJSON(options);

        encoded['path'] = this.getPath();

        return encoded;
    }

    storeAsObject(): any {
        if (this.isFile()) {
            return {
                content: this.get('content'),
                oid: this.get('oid'),
                ownerPerm: this.get('ownerPerm'),
                otherPerm: this.get('otherPerm'),
                entryType: this.get('entryType'),
                ctime: this.get('ctime'),
                mtime: this.get('mtime')
            };
        } else if (this.isDir()) {
            var subEntries = _.map(this.getSubEntries(), (e: FileEntryModel) => {
                return {
                    name: e.get('name'),
                    startsAt: e.get('startsAt')
                };
            });

            return {
                oid: this.get('oid'),
                ownerPerm: this.get('ownerPerm'),
                otherPerm: this.get('otherPerm'),
                entryType: this.get('entryType'),
                subEntries: subEntries
            };
        }
    }

    store(): string {
        return JSON.stringify(this.storeAsObject()).trim();
    }

    // not implemented.
    restore(buffer: string): FileEntryModel {
        return null;
    }

}

class FilesTree extends Backbone.Events implements SerializableInterface {

    private static instance: FilesTree = null;

    protected rootEntry: FileEntryModel;
    protected currentDir: FileEntryModel;
    
    static getInstance(): FilesTree {
        if (! FilesTree.instance) {
            FilesTree.instance = new FilesTree();
        }

        return FilesTree.instance;
    }

    constructor() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);
    }

    // Change current working directory.
    chdir(path: string): FilesTree {
        var found = this.findByAbsolutePath(path);
        if (! found) {
            pathNotFoundException(path);
        }

        return this.chdirByEntry(found);
    }

    chdirByEntry(entry: FileEntryModel): FilesTree {
        this.currentDir = entry;
        this.trigger('cwd:changed');

        return this;
    }

    // Set root entry.
    setRoot(root: FileEntryModel): FilesTree {
        this.rootEntry = root;
        this.trigger('root:changed');

        this.store();

        return this;
    }

    // Get root entry.
    getRoot(): FileEntryModel { return this.rootEntry; }

    // Get current dir.
    getCurrentDir(): FileEntryModel { return this.currentDir; }

    // Find a entry from absolute path.
    findByAbsolutePath(path: string): FileEntryModel {
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

    // Flush disk.
    flush(): void {
        // XXX
        if (this.rootEntry) {
            this.store();

            this.trigger('fs:flushed');
        }
    }

    // Dump into files block.
    store(): string {
        return Disk.getInstance().store();
    }

    // Restore from files block.
    restore(fileBlock: string): FilesTree {
        return this;
    }
}


class Disk extends Backbone.Events implements SerializableInterface {

    private static instance: Disk = null;
    private static UsableBlocks = 256;
    private static BlockWidth = 64;

    protected users: UserManager;
    protected files: FilesTree;
    protected used: boolean[];
    protected blocks: string[];

    static getInstance(): Disk {
        if (!Disk.instance) {
            Disk.instance = new Disk();
        }

        return Disk.instance;
    }

    constructor() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);

        this.users = UserManager.getInstance();
        this.files = FilesTree.getInstance();

        this.reset();
    }

    getBlocksMap(): boolean[] { return this.used.slice(); }

    // Dump disk.
    store(): string {
        this.reset();
        this.storeFileEntries();

        this.trigger('disk:changed');

        return this.blocks.join('');
    }

    // Restore disk.
    restore(disk: string): Disk {
        // TODO
        return this;
    }

    protected allocate(size: number): number {
        var taken = 0;

        for (var i = 0; i < Disk.UsableBlocks; i++) {
            if (this.used[i]) {
                continue;
            }

            for (var j = i, taken = size; taken > 0 && ! this.used[j];) {
                j = j + 1;
                taken -= Disk.BlockWidth;
            }

            // Allocated.
            if (taken <= 0) {
                for (; j >= i; j--) {
                    this.used[j] = true;
                }

                return i * Disk.BlockWidth;
            }
        }

        return -1;
    }

    protected reset(): void {
        this.used = [];
        this.blocks = [];

        for (var i = 0; i < Disk.UsableBlocks; i++) {
            this.used.push(false);
            for (var j = 0; j < Disk.BlockWidth; j++) {
                this.blocks.push(' ');
            }
        }
    }

    protected storeFileEntries(): void {
        var root = this.files.getRoot();

        var dump = (node: FileEntryModel) => {
            if (node.isDir()) {
                var subEntryPos = [];

                _.each(node.getSubEntries(), (e: FileEntryModel) => {
                    subEntryPos.push(dump(e));
                });
            }

            var dumped = node.store();
            var startsAt = this.allocate(dumped.length);

            node.set('startsAt', startsAt);

            for (var i = 0; i < dumped.length; i++) {
                this.blocks[startsAt + i] = dumped[i];
            }

            return startsAt;
        }

        dump(this.files.getRoot());
    }
}
