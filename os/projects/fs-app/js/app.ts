/// <reference path="./_ref.d.ts" />

var root = UserManager.getInstance().createUser('root'),
    hbc = UserManager.getInstance().createUser('hbc');

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


// Bootstrap.
Shell.getInstance()
    .execute(shlex('create log.txt'))
    .execute(shlex('create mail.txt'))
    .execute(shlex('mkdir Documents'))
    .execute(shlex('cd Documents'))
    .execute(shlex('create diary.docx'))
    .execute(shlex('cd ..'));


(new FilesTreeView({ el: $('#files-tree') })).render();
(new FilesDirectoryView({ el: $('#files-directory') })).render();
(new DiskUsageView({ el: $('#disk-infos') })).render();
(new UserInfosView({ el: $('#user-infos') })).render();
(new PromptView({ el: $('#command-prompt') })).render();
