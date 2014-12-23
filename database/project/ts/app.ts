/// <reference path="type/sql.d.ts" />
/// <reference path="type/jquery.d.ts" />
/// <reference path="type/underscore.d.ts" />
/// <reference path="type/backbone.d.ts" />

/// <reference path="partials/html.ts" />

// ----------------------------------------------------------------------------
// Models
// ----------------------------------------------------------------------------
class QueryResultModel extends Backbone.Model {

    defaults() {
        return {
            // Query statement.
            query: "",

            // Row fields.
            fields: [],

            // Query results.
            results: []
        }
    }

    getQuery(): string { return this.get('query'); }
    getFields(): string { return this.get('fields'); }
    getResults(): string { return this.get('results'); }
}

// ----------------------------------------------------------------------------
// Views
// ----------------------------------------------------------------------------
class HeaderView extends Backbone.View<Backbone.Model> {

    $navItems: JQuery

    constructor(options) {
        super(options);

        this.$navItems = $('li[role="presentation"]', this.$el);
    }

    events() {
        return {
            "click li[role=presentation] a": "switchView"
        }
    }

    switchView(e: any): HeaderView {
        return this.setActiviyView($(e.target.parentElement));
    }

    switchViewWithTabName(tabName: string): HeaderView {
        // TODO unifiy views naming scheme.
        var $target: JQuery = $('li[name=' + tabName + ']');

        if ($target) {
            this.setActiviyView($target);
        }

        return this;
    }

    private setActiviyView($target: JQuery): HeaderView {
        this.$navItems.removeClass('active');
        $target.addClass('active');

        return this;
    }
}

class StatView extends Backbone.View<QueryResultModel> {

    private $tableHead: JQuery
    private $tableBody: JQuery
    private $query: JQuery

    private tdTmpl = _.template('<td><%= d %></td>')
    private trTmpl = _.template('<tr><%= d %></tr>')
    private queryTmpl = _.template('<pre><%= d %></pre>')

    constructor(options) {
        super(options);

        this.$tableHead = $('#table thead', this.$el);
        this.$tableBody = $('#table tbody', this.$el);
        this.$query = $('#query .query', this.$el);
        this.listenTo(this.model, "change", this.render);
    }

    render(): StatView {
        this.renderQuery();
        this.renderTable();

        this.$el.height(window.innerHeight - 50);

        return this;
    }

    private renderQuery(): void {
        var q: string;

        q = this.queryTmpl({d: this.model.getQuery()});
        this.$query.html(q);
    }

    // TODO refactor
    private renderTable(): void {
        var rows: string[] = [],
            row: string[] = [],
            fieldName: string,
            fields =  this.model.getFields(),
            results = this.model.getResults(),
            model: any;

        // Render table header.
        for (var i = 0; i < fields.length; i++) {
            rows.push(this.tdTmpl({d: fields[i]}));
        }
        this.$tableHead.html(this.trTmpl({d: rows.join('') }));

        // Render table rows.
        rows = [];
        for (var i = 0; i < results.length; i++) {
            model = results[i];
            row = [];
            for (var j = 0; j < fields.length; j++) {
                fieldName = fields[j];
                row.push(this.tdTmpl({d: model[fieldName]}));
            }
            rows.push(this.trTmpl({
                d: row.join('')
            }));
        }
        this.$tableBody.html(rows.join(''));
    }
}

class FormView extends Backbone.View<Backbone.Model> {

    $el: JQuery

    render(content): FormView {
        this.$el.html(content);

        return this;
    }
}

// ----------------------------------------------------------------------------
// Route
// ----------------------------------------------------------------------------

class Route extends Backbone.Router {

    private formView: FormView
    private headerView: HeaderView

    constructor() {
        super()

        this.formView = new FormView({el: $('#form')});
        this.headerView = new HeaderView({el: $('#header')});
    }
    
    routes() {
        return {
            '': 'overview',
            'overview': 'overview',
            'book/borrow': 'bookBorrow',
            'book/return': 'bookReturn',
            'book/query': 'bookQuery',
            'book/add': 'bookAdd',
            'reader/query': 'readerQuery',
            'reader/add': 'readerAdd',
            'help': 'help'
        };
    }

    overview(): void {
        this.formView.render(html.overview);
        this.headerView.switchViewWithTabName('overview');
    }

    bookBorrow(): void {
        this.formView.render(html.bookborrow);
        this.headerView.switchViewWithTabName('bookborrow');
    }

    bookReturn(): void {
        this.formView.render(html.bookreturn);
        this.headerView.switchViewWithTabName('bookreturn');
    }

    bookQuery(): void {
        this.formView.render(html.bookquery);
        this.headerView.switchViewWithTabName('bookquery');
    }

    bookAdd(): void {
        this.formView.render(html.bookadd);
        this.headerView.switchViewWithTabName('bookadd');
    }

    readerQuery(): void {
        this.formView.render(html.readerquery);
        this.headerView.switchViewWithTabName('readerquery');
    }

    readerAdd(): void {
        this.formView.render(html.readeradd);
        this.headerView.switchViewWithTabName('readeradd');
    }

    help(): void {
        this.formView.render(html.help);
        this.headerView.switchViewWithTabName('help');
    }

}

$(() => {
    new Route();
    Backbone.history.start();

    var q = new QueryResultModel(),
        statView = new StatView({el: $('#stats'), model: q});

    window.setTimeout(function () {
        q.set({
            'query': 'select * from products',
            'fields': ['id', 'name'],
            'results': [
                {
                    id: 1,
                    name: 'foobar'
                },
                {
                    id: 2,
                    name: 'test'
                }
            ]
        });
    }, 1000);
});
