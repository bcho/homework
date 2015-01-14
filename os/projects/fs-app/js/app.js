/// <reference path="./_ref.d.ts" />
/// <reference path="./_ref.d.ts" />
var pathNotFoundException = function (path) {
    throw new Error('Path: ' + path + ' not found.');
};
var invalidEntryTypeException = function () {
    throw new Error('Invalid entry type.');
};
var ioFailedException = function (msg) {
    msg = msg || 'IO failed';
    throw new Error(msg);
};
var duplicatedFilesException = function (name) {
    throw new Error('Duplicated files: ' + name);
};
var html;
(function (html) {
    html.diskUsageUnused = ["<li></li>", ""].join("\n");
    html.diskUsageUsed = ["<li class=\"used\"></li>", ""].join("\n");
    html.filesDirectoryBreadcrumbActive = ["<li class=\"active\" data-path=\"<%= path %>\">", "    <%= name %>", "</li>", ""].join("\n");
    html.filesDirectoryBreadcrumb = ["<li>", "    <a data-path=\"<%= path %>\"><%= name %></a>", "</li>", ""].join("\n");
    html.filesDirectoryDir = ["<div class=\"file col-sm-2\" data-name=\"<%= name %>\" title=\"<%= infos %>\">", "    <a data-path=\"<%= path %>\">", "        <header class=\"file-icon\">", "            <i class=\"fa fa-folder-o\"></i>", "        </header>", "        <section class=\"file-meta\">", "            <h3><%= name %></h3>", "        </section>", "    </a>", "</div>", ""].join("\n");
    html.filesDirectoryFile = ["<div class=\"file col-sm-2\" data-name=\"<%= name %>\" title=\"<%= infos %>\">", "    <header class=\"file-icon\">", "        <i class=\"fa fa-file-word-o\"></i>", "    </header>", "    <section class=\"file-meta\">", "        <h3><%= name %></h3>", "    </section>", "</div>", ""].join("\n");
    html.filesTreeDir = ["<li>", "    <i class=\"fa fa-folder-o\"></i>", "    <a data-path=\"<%= path %>\"><%= name %></a>", "</li>", ""].join("\n");
    html.filesTreeFile = ["<li data-path=\"<%= path %>\">", "    <i class=\"fa fa-file-word-o\"></i>", "    <%= name %>", "</li>", ""].join("\n");
    html.filesTreeSubtree = ["<li>", "    <i class=\"fa fa-folder-open-o\"></i>", "    <a data-path=\"<%= path %>\"><%= name %></a>", "</li>", "<li class=\"files-tree-sub\">", "    <ul class=\"files-tree\">", "        <%= sub_tree %>", "    </ul>", "</li>", ""].join("\n");
    html.userInfosMe = ["<p>当前用户：<span class=\"badge\"><%= currentUserName %></span></p>", "<p>用户总数：<span class=\"badge\"><%= count %></span></p>", ""].join("\n");
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
        };
    };
    FileEntryModel.prototype.read = function () {
        return this.get('content');
    };
    FileEntryModel.prototype.write = function (buffer) {
        this.set({
            'content': buffer,
            'mtime': new Date
        });
        FilesTree.getInstance().flush();
        return buffer.length;
    };
    FileEntryModel.create = function (parent, name, entryType, owner, ownerPerm, otherPerm) {
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
        return path.reverse();
    };
    FileEntryModel.prototype.getPath = function () {
        var path = [this.get('name')], cur = this, parentEntry;
        while ((parentEntry = cur.get('parentEntry')) !== null) {
            cur = parentEntry;
            path.push(cur.get('name'));
        }
        return path.reverse().join('/');
    };
    FileEntryModel.prototype.getSubEntries = function () {
        return this.get('subEntries');
    };
    FileEntryModel.prototype.addSubEntry = function (sub) {
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
    FileEntryModel.prototype.getParentEntry = function () {
        return this.get('parentEntry');
    };
    FileEntryModel.prototype.unlink = function (subEntry) {
        var entries = _(this.getSubEntries()).filter(function (e) {
            return e !== subEntry;
        });
        this.set('subEntries', entries);
        FilesTree.getInstance().flush();
        return this;
    };
    FileEntryModel.prototype.toJSON = function (options) {
        var encoded = _super.prototype.toJSON.call(this, options);
        encoded['path'] = this.getPath();
        return encoded;
    };
    FileEntryModel.prototype.storeAsObject = function () {
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
        }
        else if (this.isDir()) {
            var subEntries = _.map(this.getSubEntries(), function (e) {
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
    };
    FileEntryModel.prototype.store = function () {
        return JSON.stringify(this.storeAsObject()).trim();
    };
    // not implemented.
    FileEntryModel.prototype.restore = function (buffer) {
        return null;
    };
    FileEntryModel.TypeEmpty = 0;
    FileEntryModel.TypeFile = 1;
    FileEntryModel.TypeDir = 2;
    return FileEntryModel;
})(Backbone.Model);
var FilesTree = (function (_super) {
    __extends(FilesTree, _super);
    function FilesTree() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);
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
        return this.chdirByEntry(found);
    };
    FilesTree.prototype.chdirByEntry = function (entry) {
        this.currentDir = entry;
        this.trigger('cwd:changed');
        return this;
    };
    // Set root entry.
    FilesTree.prototype.setRoot = function (root) {
        this.rootEntry = root;
        this.trigger('root:changed');
        this.store();
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
    // Flush disk.
    FilesTree.prototype.flush = function () {
        // XXX
        if (this.rootEntry) {
            this.store();
            this.trigger('fs:flushed');
        }
    };
    // Dump into files block.
    FilesTree.prototype.store = function () {
        return Disk.getInstance().store();
    };
    // Restore from files block.
    FilesTree.prototype.restore = function (fileBlock) {
        return this;
    };
    FilesTree.instance = null;
    return FilesTree;
})(Backbone.Events);
var Disk = (function (_super) {
    __extends(Disk, _super);
    function Disk() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);
        this.users = UserManager.getInstance();
        this.files = FilesTree.getInstance();
        this.reset();
    }
    Disk.getInstance = function () {
        if (!Disk.instance) {
            Disk.instance = new Disk();
        }
        return Disk.instance;
    };
    Disk.prototype.getBlocksMap = function () {
        return this.used.slice();
    };
    // Dump disk.
    Disk.prototype.store = function () {
        this.reset();
        this.storeFileEntries();
        this.trigger('disk:changed');
        return this.blocks.join('');
    };
    // Restore disk.
    Disk.prototype.restore = function (disk) {
        // TODO
        return this;
    };
    Disk.prototype.allocate = function (size) {
        var taken = 0;
        for (var i = 0; i < Disk.UsableBlocks; i++) {
            if (this.used[i]) {
                continue;
            }
            for (var j = i, taken = size; taken > 0 && !this.used[j];) {
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
    };
    Disk.prototype.reset = function () {
        this.used = [];
        this.blocks = [];
        for (var i = 0; i < Disk.UsableBlocks; i++) {
            this.used.push(false);
            for (var j = 0; j < Disk.BlockWidth; j++) {
                this.blocks.push(' ');
            }
        }
    };
    Disk.prototype.storeFileEntries = function () {
        var _this = this;
        var root = this.files.getRoot();
        var dump = function (node) {
            if (node.isDir()) {
                var subEntryPos = [];
                _.each(node.getSubEntries(), function (e) {
                    subEntryPos.push(dump(e));
                });
            }
            var dumped = node.store();
            var startsAt = _this.allocate(dumped.length);
            node.set('startsAt', startsAt);
            for (var i = 0; i < dumped.length; i++) {
                _this.blocks[startsAt + i] = dumped[i];
            }
            return startsAt;
        };
        dump(this.files.getRoot());
    };
    Disk.instance = null;
    Disk.UsableBlocks = 256;
    Disk.BlockWidth = 64;
    return Disk;
})(Backbone.Events);
/// <reference path="../_ref.d.ts" />
var FilesTreeView = (function (_super) {
    __extends(FilesTreeView, _super);
    function FilesTreeView(opts) {
        _super.call(this, opts);
        this.fileTmpl = _.template(html.filesTreeFile);
        this.dirTmpl = _.template(html.filesTreeDir);
        this.subTreeTmpl = _.template(html.filesTreeSubtree);
        this.ft = FilesTree.getInstance();
        this.listenTo(this.ft, 'cwd:changed', this.render);
        this.listenTo(this.ft, 'fs:flushed', this.flush);
    }
    FilesTreeView.prototype.events = function () {
        return {
            'click a[data-path]': 'chdir'
        };
    };
    FilesTreeView.prototype.flush = function () {
        this.render();
        this.delegateEvents();
    };
    FilesTreeView.prototype.render = function () {
        var _this = this;
        var currentDir = this.ft.getCurrentDir(), entries = currentDir.getEntriesTo();
        var info = function (cur) {
            return [
                'Owner: ' + cur.get('oid'),
                'Created at: ' + cur.get('ctime'),
                'Edited at: ' + cur.get('mtime')
            ].join("\n");
        };
        var entryTemplate = function (cur) {
            var payload = cur.toJSON();
            payload['infos'] = info(cur);
            if (cur.isDir()) {
                return _this.dirTmpl(payload);
            }
            return _this.fileTmpl(payload);
        };
        var treeBuilder = function (entries) {
            if (entries.length === 0) {
                return '';
            }
            var cur = entries[0], remains = entries.slice(1), next = remains[0] || null;
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
        var tree = treeBuilder(entries);
        $('.chart-stage .files-tree', this.$el).html(tree);
        return this;
    };
    FilesTreeView.prototype.chdir = function (e) {
        this.ft.chdir($(e.currentTarget).data('path'));
        return false;
    };
    return FilesTreeView;
})(Backbone.View);
var FilesDirectoryView = (function (_super) {
    __extends(FilesDirectoryView, _super);
    function FilesDirectoryView(opts) {
        _super.call(this, opts);
        this.ft = FilesTree.getInstance();
        this.listenTo(this.ft, 'cwd:changed', this.render);
        this.listenTo(this.ft, 'fs:flushed', this.flush);
    }
    FilesDirectoryView.prototype.events = function () {
        return {
            'click a[data-path]': 'chdir'
        };
    };
    FilesDirectoryView.prototype.flush = function () {
        this.render();
        this.delegateEvents();
    };
    FilesDirectoryView.prototype.render = function () {
        var currentDir = this.ft.getCurrentDir();
        this.renderBreadcrumbs(currentDir);
        this.renderSubEntries(currentDir);
        return this;
    };
    FilesDirectoryView.prototype.renderBreadcrumbs = function (currentDir) {
        var path = currentDir.getEntriesTo();
        var parentTmpl = _.template(html.filesDirectoryBreadcrumb), curTmpl = _.template(html.filesDirectoryBreadcrumbActive);
        path.pop();
        var parts = _.map(path, function (p) {
            return parentTmpl(p.toJSON());
        });
        parts.push(curTmpl(currentDir.toJSON()));
        $('.breadcrumb', this.$el).html(parts.join("\n"));
    };
    FilesDirectoryView.prototype.renderSubEntries = function (currentDir) {
        var entries = currentDir.getSubEntries();
        var dirTmpl = _.template(html.filesDirectoryDir), fileTmpl = _.template(html.filesDirectoryFile);
        var info = function (cur) {
            var owner = UserManager.getInstance().findUserByUid(cur.get('oid'));
            return [
                'Owner: ' + owner.get('name'),
                'Created at: ' + cur.get('ctime'),
                'Edited at: ' + cur.get('mtime')
            ].join("\n");
        };
        var icons = _.map(entries, function (cur) {
            var payload = cur.toJSON();
            payload['infos'] = info(cur);
            if (cur.isDir()) {
                return dirTmpl(payload);
            }
            return fileTmpl(payload);
        });
        $('.chart-stage', this.$el).html(icons.join("\n"));
    };
    FilesDirectoryView.prototype.chdir = function (e) {
        this.ft.chdir($(e.currentTarget).data('path'));
        return false;
    };
    return FilesDirectoryView;
})(Backbone.View);
var DiskUsageView = (function (_super) {
    __extends(DiskUsageView, _super);
    function DiskUsageView(opts) {
        _super.call(this, opts);
        this.usedBlockTmpl = _.template(html.diskUsageUsed);
        this.unusedBlockTmpl = _.template(html.diskUsageUnused);
        this.disk = Disk.getInstance();
        this.listenTo(this.disk, 'disk:changed', this.render);
    }
    DiskUsageView.prototype.render = function () {
        var _this = this;
        var blocks = _.map(this.disk.getBlocksMap(), function (node) {
            return node ? _this.usedBlockTmpl(node) : _this.unusedBlockTmpl(node);
        });
        $('.disk-nodes', this.$el).html(blocks.join(''));
        return this;
    };
    return DiskUsageView;
})(Backbone.View);
/// <reference path="../_ref.d.ts" />
// TODO record mode (read or write).
var OPENED_FILES = [
    null,
    null,
    null,
    null,
], OPENED_FILES_STARTS_AT = 4; // XXX oops
// Change working dir.
var sys_chdir = function (entry) {
    FilesTree.getInstance().chdirByEntry(entry);
    return 0;
};
// Open a file and return file descriptor.
//
// TODO record mode.
var sys_open = function (entry, mode) {
    // TODO check permission
    for (var i = OPENED_FILES_STARTS_AT; i < OPENED_FILES.length; i++) {
        if (OPENED_FILES[i] === null) {
            OPENED_FILES[i] = entry;
            return i;
        }
    }
    OPENED_FILES.push(entry);
    return OPENED_FILES.length - 1;
};
// Close a file descriptior.
var sys_close = function (fd) {
    OPENED_FILES[fd] = null;
    return 0;
};
// Read from file descriptor.
var sys_read = function (fd) {
    if (!OPENED_FILES[fd]) {
        ioFailedException('cannot read from: ' + fd);
    }
    return OPENED_FILES[fd].read();
};
// Write to file descriptor.
var sys_write = function (fd, content) {
    if (!OPENED_FILES[fd]) {
        ioFailedException('cannot write to: ' + fd);
    }
    return OPENED_FILES[fd].write(content);
};
// Create an entry.
var sys_create = function (parent, name, entryType, owner, ownerPerm, otherPerm) {
    return FileEntryModel.create(parent, name, entryType, owner, ownerPerm, otherPerm);
};
// Delete an entry.
var sys_delete = function (user, entry) {
    var parentEntry = entry.getParentEntry();
    // TODO: more permission check.
    if (user.getUid() != entry.get('oid')) {
        ioFailedException('cannot remove files');
    }
    if (parentEntry) {
        parentEntry.unlink(entry);
    }
    else {
        ioFailedException('cannot unlink root'); // XXX
    }
    return 0;
};
/// <reference path="../_ref.d.ts" />
var UserModel = (function (_super) {
    __extends(UserModel, _super);
    function UserModel() {
        _super.apply(this, arguments);
    }
    UserModel.prototype.defaults = function () {
        return {
            uid: 0,
            name: ''
        };
    };
    UserModel.prototype.getUid = function () {
        return this.get('uid');
    };
    UserModel.prototype.getName = function () {
        return this.get('name');
    };
    UserModel.prototype.getHomeDir = function () {
        var homePath = 'home/' + this.getName();
        return FilesTree.getInstance().findByAbsolutePath(homePath);
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
var UserManager = (function (_super) {
    __extends(UserManager, _super);
    function UserManager() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);
        // Bootstrap users.
        this.users = new UserCollection();
    }
    UserManager.getInstance = function () {
        if (!UserManager.instance) {
            UserManager.instance = new UserManager();
        }
        return UserManager.instance;
    };
    // Create an user.
    UserManager.prototype.createUser = function (name) {
        UserManager.uidCounter += 1;
        var user = new UserModel({
            name: name,
            uid: UserManager.uidCounter
        });
        this.users.push(user);
        this.trigger('users:changed');
        return user;
    };
    // Get current user.
    UserManager.prototype.getCurrentUser = function () {
        return this.currentUser;
    };
    // Set current user.
    UserManager.prototype.setCurrentUser = function (user) {
        this.currentUser = user;
        this.trigger('current_user:changed');
        return this;
    };
    // Set users.
    UserManager.prototype.setUsers = function (users) {
        this.users = users;
        return this;
    };
    // Find an user by uid.
    UserManager.prototype.findUserByUid = function (uid) {
        return this.users.findWhere({ uid: uid });
    };
    // Find an user by name.
    UserManager.prototype.findUserByName = function (name) {
        return this.users.findWhere({ name: name });
    };
    // Get #users.
    UserManager.prototype.getUsersCount = function () {
        return this.users.length;
    };
    UserManager.instance = null;
    UserManager.uidCounter = 0;
    return UserManager;
})(Backbone.Events);
/// <reference path="../_ref.d.ts" />
var UserInfosView = (function (_super) {
    __extends(UserInfosView, _super);
    function UserInfosView(opts) {
        _super.call(this, opts);
        this.meTmpl = _.template(html.userInfosMe);
        this.userManager = UserManager.getInstance();
        this.listenTo(this.userManager, 'current_user:changed', this.render);
        this.listenTo(this.userManager, 'users:changed', this.render);
    }
    UserInfosView.prototype.render = function () {
        var currentUser = this.userManager.getCurrentUser();
        $('#user-me', this.$el).html(this.meTmpl({
            currentUserName: currentUser ? currentUser.get('name') : '',
            count: this.userManager.getUsersCount()
        }));
        return this;
    };
    return UserInfosView;
})(Backbone.View);
/// <reference path="../_ref.d.ts" />
var sys_login = function (user) {
    UserManager.getInstance().setCurrentUser(user);
    return 0;
};
/// <reference path="../_ref.d.ts" />
var PromptView = (function (_super) {
    __extends(PromptView, _super);
    function PromptView(opts) {
        _super.call(this, opts);
        this.lineTmpl = _.template('<p><%= line %></p>');
        this.$screen = $('.prompt-screen', this.$el);
        this.$input = $('.prompt-input', this.$el);
        this.shell = Shell.getInstance().setPromptView(this);
    }
    PromptView.prototype.events = function () {
        return {
            'keypress .prompt-input': 'checkInput'
        };
    };
    PromptView.prototype.writeToScreen = function (line) {
        this.$screen.append(this.lineTmpl({ line: line }));
        this.$screen.scrollTop(this.$screen.prop('scrollHeight'));
        return this;
    };
    PromptView.prototype.checkInput = function (e) {
        if (e.which !== 13) {
            return;
        }
        var cmd = shlex(this.$input.val());
        this.shell.execute(cmd);
        this.$input.val('');
        return false;
    };
    return PromptView;
})(Backbone.View);
/// <reference path="../_ref.d.ts" />
var ShellEnv = (function () {
    function ShellEnv(shell) {
        this.shell = shell;
    }
    ShellEnv.prototype.readStdin = function () {
        // XXX not implemented yet.
        return '';
    };
    ShellEnv.prototype.writeStdout = function (output) {
        this.shell.write(output);
    };
    ShellEnv.prototype.writeStderr = function (output) {
        this.shell.writeErr(output);
    };
    ShellEnv.prototype.getUser = function () {
        return UserManager.getInstance().getCurrentUser();
    };
    ShellEnv.prototype.getCWD = function () {
        return FilesTree.getInstance().getCurrentDir();
    };
    return ShellEnv;
})();
var Shell = (function () {
    function Shell() {
        this.commands = {};
    }
    Shell.getInstance = function () {
        if (!Shell.instance) {
            Shell.instance = new Shell();
        }
        return Shell.instance;
    };
    Shell.prototype.setPromptView = function (view) {
        this.promptView = view;
        return this;
    };
    Shell.prototype.execute = function (cmd) {
        var name = cmd[0], args = cmd.slice(1);
        if (!_.has(this.commands, name)) {
            this.writeErr('Unknown command: ' + name);
        }
        else {
            var env = new ShellEnv(this);
            this.commands[name](env, args);
        }
        return this;
    };
    Shell.prototype.install = function (name, cmd, checker) {
        var command = cmd;
        if (checker) {
            command = function (env, args) {
                var checkerRv = checker();
                if (!checkerRv.isOk) {
                    env.writeStderr(checkerRv.reason);
                    return 1;
                }
                return cmd(env, args);
            };
        }
        this.commands[name] = command;
        return this;
    };
    Shell.prototype.write = function (output) {
        this.promptView.writeToScreen(output);
        return this;
    };
    Shell.prototype.writeErr = function (output) {
        // TODO style error.
        this.promptView.writeToScreen(output);
        return this;
    };
    return Shell;
})();
/// <reference path="../_ref.d.ts" />
// @see https://gist.github.com/OllieTerrance/6280851
var shlex = function (str) {
    var args = str.split(" ");
    var out = [];
    var lookForClose = -1;
    var quoteOpen = false;
    for (var x in args) {
        if (args.hasOwnProperty(x)) {
            var arg = args[x];
            var escSeq = false;
            for (var y in arg) {
                if (escSeq) {
                    escSeq = false;
                }
                else if (arg[y] === "\\") {
                    escSeq = true;
                }
                else if (arg[y] === "\"") {
                    quoteOpen = !quoteOpen;
                }
            }
            if (!quoteOpen && lookForClose === -1) {
                out.push(arg);
            }
            else if (quoteOpen && lookForClose === -1) {
                lookForClose = x;
            }
            else if (!quoteOpen && lookForClose >= 0) {
                var block = args.slice(lookForClose, parseInt(x) + 1).join(" ");
                var escSeq = false;
                var quotes = [];
                for (var y in block) {
                    if (escSeq) {
                        escSeq = false;
                    }
                    else if (block[y] === "\\") {
                        escSeq = true;
                    }
                    else if (block[y] === "\"") {
                        quotes.push(y);
                    }
                }
                var parts = [];
                parts.push(block.substr(0, quotes[0]));
                parts.push(block.substr(parseInt(quotes[0]) + 1, quotes[1] - (parseInt(quotes[0]) + 1)));
                parts.push(block.substr(parseInt(quotes[1]) + 1));
                block = parts.join("");
                out.push(block);
                lookForClose = -1;
            }
        }
    }
    return quoteOpen ? false : out;
};
/// <reference path="./_ref.d.ts" />
var SHELL_EMPTY_FD = -1, SHELL_CURRENT_FD = SHELL_EMPTY_FD;
var isUserLogined = function () {
    return UserManager.getInstance().getCurrentUser() !== null;
};
var loginRequired = function () {
    var rv = {
        isOk: isUserLogined(),
        reason: ''
    };
    if (!rv.isOk) {
        rv.reason = 'login required.';
    }
    return rv;
};
Shell.getInstance().install('cd', function (env, args) {
    if (args.length <= 0) {
        env.writeStderr('help: cd SUB_DIR');
        return 1;
    }
    var path = args[0], cwd = env.getCWD(), subDir;
    // XXX handle some special cases.
    if (path === '.') {
        subDir = cwd;
    }
    else if (path === '..') {
        subDir = cwd.getParentEntry();
    }
    else {
        subDir = env.getCWD().getSubEntryByName(args[0]);
    }
    if (!subDir || !subDir.isDir()) {
        env.writeStderr('Cannot found dir: ' + args[0]);
        return 1;
    }
    sys_chdir(subDir);
    return 0;
}, loginRequired).install('create', function (env, args) {
    if (args.length <= 0) {
        env.writeStderr('help: create FILE_NAME');
        return 1;
    }
    try {
        var created = sys_create(env.getCWD(), args[0], FileEntryModel.TypeFile, env.getUser(), 0, 0);
    }
    catch (e) {
        env.writeStderr('create: ' + e.message);
        return 1;
    }
    SHELL_CURRENT_FD = sys_open(created);
    return 0;
}, loginRequired).install('mkdir', function (env, args) {
    if (args.length <= 0) {
        env.writeStderr('help: mkdir DIR_NAME');
        return 1;
    }
    try {
        sys_create(env.getCWD(), args[0], FileEntryModel.TypeDir, env.getUser(), 0, 0);
    }
    catch (e) {
        env.writeStderr('mkdir: ' + e.message);
        return 1;
    }
    return 0;
}, loginRequired).install('open', function (env, args) {
    if (args.length <= 0) {
        env.writeStderr('help: open FILE_NAME');
        return 1;
    }
    var cwd = env.getCWD(), file = cwd.getSubEntryByName(args[0]);
    if (!file || !file.isFile()) {
        env.writeStderr('open: unable to open ' + args[0]);
        return 1;
    }
    SHELL_CURRENT_FD = sys_open(file);
    env.writeStderr('open: file opened: ' + SHELL_CURRENT_FD);
    return 0;
}, loginRequired).install('close', function (env, args) {
    if (SHELL_CURRENT_FD != SHELL_EMPTY_FD) {
        sys_close(SHELL_CURRENT_FD);
        SHELL_CURRENT_FD = SHELL_EMPTY_FD;
        env.writeStderr('close: file closed');
    }
    return 0;
}, loginRequired).install('read', function (env, args) {
    if (SHELL_CURRENT_FD === SHELL_EMPTY_FD) {
        env.writeStderr('read: open a file first');
        return 1;
    }
    env.writeStdout('read:' + sys_read(SHELL_CURRENT_FD));
    return 0;
}, loginRequired).install('write', function (env, args) {
    if (SHELL_CURRENT_FD === SHELL_EMPTY_FD) {
        env.writeStderr('write: open a file first');
        return 1;
    }
    if (args.length < 1) {
        env.writeStderr('help: write CONTENT');
        return 1;
    }
    sys_write(SHELL_CURRENT_FD, args.join(' '));
    env.writeStdout('write: wrote');
    return 0;
}, loginRequired).install('rm', function (env, args) {
    if (args.length < 1) {
        env.writeStderr('help: rm NAME');
        return 1;
    }
    var entry = env.getCWD().getSubEntryByName(args[0]);
    if (!entry) {
        env.writeStderr('rm: unable to remove ' + args[0]);
        return 1;
    }
    try {
        sys_delete(env.getUser(), entry);
    }
    catch (e) {
        env.writeStderr('rm: ' + e.message);
        return 1;
    }
    return 0;
}, loginRequired).install('login', function (env, args) {
    if (args.length < 1) {
        env.writeStderr('help: login USERNAME');
        return 1;
    }
    var user = UserManager.getInstance().findUserByName(args[0]);
    if (!user) {
        env.writeStderr('login: cannot find user: ' + args[0]);
        return 1;
    }
    sys_login(user);
    env.writeStderr('login: login successfully');
    return 0;
}).install('logout', function (env, args) {
    if (isUserLogined()) {
        UserManager.getInstance().setCurrentUser(null);
        env.writeStderr('logout: logout successfully');
    }
    return 0;
}, loginRequired);
/// <reference path="./_ref.d.ts" />
var root = UserManager.getInstance().createUser('root'), hbc = UserManager.getInstance().createUser('hbc');
// Login as root.
sys_login(root);
// Init fs tree.
var rootDir = sys_create(null, 'home', FileEntryModel.TypeDir, root, 0, 0);
FilesTree.getInstance().setRoot(rootDir).chdir('home');
(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new DiskUsageView({ el: $('#disk-infos') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
(new PromptView({ el: $('#command-prompt') })).render();
