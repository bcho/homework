/// <reference path="../_ref.d.ts" />

class UserInfosView extends Backbone.View<Backbone.Model> {
    
    $el: JQuery;

    protected userManager: UserManager;
    protected meTmpl = _.template(html.userInfosMe);

    constructor(opts?: any) {
        super(opts);

        this.userManager = UserManager.getInstance();

        this.listenTo(this.userManager, 'current_user:changed', this.render);
        this.listenTo(this.userManager, 'users:changed', this.render);
    }

    render(): UserInfosView {
        var currentUser = this.userManager.getCurrentUser();

        $('#user-me', this.$el).html(this.meTmpl({
            currentUserName: currentUser ? currentUser.get('name') : '',
            count: this.userManager.getUsersCount()
        }));

        return this;
    }
}
