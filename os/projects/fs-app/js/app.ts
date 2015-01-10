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

FilesTree.getInstance()
    .setRoot(root)
    .chdir('home/foo');

(new FilesTreeView({ el: $('#files-tree') })).render();
