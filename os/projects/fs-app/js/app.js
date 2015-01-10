/// <reference path="./_ref.d.ts" />
/// <reference path="./_ref.d.ts" />
var pathNotFoundException = function (path) {
    throw new Error('Path: ' + path + ' not found.');
};
var invalidEntryTypeException = function () {
    throw new Error('Invalid entry type.');
};
var html;
(function (html) {
    html.filesTreeDir = ["<li>", "    <i class=\"fa fa-folder-o\"></i>", "    <a><%= name %></a>", "</li>", ""].join("\n");
    html.filesTreeFile = ["<li>", "    <i class=\"fa fa-file-word-o\"></i>", "    <%= name %>", "</li>", ""].join("\n");
    html.filesTreeSubtree = ["<li>", "    <i class=\"fa fa-folder-open-o\"></i>", "    <a><%= name %></a>", "</li>", "<li class=\"files-tree-sub\">", "    <ul class=\"files-tree\">", "        <%= sub_tree %>", "    </ul>", "</li>", ""].join("\n");
})(html || (html = {}));
/// <reference path="../_ref.d.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var FileEntryModel = (function (_super) {
    __extends(FileEntryModel, _super);
    function FileEntryModel() {
        _super.apply(this, arguments);
    }
    FileEntryModel.prototype.defaults = function () {
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
        };
    };
    FileEntryModel.prototype.getType = function () {
        return this.get('entryType');
    };
    FileEntryModel.prototype.isDir = function () {
        return this.getType() === FileEntryModel.TypeDir;
    };
    FileEntryModel.prototype.isFile = function () {
        return this.getType() === FileEntryModel.TypeFile;
    };
    FileEntryModel.prototype.getSubEntryByName = function (name) {
        return _.find(this.get('subEntries'), function (e) {
            return e.get('name') === name;
        });
    };
    FileEntryModel.prototype.getEntriesTo = function () {
        var path = [this], cur = this, parentEntry;
        while ((parentEntry = cur.get('parentEntry')) !== null) {
            cur = parentEntry;
            path.push(cur);
        }
        return path;
    };
    FileEntryModel.prototype.getSubEntries = function () {
        return this.get('subEntries');
    };
    FileEntryModel.prototype.addSubEntry = function (sub) {
        console.log(this);
        if (!this.isDir()) {
            invalidEntryTypeException();
        }
        var subEntries = this.getSubEntries();
        // TODO Check circular reference.
        subEntries.push(sub);
        this.set('subEntries', subEntries);
        sub.setParentEntry(this);
        return this;
    };
    FileEntryModel.prototype.setParentEntry = function (p) {
        this.set('parentEntry', p);
        return this;
    };
    FileEntryModel.TypeEmpty = 0;
    FileEntryModel.TypeFile = 1;
    FileEntryModel.TypeDir = 2;
    return FileEntryModel;
})(Backbone.Model);
var FilesTree = (function () {
    function FilesTree() {
    }
    FilesTree.getInstance = function () {
        if (!FilesTree.instance) {
            FilesTree.instance = new FilesTree();
        }
        return FilesTree.instance;
    };
    // Change current working directory.
    FilesTree.prototype.chdir = function (path) {
        var found = this.findByAbsolutePath(path);
        if (!found) {
            pathNotFoundException(path);
        }
        this.currentDir = found;
        return this;
    };
    // Set root entry.
    FilesTree.prototype.setRoot = function (root) {
        this.rootEntry = root;
        return this;
    };
    // Get root entry.
    FilesTree.prototype.getRoot = function () {
        return this.rootEntry;
    };
    // Get current dir.
    FilesTree.prototype.getCurrentDir = function () {
        return this.currentDir;
    };
    // Find a entry from absolute path.
    FilesTree.prototype.findByAbsolutePath = function (path) {
        var finder = function (subs, cur) {
            if (subs.length === 0 || cur === null || !cur.isDir()) {
                return cur;
            }
            var subDir = subs[0], remains = subs.slice(1);
            return finder(remains, cur.getSubEntryByName(subDir));
        };
        return finder(path.split('/').slice(1), this.rootEntry);
    };
    // Dump into files block.
    FilesTree.prototype.store = function () {
        return '';
    };
    // Restore from files block.
    FilesTree.prototype.restore = function (fileBlock) {
        return this;
    };
    FilesTree.instance = null;
    return FilesTree;
})();
var Disk = (function () {
    function Disk() {
    }
    Disk.getInstance = function () {
        if (Disk.instance) {
            Disk.instance = new Disk();
        }
        return Disk.instance;
    };
    // Dump disk.
    Disk.prototype.store = function () {
        return '';
    };
    // Restore disk.
    Disk.prototype.restore = function (disk) {
        return this;
    };
    Disk.instance = null;
    return Disk;
})();
/// <reference path="../_ref.d.ts" />
var FilesTreeView = (function (_super) {
    __extends(FilesTreeView, _super);
    function FilesTreeView(opts) {
        _super.call(this, opts);
        this.fileTmpl = _.template(html.filesTreeFile);
        this.dirTmpl = _.template(html.filesTreeDir);
        this.subTreeTmpl = _.template(html.filesTreeSubtree);
        this.ft = FilesTree.getInstance();
        // TODO listen on events
    }
    FilesTreeView.prototype.render = function () {
        var _this = this;
        var currentDir = this.ft.getCurrentDir(), entries = currentDir.getEntriesTo();
        var entryTemplate = function (cur) {
            if (cur.isDir()) {
                return _this.dirTmpl(cur.toJSON());
            }
            return _this.fileTmpl(cur.toJSON());
        };
        var treeBuilder = function (entries) {
            if (entries.length === 0) {
                return '';
            }
            var cur = entries[0], remains = entries.slice(1), next = remains[0] || null;
            if (!next) {
                return entryTemplate(cur);
            }
            var subTree = _.map(cur.getSubEntries(), function (sub) {
                if (sub === next) {
                    return treeBuilder(remains);
                }
                return entryTemplate(sub);
            });
            var payload = cur.toJSON();
            payload['sub_tree'] = subTree.join("\n");
            return _this.subTreeTmpl(payload);
        };
        var tree = treeBuilder(entries.reverse());
        $('.chart-stage .files-tree', this.$el).html(tree);
        return this;
    };
    return FilesTreeView;
})(Backbone.View);
/// <reference path="../_ref.d.ts" />
var UserModel = (function (_super) {
    __extends(UserModel, _super);
    function UserModel() {
        _super.apply(this, arguments);
    }
    UserModel.prototype.defaults = function () {
        return {
            uid: 0,
            name: '',
            homeDir: '/'
        };
    };
    UserModel.prototype.getUid = function () {
        return this.get('uid');
    };
    UserModel.prototype.getName = function () {
        return this.get('name');
    };
    UserModel.prototype.getHomeDir = function () {
        return null;
    };
    return UserModel;
})(Backbone.Model);
var UserCollection = (function (_super) {
    __extends(UserCollection, _super);
    function UserCollection() {
        _super.apply(this, arguments);
    }
    // Dump users into user block.
    UserCollection.prototype.store = function () {
        return '';
    };
    // Restore users from user block.
    UserCollection.prototype.restore = function (userBlock) {
        return this;
    };
    return UserCollection;
})(Backbone.Collection);
/// <reference path="./_ref.d.ts" />
var root = new FileEntryModel({
    'name': 'home',
    'entryType': FileEntryModel.TypeDir
});
var s = new FileEntryModel({
    'name': 'foo',
    'entryType': FileEntryModel.TypeFile
});
root.addSubEntry(s);
FilesTree.getInstance().setRoot(root).chdir('home/foo');
(new FilesTreeView({ el: $('#files-tree') })).render();
