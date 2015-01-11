/// <reference path="./_ref.d.ts" />

var root = new FileEntryModel({
    'name': 'home',
    'entryType': FileEntryModel.TypeDir
});

var s = new FileEntryModel({
    'name': 'foo',
    'entryType': FileEntryModel.TypeDir
});

var b = new FileEntryModel({
    'name': 'bar',
    'entryType': FileEntryModel.TypeFile
});

var c = new FileEntryModel({
    'name': 'baz',
    'entryType': FileEntryModel.TypeDir
});

root.addSubEntry(s);
s.addSubEntry(b);
s.addSubEntry(c);

FilesTree.getInstance()
    .setRoot(root)
    .chdir('home/foo');

var u = new UserModel({ uid: 1, name: 'root' }),
    u2 = new UserModel({ uid: 2, name: 'hbc' }),
    d = new UserCollection([u, u2]);

UserManager.getInstance()
    .setUsers(d)
    .setCurrentUser(u);

(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
