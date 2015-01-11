/// <reference path="../_ref.d.ts" />

class PromptView extends Backbone.View<Backbone.Model> {

    $el: JQuery;

    protected shell: Shell;
    protected $screen: JQuery;
    protected $input: JQuery;
    
    protected lineTmpl = _.template('<p><%= line %></p>');

    constructor(opts?: any) {
        super(opts);

        this.$screen = $('.prompt-screen', this.$el);
        this.$input = $('.prompt-input', this.$el);

        this.shell = Shell.getInstance().setPromptView(this);
    }

    events(): any {
        return {
            'keypress .prompt-input': 'checkInput'
        };
    }

    writeToScreen(line: string): PromptView {
        this.$screen.append(this.lineTmpl({ line: line }));

        this.$screen.scrollTop(this.$screen.prop('scrollHeight'));

        return this;
    }

    checkInput(e): boolean {
        if (e.which !== 13) {
            return;
        }

        var cmd = shlex(this.$input.val());

        this.shell.execute(cmd);

        this.$input.val('');

        return false;
    }

}
