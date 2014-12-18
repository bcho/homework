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
var FormView = (function (_super) {
    __extends(FormView, _super);
    function FormView() {
        _super.apply(this, arguments);
    }
    FormView.prototype.render = function (content) {
        this.$el.html(content);
        return this;
    };
    return FormView;
})(Backbone.View);
// ----------------------------------------------------------------------------
// Route
// ----------------------------------------------------------------------------
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
        var formView = new FormView({ $el: $('#form') });
        formView.render('ok');
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
var html;
(function (html) {
    html.help = '<article class="help-article">    <h1>图书馆书籍管理系统使用帮助</h1>    <section id="article-overview" class="help-article-section">        <h3>系统概况</h3>        <p>write something...</p>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>借阅图书</h3>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>归还图书</h3>    </section>    <section id="article-enter-book" class="help-article-section">        <h3>登记图书</h3>    </section>    <section id="article-enter-user" class="help-article-section">        <h3>登记读者</h3>    </section>    <section id="article-book-profile" class="help-article-section">        <h3>图书详情</h3>    </section>    <section id="article-user-profile" class="help-article-section">        <h3>读者详情</h3>    </section></article>';
})(html || (html = {}));
