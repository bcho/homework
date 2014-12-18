/// <reference path="type/sql.d.ts" />
/// <reference path="type/jquery.d.ts" />
/// <reference path="type/underscore.d.ts" />
/// <reference path="type/backbone.d.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
// ----------------------------------------------------------------------------
// Models
// ----------------------------------------------------------------------------
var QueryResultModel = (function (_super) {
    __extends(QueryResultModel, _super);
    function QueryResultModel() {
        _super.apply(this, arguments);
    }
    QueryResultModel.prototype.defaults = function () {
        return {
            // Query statement.
            query: "",
            // Row fields.
            fields: [],
            // Query results.
            results: []
        };
    };
    Object.defineProperty(QueryResultModel.prototype, "query", {
        get: function () {
            return this.get('query');
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(QueryResultModel.prototype, "fields", {
        get: function () {
            return this.get('fields');
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(QueryResultModel.prototype, "results", {
        get: function () {
            return this.get('results');
        },
        enumerable: true,
        configurable: true
    });
    return QueryResultModel;
})(Backbone.Model);
// ----------------------------------------------------------------------------
// Views
// ----------------------------------------------------------------------------
var HeaderView = (function (_super) {
    __extends(HeaderView, _super);
    function HeaderView(options) {
        _super.call(this, options);
        this.$navItems = $('li[role="presentation"]', this.$el);
    }
    HeaderView.prototype.events = function () {
        return {
            "click li[role=presentation] a": "switchView"
        };
    };
    HeaderView.prototype.switchView = function (e) {
        this.$navItems.removeClass('active');
        $(e.target.parentElement).addClass('active');
        return this;
    };
    return HeaderView;
})(Backbone.View);
var StatView = (function (_super) {
    __extends(StatView, _super);
    function StatView(options) {
        _super.call(this, options);
        this.tdTmpl = _.template('<td><%= d %></td>');
        this.trTmpl = _.template('<tr><%= d %></tr>');
        this.queryTmpl = _.template('<pre><%= d %></pre>');
        this.$tableHead = $('#table thead', this.$el);
        this.$tableBody = $('#table tbody', this.$el);
        this.$query = $('#query .query', this.$el);
        this.listenTo(this.model, "change", this.render);
    }
    StatView.prototype.render = function () {
        this.renderQuery();
        this.renderTable();
        this.$el.height(window.innerHeight - 50);
        return this;
    };
    StatView.prototype.renderQuery = function () {
        var q;
        q = this.queryTmpl({ d: this.model.query });
        this.$query.html(q);
    };
    // TODO refactor
    StatView.prototype.renderTable = function () {
        var rows = [], row = [], fieldName, model;
        for (var i = 0; i < this.model.fields.length; i++) {
            rows.push(this.tdTmpl({ d: this.model.fields[i] }));
        }
        this.$tableHead.html(this.trTmpl({ d: rows.join('') }));
        // Render table rows.
        rows = [];
        for (var i = 0; i < this.model.results.length; i++) {
            model = this.model.results[i];
            row = [];
            for (var j = 0; j < this.model.fields.length; j++) {
                fieldName = this.model.fields[j];
                row.push(this.tdTmpl({ d: model[fieldName] }));
            }
            rows.push(this.trTmpl({
                d: row.join('')
            }));
        }
        this.$tableBody.html(rows.join(''));
    };
    return StatView;
})(Backbone.View);
var Route = (function (_super) {
    __extends(Route, _super);
    function Route() {
        _super.apply(this, arguments);
    }
    Route.prototype.routes = function () {
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
    };
    Route.prototype.help = function () {
        console.log('here');
    };
    Route.prototype.overview = function () {
        console.log('overview');
    };
    return Route;
})(Backbone.Router);
$(function () {
    var headerView = new HeaderView({ el: $('#header') });
    new Route();
    Backbone.history.start();
    var q = new QueryResultModel(), statView = new StatView({ el: $('#stats'), model: q });
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
