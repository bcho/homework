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

console.log(root.store());


FilesTree.getInstance()
    .setRoot(root)
    .chdir('home/foo');

(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
(new PromptView({ el: $('#command-prompt') })).render();
