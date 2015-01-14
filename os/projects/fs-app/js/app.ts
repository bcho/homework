/// <reference path="./_ref.d.ts" />

var root = UserManager.getInstance().findUserByUid(1);

// Login as root.
sys_login(root);

// Init fs tree.
var rootDir = sys_create(
    null,
    'home',
    FileEntryModel.TypeDir,
    root,
    0,
    0
);

FilesTree.getInstance()
    .setRoot(rootDir)
    .chdir('home');


(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new DiskUsageView({ el: $('#disk-infos') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
(new PromptView({ el: $('#command-prompt') })).render();
