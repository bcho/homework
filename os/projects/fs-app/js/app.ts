/// <reference path="./_ref.d.ts" />

var root = new FileEntryModel({
    'name': 'home',
    'entryType': FileEntryModel.TypeDir
});

FilesTree.getInstance()
    .setRoot(root)
    .chdir('home');


(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new DiskUsageView({ el: $('#disk-infos') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
(new PromptView({ el: $('#command-prompt') })).render();
