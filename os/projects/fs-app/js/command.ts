/// <reference path="./_ref.d.ts" />

Shell.getInstance()
    .install('cd', (env: Env, args: string[]): number => {
        if (args.length <= 0) {
            return;
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
    });
