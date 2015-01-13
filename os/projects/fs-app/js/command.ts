/// <reference path="./_ref.d.ts" />

var SHELL_EMPTY_FD = -1,
    SHELL_CURRENT_FD = SHELL_EMPTY_FD;

var SHELL_EMPTY_USER = null,
    SHELL_CURRENT_USER: UserModel = SHELL_EMPTY_USER;

var loginRequired = () => {
    var rv = {
        isOk: SHELL_CURRENT_USER !== SHELL_EMPTY_USER,
        reason: ''
    };

    if (!rv.isOk) {
        rv.reason = 'login required.';
    }

    return rv;
};

Shell.getInstance()

    // Change the working dir.
    //
    // TODO support absolute path.
    .install('cd', (env: Env, args: string[]): number => {
        if (args.length <= 0) {
            env.writeStderr('help: cd SUB_DIR');

            return 1;
        }

        var path = args[0],
            cwd = env.getCWD(),
            subDir: FileEntryModel;

        // XXX handle some special cases.
        if (path === '.') {
            subDir = cwd;
        } else if (path === '..') {
            subDir = cwd.getParentEntry();
        } else {
            subDir = env.getCWD().getSubEntryByName(args[0]);
        }

        if (! subDir || ! subDir.isDir()) {
            env.writeStderr('Cannot found dir: ' + args[0]);

            return 1;
        }

        sys_chdir(subDir);

        return 0;
    }, loginRequired)

    // Create a file.
    //
    // Open after creating.
    .install('create', (env: Env, args: string[]): number => {
        if (args.length <= 0) {
            env.writeStderr('help: create FILE_NAME');

            return 1;
        }

        try {
            var created = sys_create(
                env.getCWD(),
                args[0],
                FileEntryModel.TypeFile,
                env.getUser(),
                0,  // TODO implement permission
                0
            );
        } catch (e) {
            env.writeStderr('create: ' + e.message);
            
            return 1;
        }

        SHELL_CURRENT_FD = sys_open(created);

        return 0;
    }, loginRequired)
    
    // Create a directory.
    .install('mkdir', (env: Env, args: string[]): number => {
        if (args.length <= 0) {
            env.writeStderr('help: mkdir DIR_NAME');

            return 1;
        }

        try {
            sys_create(
                env.getCWD(),
                args[0],
                FileEntryModel.TypeDir,
                env.getUser(),
                0,  // TODO implement permission
                0
            );
        } catch (e) {
            env.writeStderr('mkdir: ' + e.message);

            return 1;
        }

        return 0;
    }, loginRequired)

    // Open a file.
    //
    // TODO support absolute path.
    .install('open', (env: Env, args: string[]): number => {
        if (args.length <= 0) {
            env.writeStderr('help: open FILE_NAME');

            return 1;
        }

        var cwd = env.getCWD(),
            file = cwd.getSubEntryByName(args[0]);

        if (!file || !file.isFile()) {
            env.writeStderr('open: unable to open ' + args[0]);

            return 1;
        }

        SHELL_CURRENT_FD = sys_open(file);
        env.writeStderr('open: file opened: ' + SHELL_CURRENT_FD);

        return 0;
    }, loginRequired)
    
    // Close opening file.
    .install('close', (env: Env, args: string[]): number => {
        if (SHELL_CURRENT_FD != SHELL_EMPTY_FD) {
            sys_close(SHELL_CURRENT_FD);
            SHELL_CURRENT_FD = SHELL_EMPTY_FD;
            env.writeStderr('close: file closed');
        }

        return 0;
    }, loginRequired)

    // Read from opening file.
    .install('read', (env: Env, args: string[]): number => {
        if (SHELL_CURRENT_FD === SHELL_EMPTY_FD) {
            env.writeStderr('read: open a file first');

            return 1;
        }

        env.writeStdout('read:' + sys_read(SHELL_CURRENT_FD));
        return 0;
    }, loginRequired)

    // Write to opening file.
    .install('write', (env: Env, args: string[]): number => {
        if (SHELL_CURRENT_FD === SHELL_EMPTY_FD) {
            env.writeStderr('write: open a file first');

            return 1;
        }

        if (args.length < 1) {
            env.writeStderr('help: write CONTENT');

            return 1;
        }

        sys_write(SHELL_CURRENT_FD, args[0]);
        env.writeStdout('write: wrote');

        return 0;
    }, loginRequired)

    // Delete an entry.
    .install('rm', (env: Env, args: string[]): number => {
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
            sys_delete(entry);
            
            env.writeStderr('rm: removed');
        } catch (e) {
            env.writeStderr('rm: failed ' + e.message);
            return 1;
        }

        return 0;
    }, loginRequired)

    // Login an user.
    .install('login', (env: Env, args: string[]): number => {
        if (args.length < 1) {
            env.writeStderr('help: login USERNAME');

            return 1;
        }
        
        var user = UserManager.getInstance().findUserByName(args[0]);
        if (!user) {
            env.writeStderr('login: cannot find user: ' + args[0]);

            return 1;
        }


        SHELL_CURRENT_USER = user;
        env.writeStderr('login: login successfully');
        return 0;
    })

    // Logout.
    .install('logout', (env: Env, args: string[]): number => {
        if (SHELL_CURRENT_USER != SHELL_EMPTY_USER) {
            SHELL_CURRENT_USER = SHELL_EMPTY_USER;
            env.writeStderr('logout: logout successfully');
        }
        
        return 0;
    }, loginRequired);
