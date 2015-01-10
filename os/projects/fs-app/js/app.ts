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
    'name': 'foo',
    'entryType': FileEntryModel.TypeDir
});

root.addSubEntry(s);
s.addSubEntry(b);

FilesTree.getInstance()
    .setRoot(root)
    .chdir('home/foo/foo');

(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();

window.setTimeout(() => {
    FilesTree.getInstance()
        .chdir('home/foo');
}, 2000);
