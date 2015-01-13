/// <reference path="../_ref.d.ts" />


interface CommandInterface {
    (env: Env, args: string[]): number
}

interface OkToRun {
    isOk: boolean
    reason: string
}

interface BeforeCommand {
    (opts?: any): OkToRun
}


interface Env {
    
    // Read from stdin.
    readStdin(): string

    // Write to stdout.
    writeStdout(output: string): void

    // Write to stderr.
    writeStderr(output: string): void

    // Get current user.
    getUser(): UserModel;

    // Get current working directory.
    getCWD(): FileEntryModel;
}


class ShellEnv implements Env {

    protected shell: Shell;

    constructor(shell: Shell) {
        this.shell = shell;
    }
    
    readStdin(): string {
        // XXX not implemented yet.
        return '';
    }

    writeStdout(output: string): void {
        this.shell.write(output);
    }

    writeStderr(output: string): void {
        this.shell.writeErr(output);
    }

    getUser(): UserModel {
        return UserManager.getInstance().getCurrentUser();
    }

    getCWD(): FileEntryModel {
        return FilesTree.getInstance().getCurrentDir();
    }
}


class Shell {
    
    private static instance: Shell;

    protected promptView: PromptView;
    protected commands: { [x: string]: CommandInterface } = {};

    public static getInstance(): Shell {
        if (! Shell.instance) {
            Shell.instance = new Shell();
        }

        return Shell.instance;
    }

    public setPromptView(view: PromptView): Shell {
        this.promptView = view;

        return this;
    }

    public execute(cmd: string[]): Shell {
        var name = cmd[0],
            args = cmd.slice(1);

        if (! _.has(this.commands, name)) {
            this.writeErr('Unknown command: ' + name);
        } else {
            var currentUser = UserManager.getInstance().getCurrentUser();

            if (! currentUser) {
                this.writeErr('Please login first.');
                return;
            }

            var env = new ShellEnv(this);

            this.commands[name](env, args);
        }

        return this;
    }

    public install(name: string,
                   cmd: CommandInterface,
                   checker?: BeforeCommand
                  ): Shell
    {
        var command = cmd;

        if (checker) {
            command = (env: Env, args: string[]) => {
                var checkerRv = checker();

                if (! checkerRv.isOk) {
                    env.writeStderr(checkerRv.reason);

                    return 1;
                }

                return cmd(env, args);
            };
        }

        this.commands[name] = command;

        return this;
    }

    public write(output: string): Shell {
        this.promptView.writeToScreen(output);

        return this;
    }

    public writeErr(output: string): Shell {
        // TODO style error.
        this.promptView.writeToScreen(output);

        return this;
    }

}
