/// <reference path="type/sql.d.ts" />
/// <reference path="type/jquery.d.ts" />
/// <reference path="type/underscore.d.ts" />
/// <reference path="type/backbone.d.ts" />

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

    get query(): string { return this.get('query'); }
    get fields(): string { return this.get('fields'); }
    get results(): string { return this.get('results'); }
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
        this.$navItems.removeClass('active');
        $(e.target.parentElement).addClass('active');

        return this;
    }
}

class StatView extends Backbone.View<QueryResultModel> {

    private $tableHead: JQuery
    private $tableBody: JQuery
    private $query: JQuery

    private tdTmpl = _.template('<td><%= d %></td>')
    private trTmpl = _.template('<tr><%= d %></tr>')

    constructor(options) {
        super(options);

        this.$tableHead = $('#table thead', this.$el);
        this.$tableBody = $('#table tbody', this.$el);
        this.$query = $('#query pre', this.$el);
        this.listenTo(this.model, "change", this.render);
    }

    render(): StatView {
        this.renderQuery();
        this.renderTable();

        this.$el.height(window.innerHeight - 50);

        return this;
    }

    private renderQuery(): void { this.$query.text(this.model.query); }

    // TODO refactor
    private renderTable(): void {
        var rows: string[] = [],
            row: string[] = [],
            fieldName: string,
            model: any;

        // Render table header.
        for (var i = 0; i < this.model.fields.length; i++) {
            rows.push(this.tdTmpl({d: this.model.fields[i]}));
        }
        this.$tableHead.html(this.trTmpl({d: rows.join('') }));

        // Render table rows.
        rows = [];
        for (var i = 0; i < this.model.results.length; i++) {
            model = this.model.results[i];
            row = [];
            for (var j = 0; j < this.model.fields.length; j++) {
                fieldName = this.model.fields[j];
                row.push(this.tdTmpl({d: model[fieldName]}));
            }
            rows.push(this.trTmpl({
                d: row.join('')
            }));
        }
        this.$tableBody.html(rows.join(''));
    }
}

class Route extends Backbone.Router {
    
    routes() {
        return {
            'overview': 'overview',
            'book/borrow': 'bookBorrow',
            'book/return': 'bookReturn',
            'book/query': 'bookQuery',
            'book/add': 'bookAdd',
            'reader/query': 'readerQuery',
            'reader/add': 'readerAdd',
            'help': 'help',
        };
    }

    help(): void {
        console.log('here');
    }

    overview(): void {
        console.log('overview');
    }
}

$(() => {
    var headerView = new HeaderView({el: $('#header')});

    new Route();
    Backbone.history.start();

    var q = new QueryResultModel(),
        statView = new StatView({el: $('#stats'), model: q});

    console.log(statView);

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
