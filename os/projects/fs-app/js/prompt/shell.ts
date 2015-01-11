/// <reference path="../_ref.d.ts" />


class Shell {
    
    private static instance: Shell;

    protected promptView: PromptView;

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
        this.promptView.writeToScreen(cmd.join(' '));

        return this;
    }

}
