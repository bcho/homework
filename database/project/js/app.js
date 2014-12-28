var html;
(function (html) {
    html.readerprofilenotfound = '<h3>没有找到读者： <%= no %></h3>';
    html.readerborrowlogrow = '<tr>    <td>        <a href="/#book/<%= no %>"><%= title %></a>    </td>    <td><%= no %></td>    <td><%= borrowed_at %></td>    <td><%= expire_at %></td>    <td><%= returned_at %></td></tr>';
    html.bookborrow = '                <div class="page-header">                    <h3>借出图书</h3>                </div>                <form action="#" role="form" class="book-borrow-return">                    <div class="row form-group">                        <div class="col-xs-8">                            <label for="book-borrow-return-user-name">读者姓名</label>                            <input name="book-borrow-return-user-name" type="text" class="form-control" placeholder="读者姓名" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-borrow-return-book-no">书籍编码</label>                            <input name="book-borrow-return-book-no" type="text" class="form-control" placeholder="书籍编码" />                        </div>                        <div class="col-xs-4">                            <label for="book-borrow-return-book-title">书籍名称</label>                            <input name="book-borrow-return-book-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                    </div>                    <div class="user-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">借出</a>                        </div>                    </div>                </form>';
    html.returnbook = '            <div class="page-header">                <h3>归还图书</h3>            </div>            <form action="#" role="form" class="book-borrow-return-form" data-user-no="<%= user.no %>">                <div class="row form-group">                    <div class="col-xs-8">                        <label for="book-borrow-return-user-name">读者姓名</label>                        <input name="book-borrow-return-user-name" type="text" class="form-control" placeholder="读者姓名" value="<%= user.name %>" readonly />                    </div>                </div>                <div class="row form-group">                    <div class="col-xs-8">                        <label for="book-borrow-return-book-no">书籍编码</label>                        <input name="book-borrow-return-book-no" type="text" class="form-control" placeholder="书籍编码" />                    </div>                </div>                <div class="book-borrow-return row">                    <div class="btn-group col-md-4" role="group">                        <a class="btn btn-success book-borrow-return-submit">归还</a>                    </div>                </div>            </form>            <div class="book-borrow-return-stats row">                <div class="col-md-12">                    <div class="page-header">                        <h3>持书情况</h3>                    </div>                    <table id="book-borrow-return-user-borrowing" class="table">                        <thead>                            <tr>                                <td>书籍名称</td>                                <td>书籍编号</td>                                <td>借阅时间</td>                                <td>应归还时间</td>                            </tr>                        </thead>                        <tbody>                        </tbody>                    </table>                </div>            </div>';
    html.bookquery = '                <div class="page-header">                    <h3>查询条件</h3>                </div>                <form action="#" role="form" class="book-query">                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-query-title">书籍名称</label>                            <input name="book-query-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-query-no">书籍编号</label>                            <input name="book-query-no" type="text" class="form-control" placeholder="书籍编号" />                        </div>                        <div class="col-xs-4">                            <label for="book-query-isbn">ISBN 编码</label>                            <input name="book-query-isbn" type="text" class="form-control" placeholder="ISBN 编码" />                        </div>                    </div>                    <div class="book-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success">查询</a>                        </div>                    </div>                </form>                <div class="book-query-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>查询结果</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>书籍 ISBN</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>';
    html.bookprofile = '                <div class="page-header">                    <h3><%= title %> 书籍详情</h3>                </div>                <form action="#" role="form" class="book-profile" data-book-no="<%= no %>">                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-profile-title">书籍名称</label>                            <input name="book-profile-title" type="text" class="form-control" placeholder="书籍名称" value="<%= title %>" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-profile-no">书籍编号</label>                            <input name="book-profile-no" type="text" class="form-control" placeholder="书籍编号" value="<%= no %>" />                        </div>                        <div class="col-xs-4">                            <label for="book-profile-isbn">ISBN 编码</label>                            <input name="book-profile-isbn" type="text" class="form-control" placeholder="ISBN 编码" value="<%= isbn %>" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-profile-borrow-stats">借阅次数</label>                            <input class="form-control" type="text" name="book-profile-borrow-stats" placeholder="借阅次数" value="<%= borrow_times %>" readonly>                        </div>                    </div>                    <div class="book-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-primary book-profile-update">更新图书</a>                            <a class="btn btn-success book-profile-borrow <%= can_borrow %>">借出图书</a>                            <a class="btn btn-danger book-profile-remove">删除图书</a>                        </div>                    </div>                </form>                <div class="book-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅记录</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>借阅读者</td>                                    <td>借阅日期</td>                                    <td>应该归还日期</td>                                    <td>归还日期</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>';
    html.readerquery = '                <div class="page-header">                    <h3>查询条件</h3>                </div>                <form action="#" role="form" class="user-query">                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="user-query-name">读者姓名</label>                            <input name="user-query-name" type="text" class="form-control" placeholder="读者姓名" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="user-query-no">读者学号</label>                            <input name="user-query-no" type="text" class="form-control" placeholder="读者学号" />                        </div>                        <div class="col-xs-4">                            <label for="user-query-faculty">读者学院</label>                            <input name="user-query-faculty" type="text" class="form-control" placeholder="读者学院" />                        </div>                    </div>                    <div class="user-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success">查询</a>                        </div>                    </div>                </form>                <div class="user-query-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>查询结果</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>读者姓名</td>                                    <td>读者学号</td>                                    <td>读者学院</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>';
    html.readerprofile = '                <div class="page-header">                    <h3>读者 <%= name %> 详情</h3>                </div>                <form action="#" role="form" class="user-profile" data-user-no="<%= no %>">                    <div class="row form-group">                        <div class="col-xs-4 user-profile-name">                            <label for="user-profile-name">姓名</label>                            <input name="user-profile-name" type="text" class="form-control" placeholder="姓名" value="<%= name %>" />                        </div>                        <div class="col-xs-4 user-profile-no">                            <label for="user-profile-no">学号</label>                            <input name="user-profile-no" type="text" class="form-control" placeholder="学号" value="<%= no %>" />                        </div>                        <div class="col-xs-4 user-profile-faculty">                            <label for="user-profile-faculty">学院</label>                            <input name="user-profile-faculty" type="text" class="form-control" placeholder="学院" value="<%= faculty %>" />                        </div>                    </div>                    <div class="user-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success user-profile-update">更新</a>                            <a class="btn btn-primary user-profile-return" <%= disable_return_book_btn %> href="/#book/return/<%= no %>">还书</a>                            <a class="btn btn-danger user-profile-remove" <%= disable_remove_btn %>>删除</a>                        </div>                    </div>                </form>                <div class="user-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>持书情况</h3>                        </div>                        <table class="table" id="user-profile-borrowing">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                    <td>归还时间</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅记录</h3>                        </div>                        <table class="table" id="user-profile-borrowed">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                    <td>归还时间</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>';
    html.bookborrowlogrow = '<tr>    <td><%= name %></td>    <td><%= borrowed_at %></td>    <td><%= expire_at %></td>    <td><%= returned_at %></td></tr>';
    html.bookborrowreturnuserborrowingrow = '<tr data-book-no="<%= no %>">    <td><%= title %></td>    <td><%= no %></td>    <td><%= borrowed_at %></td>    <td><%= expire_at %></td></tr>';
    html.overview = '                <div class="page-header">                    <h1>藏书情况</h1>                </div>                <div>                    <p>共有藏书 <%= books %> 册</p>                </div>                <div class="page-header">                    <h1>读者情况</h1>                </div>                <div>                    <p>共有登记读者 <%= users %> 名</p>                </div>';
    html.readeradd = '                <div class="page-header">                    <h3>读者详情</h3>                </div>                <form action="#" role="form" class="user-profile">                    <div class="row form-group">                        <div class="col-xs-4 user-profile-title">                            <label for="user-profile-title">姓名</label>                            <input name="user-profile-title" type="text" class="form-control" placeholder="张三" />                        </div>                        <div class="col-xs-4 user-profile-no">                            <label for="user-profile-no">学号</label>                            <input name="user-profile-no" type="text" class="form-control" placeholder="3112005816" />                        </div>                        <div class="col-xs-4 user-profile-faculty">                            <label for="user-profile-isbn">学院</label>                            <input type="text" class="form-control" placeholder="计算机学院" />                        </div>                    </div>                    <div class="user-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">新增</a>                        </div>                    </div>                </form>                <div class="user-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>持书情况</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>大学数学</td>                                    <td>TP 12345</td>                                    <td>2014/10/1</td>                                    <td>2014/11/5</td>                                </tr>                                <tr>                                    <td>大学英语</td>                                    <td>TP 67890</td>                                    <td>2014/11/12</td>                                    <td>2014/12/15</td>                                </tr>                            </tbody>                        </table>                    </div>                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅记录</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>归还时间</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>大学数学</td>                                    <td>TP 12345</td>                                    <td>2014/9/1</td>                                    <td>2014/10/1</td>                                </tr>                            </tbody>                        </table>                    </div>                </div>';
    html.bookprofilenotfound = '<h3>没有找到图书： <%= no %></h3>';
    html.readerresultrow = '<tr>    <td>        <a href="/#reader/<%= no %>"><%= name %></a>    </td>    <td><%= no %></td>    <td><%= faculty %></td></tr>';
    html.bookresultrow = '<tr>    <td>        <a href="/#book/<%= no %>"><%= title %></a>    </td>    <td><%= no %></td>    <td><%= isbn %></td></tr>';
    html.help = '<article class="help-article">    <h1>图书馆书籍管理系统使用帮助</h1>    <section id="article-overview" class="help-article-section">        <h3>系统概况</h3>        <p>write something...</p>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>借阅图书</h3>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>归还图书</h3>    </section>    <section id="article-enter-book" class="help-article-section">        <h3>登记图书</h3>    </section>    <section id="article-enter-user" class="help-article-section">        <h3>登记读者</h3>    </section>    <section id="article-book-profile" class="help-article-section">        <h3>图书详情</h3>    </section>    <section id="article-user-profile" class="help-article-section">        <h3>读者详情</h3>    </section></article>';
    html.bookadd = '                <div class="page-header">                    <h3>图书详情</h3>                </div>                <form action="#" role="form" class="book-profile">                    <div class="row form-group">                        <div class="col-xs-8 book-profile-title">                            <label for="book-profile-title">书籍名称</label>                            <input name="book-profile-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                        <div class="col-xs-4 book-profile-no">                            <label for="book-profile-no">书籍编码</label>                            <input name="book-profile-no" type="text" class="form-control" placeholder="书籍编码" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-6 book-profile-isbn">                            <label for="book-profile-isbn">ISBN 编码</label>                            <input type="text" class="form-control" placeholder="ISBN 编码" />                        </div>                    </div>                    <div class="book-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">借出</a>                            <a class="btn btn-success" href="#">归还</a>                            <a class="btn btn-success" href="#">新增</a>                        </div>                    </div>                </form>                <div class="book-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅情况</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                    <td>归还时间</td>                                    <td>借阅读者</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>2014/10/1</td>                                    <td>2014/11/5</td>                                    <td>2014/11/10</td>                                    <td>张三</td>                                </tr>                                <tr>                                    <td>2014/11/12</td>                                    <td>2014/12/15</td>                                    <td>2014/12/1</td>                                    <td>张三</td>                                </tr>                                <tr>                                    <td>2014/12/5</td>                                    <td>2015/1/5</td>                                    <td></td>                                    <td>张三</td>                                </tr>                            </tbody>                        </table>                    </div>                </div>';
})(html || (html = {}));
var sqlQuery;
(function (sqlQuery) {
    sqlQuery.createtable = 'PRAGMA foreign_keys = ON;create table book(    no string primary key,    title string,    isbn string unique,    category string,    description text,    created_at timestamp default (CURRENT_TIMESTAMP),    updated_at timestamp);create table user(    no string primary key,    name string,    gender string,    faculty string,    created_at timestamp default (CURRENT_TIMESTAMP),    updated_at timestamp);create table book_borrowing_log(    id integer primary key,    book_no string references book(no) on delete cascade on update cascade,    user_no string references user(no) on delete cascade on update cascade,    expire_at date,    returned_at date,    borrowed_at date default (CURRENT_DATE));';
    sqlQuery.initbookborrowinglog = 'insert into book_borrowing_log    (book_no, user_no, expire_at)values    ("E0094868", "3112005816", date("now", "+3 months")),    ("A1840127", "3112005816", date("now", "+3 months"));insert into book_borrowing_log    (book_no, user_no, expire_at, returned_at)values    ("A0836869", "3112005816", date("now", "+3 months"), date("now", "+1 months"));';
    sqlQuery.inituser = 'insert into user    (no, name, gender, faculty)values    ("3112005816", "张三", "男", "计算机学院"),    ("3112005817", "李四", "男", "计算机学院");';
    sqlQuery.initbook = 'insert into book    (no, title, isbn, category, description)values    ("E0094868", "A first course in database systems", "9787111247333", "", ""),    ("A0836869", "编译原理", "7302089795", "", ""),    ("A1840127", "数据库系统概论", "704007494X", "", "");';
})(sqlQuery || (sqlQuery = {}));
/// <reference path="type/sql.d.ts" />
/// <reference path="type/squel.d.ts" />
/// <reference path="type/jquery.d.ts" />
/// <reference path="type/underscore.d.ts" />
/// <reference path="type/backbone.d.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
/// <reference path="partials/html.ts" />
/// <reference path="partials/sqlQuery.ts" />
// ----------------------------------------------------------------------------
// Models & Collections
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
    QueryResultModel.prototype.getQuery = function () {
        return this.get('query');
    };
    QueryResultModel.prototype.getFields = function () {
        return this.get('fields');
    };
    QueryResultModel.prototype.getResults = function () {
        return this.get('results');
    };
    return QueryResultModel;
})(Backbone.Model);
var BookModel = (function (_super) {
    __extends(BookModel, _super);
    function BookModel() {
        _super.apply(this, arguments);
        this.idAttribute = 'no';
    }
    BookModel.prototype.defaults = function () {
        return {
            no: '',
            title: '',
            isbn: '',
            category: '',
            description: '',
            created_at: '',
            updated_at: ''
        };
    };
    return BookModel;
})(Backbone.Model);
var UserModel = (function (_super) {
    __extends(UserModel, _super);
    function UserModel() {
        _super.apply(this, arguments);
        this.idAttribute = 'no';
    }
    UserModel.prototype.defaults = function () {
        return {
            name: '',
            gender: '',
            faculty: '',
            created_at: '',
            updated_at: ''
        };
    };
    return UserModel;
})(Backbone.Model);
var BaseCollection = (function (_super) {
    __extends(BaseCollection, _super);
    function BaseCollection() {
        _super.apply(this, arguments);
    }
    BaseCollection.prototype.fetch = function (options) {
        options = options ? _.clone(options) : {};
        var rv = DB.prepare(this.table, 'select * from ' + this.table).execute();
        var method = options.reset ? 'reset' : 'set';
        this[method](rv, options);
        this.trigger('sync', this, rv, options);
    };
    return BaseCollection;
})(Backbone.Collection);
var BookCollection = (function (_super) {
    __extends(BookCollection, _super);
    function BookCollection() {
        _super.apply(this, arguments);
        this.table = 'book';
    }
    return BookCollection;
})(BaseCollection);
var UserCollection = (function (_super) {
    __extends(UserCollection, _super);
    function UserCollection() {
        _super.apply(this, arguments);
        this.table = 'user';
    }
    return UserCollection;
})(BaseCollection);
// ----------------------------------------------------------------------------
// DB proxy
// ----------------------------------------------------------------------------
var StatementProxy = (function () {
    function StatementProxy(table, db, queryResultModel, stmtString) {
        this.db = db;
        this.table = table;
        this.queryResultModel = queryResultModel;
        this.stmtString = stmtString;
        try {
            this.stmt = db.prepare(stmtString);
        }
        catch (e) {
            console.log(stmtString);
            throw e;
        }
    }
    StatementProxy.prototype.bind = function (params) {
        return this.stmt.bind(params);
    };
    StatementProxy.prototype.execute = function (params) {
        try {
            return this._execute(params);
        }
        catch (e) {
            console.log(this.stmtString);
            console.log(this.stmt);
            throw e;
        }
    };
    StatementProxy.prototype._execute = function (params) {
        var rv = [], columnNames = this.getTableColumns();
        this.bind(params);
        while (this.stmt.step()) {
            rv.push(this.stmt.getAsObject());
            columnNames = this.stmt.getColumnNames();
        }
        this.queryResultModel.set({
            query: this.stmtString,
            fields: columnNames,
            results: rv
        });
        return rv;
    };
    StatementProxy.prototype.getTableColumns = function () {
        var rv = this.db.exec('PRAGMA table_info("' + this.table + '")');
        if (rv.length < 1) {
            return [];
        }
        return _.map(rv[0].values, function (i) {
            return i[1];
        });
    };
    return StatementProxy;
})();
// TODO use interface to define db manager.
var DB = {
    db: new SQL.Database(),
    queryResult: new QueryResultModel(),
    run: function (stmt) {
        return this.db.run(stmt);
    },
    exec: function (stmt) {
        return this.db.exec(stmt);
    },
    prepare: function (table, stmt) {
        return new StatementProxy(table, this.db, this.queryResult, stmt);
    }
};
// ----------------------------------------------------------------------------
// Seeder
// ----------------------------------------------------------------------------
var Seeder = (function () {
    function Seeder(db) {
        this.db = db;
    }
    Seeder.prototype.run = function () {
        console.log('Seeding database...');
        this.seedTables();
        this.seedBooks();
        this.seedUsers();
        this.seedBookBorrowingLogs();
    };
    Seeder.prototype.seedTables = function () {
        this.db.exec(sqlQuery.createtable);
    };
    Seeder.prototype.seedBooks = function () {
        this.db.exec(sqlQuery.initbook);
    };
    Seeder.prototype.seedUsers = function () {
        this.db.exec(sqlQuery.inituser);
    };
    Seeder.prototype.seedBookBorrowingLogs = function () {
        this.db.exec(sqlQuery.initbookborrowinglog);
    };
    return Seeder;
})();
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
        return this.setActiviyView($(e.target.parentElement));
    };
    HeaderView.prototype.switchViewWithTabName = function (tabName) {
        // TODO unifiy views naming scheme.
        var $target = $('li[name=' + tabName + ']');
        if ($target) {
            this.setActiviyView($target);
        }
        return this;
    };
    HeaderView.prototype.setActiviyView = function ($target) {
        this.$navItems.removeClass('active');
        $target.addClass('active');
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
        q = this.queryTmpl({ d: this.model.getQuery() });
        this.$query.html(q);
    };
    // TODO refactor
    StatView.prototype.renderTable = function () {
        var rows = [], row = [], fieldName, fields = this.model.getFields(), results = this.model.getResults(), model;
        for (var i = 0; i < fields.length; i++) {
            rows.push(this.tdTmpl({ d: fields[i] }));
        }
        this.$tableHead.html(this.trTmpl({ d: rows.join('') }));
        // Render table rows.
        rows = [];
        for (var i = 0; i < results.length; i++) {
            model = results[i];
            row = [];
            for (var j = 0; j < fields.length; j++) {
                fieldName = fields[j];
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
var DashboardView = (function (_super) {
    __extends(DashboardView, _super);
    function DashboardView() {
        _super.apply(this, arguments);
        this.tmpl = _.template(html.overview);
    }
    DashboardView.prototype.render = function () {
        $(this.el).html(this.tmpl({
            books: this.queryBookCount(),
            users: this.queryUserCount()
        }));
        return this;
    };
    // FIXME should separate view & model/collection.
    DashboardView.prototype.queryUserCount = function () {
        var rv = DB.prepare('user', 'select count(*) as count from user').execute();
        return rv[0].count;
    };
    DashboardView.prototype.queryBookCount = function () {
        var rv = DB.prepare('book', 'select count(*) as count from book').execute();
        return rv[0].count;
    };
    return DashboardView;
})(Backbone.View);
var QueryView = (function (_super) {
    __extends(QueryView, _super);
    function QueryView() {
        _super.apply(this, arguments);
        this.table = '';
        this.emptyValue = '';
    }
    // Query fields.
    QueryView.prototype.fields = function () {
        return {};
    };
    QueryView.prototype.query = function () {
        var stmt = DB.prepare(this.table, this.generateQuery().toString());
        return stmt.execute();
    };
    QueryView.prototype.generateQuery = function () {
        var queryClauses = this.grabUserInput(), stmt = squel.select().from(this.table);
        for (var i = 0; i < queryClauses.length; i++) {
            stmt = stmt.where(queryClauses[i]);
        }
        return stmt;
    };
    QueryView.prototype.grabUserInput = function () {
        var _this = this;
        var definedFields = _.extend({}, this.fields()), queryFields = [], $form = $('form[role=form]', this.el);
        _.each(definedFields, function (q, fieldName) {
            var userInput = $('input[name=' + fieldName + ']', $form).val();
            if (!userInput || userInput === _this.emptyValue) {
                return;
            }
            queryFields.push(q({ value: userInput }));
        });
        return queryFields;
    };
    return QueryView;
})(Backbone.View);
var BookQueryView = (function (_super) {
    __extends(BookQueryView, _super);
    function BookQueryView(options) {
        _super.call(this, options);
        this.table = 'book';
        this.tmpl = html.bookquery;
        this.resultRowTmpl = _.template(html.bookresultrow);
        $(this.el).html(this.tmpl);
        this.$resultTable = $('.book-query-stats table', this.el);
    }
    BookQueryView.prototype.events = function () {
        return {
            'click .book-query-actions .btn-success': 'render'
        };
    };
    BookQueryView.prototype.fields = function () {
        return {
            'book-query-title': _.template('title like "%<%= value %>%"'),
            'book-query-no': _.template('no = "<%= value %>"'),
            'book-query-isbn': _.template('isbn = "<%= value %>"')
        };
    };
    BookQueryView.prototype.render = function () {
        var books = this.query();
        this.renderResultTable(books);
        return this;
    };
    BookQueryView.prototype.renderResultTable = function (books) {
        var $tbody = $('tbody', this.$resultTable);
        $tbody.html(_.map(books, this.resultRowTmpl).join(''));
    };
    return BookQueryView;
})(QueryView);
var BookProfileView = (function (_super) {
    __extends(BookProfileView, _super);
    function BookProfileView() {
        _super.apply(this, arguments);
        this.tmpl = _.template(html.bookprofile);
    }
    BookProfileView.prototype.events = function () {
        return {
            'click a.book-profile-update': 'updateProfile',
            'click a.book-profile-remove': 'removeProfile'
        };
    };
    BookProfileView.prototype.render = function (bookNo) {
        var book = this.query(bookNo);
        if (book) {
            this.renderProfile(book);
        }
        else {
            this.renderNotFound(bookNo);
        }
        return this;
    };
    BookProfileView.prototype.renderProfile = function (book) {
        var $el = $(this.el), rowTmpl = _.template(html.bookborrowlogrow), borrowLogs;
        borrowLogs = _.map(this.queryBorrowLogs(book.no), rowTmpl);
        book['borrow_times'] = borrowLogs.length;
        book['can_borrow'] = this.queryCanBorrow(book.no) ? '' : 'hide';
        $el.html(this.tmpl(book));
        $('.book-profile-stats tbody', $el).html(borrowLogs.join(''));
        this.delegateEvents();
    };
    BookProfileView.prototype.renderNotFound = function (bookNo) {
        $(this.el).html(_.template(html.bookprofilenotfound)({ no: bookNo }));
    };
    BookProfileView.prototype.query = function (bookNo) {
        var stmt = squel.select().from('book').where('no = ?', bookNo);
        var rv = DB.prepare('book', stmt.toString()).execute();
        if (rv.length < 1) {
            return null;
        }
        return rv[0];
    };
    BookProfileView.prototype.queryBorrowLogs = function (bookNo) {
        var stmt = squel.select().from('book_borrowing_log', 'log').where('log.book_no = ?', bookNo).left_join('user', null, 'user.no = log.user_no');
        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    };
    BookProfileView.prototype.queryCanBorrow = function (bookNo) {
        var stmt = squel.select().field('count(*)', 'not_returned').from('book_borrowing_log', 'log').where('log.book_no = ?', bookNo).where('log.returned_at is null');
        var rv = DB.prepare('book_borrowing_log', stmt.toString()).execute();
        return rv[0]['not_returned'] <= 0;
    };
    BookProfileView.prototype.updateProfile = function () {
        var $form = $('.book-profile', this.el), bookTitle = $('[name=book-profile-title]', $form).val(), bookNo = $('[name=book-profile-no]', $form).val(), bookIsbn = $('[name=book-profile-isbn]', $form).val(), originalBookNo = this.getOriginalBookNo();
        var stmt = squel.update().table('book').set('no', bookNo).set('isbn', bookIsbn).set('title', bookTitle).where('no = ?', originalBookNo);
        try {
            DB.exec(stmt.toString());
            alert('更新成功');
            this.render(bookNo);
        }
        catch (e) {
            console.log(e);
            alert('更新失败');
        }
        return true;
    };
    BookProfileView.prototype.removeProfile = function () {
        var bookNo = this.getOriginalBookNo();
        if (!this.queryCanBorrow(bookNo)) {
            alert('不能删除本书记录');
            return true;
        }
        var stmt = squel.delete().from('book').where('no = ?', bookNo);
        try {
            DB.exec(stmt.toString());
            alert('删除成功');
            location.href = '/#book/query';
        }
        catch (e) {
            console.log(e);
            alert('删除失败');
        }
        return true;
    };
    BookProfileView.prototype.getOriginalBookNo = function () {
        return $('.book-profile', this.el).data('book-no');
    };
    return BookProfileView;
})(Backbone.View);
var UserQueryView = (function (_super) {
    __extends(UserQueryView, _super);
    function UserQueryView(options) {
        _super.call(this, options);
        this.table = 'user';
        this.tmpl = html.readerquery;
        this.resultRowTmpl = _.template(html.readerresultrow);
        $(this.el).html(this.tmpl);
        this.$resultTable = $('.user-query-stats table', this.el);
    }
    UserQueryView.prototype.events = function () {
        return {
            'click .user-query-actions .btn-success': 'render'
        };
    };
    UserQueryView.prototype.fields = function () {
        return {
            'user-query-name': _.template('name like "%<%= value %>%"'),
            'user-query-no': _.template('no = "<%= value %>"'),
            'user-query-faculty': _.template('faculty like "%<%= faculty %>%"')
        };
    };
    UserQueryView.prototype.render = function () {
        var users = this.query();
        this.renderResultTable(users);
        return this;
    };
    UserQueryView.prototype.renderResultTable = function (users) {
        var $tbody = $('tbody', this.$resultTable);
        $tbody.html(_.map(users, this.resultRowTmpl).join(''));
    };
    return UserQueryView;
})(QueryView);
var UserProfileView = (function (_super) {
    __extends(UserProfileView, _super);
    function UserProfileView() {
        _super.apply(this, arguments);
        this.tmpl = _.template(html.readerprofile);
    }
    UserProfileView.prototype.events = function () {
        return {
            'click a.user-profile-update': 'updateProfile',
            'click a.user-profile-remove': 'removeProfile'
        };
    };
    UserProfileView.prototype.render = function (userNo) {
        var user = this.query(userNo);
        if (user) {
            this.renderProfile(user);
        }
        else {
            this.renderNotFound(userNo);
        }
        return this;
    };
    UserProfileView.prototype.renderProfile = function (user) {
        var $el = $(this.el), hasBorrowingBooks = this.queryHasBorrowingBooks(user.no);
        user['disable_return_book_btn'] = hasBorrowingBooks ? '' : 'disabled';
        user['disable_remove_btn'] = hasBorrowingBooks ? 'disabled' : '';
        $el.html(this.tmpl(user));
        this.renderBorrowingBooks(user);
        this.renderBorrowedBooks(user);
        this.delegateEvents();
    };
    UserProfileView.prototype.renderBorrowingBooks = function (user) {
        var $el = $('#user-profile-borrowing tbody', this.el), rowTmpl = _.template(html.readerborrowlogrow), books = this.queryBorrowingBooks(user.no);
        $el.html(_.map(books, rowTmpl).join(''));
    };
    UserProfileView.prototype.renderBorrowedBooks = function (user) {
        var $el = $('#user-profile-borrowed tbody', this.el), rowTmpl = _.template(html.readerborrowlogrow), books = this.queryBorrowedBooks(user.no);
        $el.html(_.map(books, rowTmpl).join(''));
    };
    UserProfileView.prototype.renderNotFound = function (userNo) {
        $(this.el).html(_.template(html.readerprofilenotfound)({ no: userNo }));
    };
    UserProfileView.prototype.query = function (userNo) {
        var stmt = squel.select().from('user').where('no = ?', userNo);
        var rv = DB.prepare('user', stmt.toString()).execute();
        if (rv.length < 1) {
            return null;
        }
        return rv[0];
    };
    UserProfileView.prototype.queryBorrowingBooks = function (userNo) {
        var stmt = squel.select().from('book').join('book_borrowing_log', 'log', 'log.book_no = book.no').where('log.user_no = ?', userNo).where('log.returned_at is null');
        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    };
    UserProfileView.prototype.queryBorrowedBooks = function (userNo) {
        var stmt = squel.select().from('book').join('book_borrowing_log', 'log', 'log.book_no = book.no').where('log.user_no = ?', userNo);
        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    };
    UserProfileView.prototype.queryCanDelete = function (userNo) {
        return (!this.queryHasBorrowingBooks(userNo));
    };
    UserProfileView.prototype.queryHasBorrowingBooks = function (userNo) {
        var stmt = squel.select().field('count(*)', 'not_returned').from('book_borrowing_log', 'log').where('log.user_no = ?', userNo).where('log.returned_at is null');
        var rv = DB.prepare('book_borrowing_log', stmt.toString()).execute();
        return rv[0]['not_returned'] > 0;
    };
    UserProfileView.prototype.updateProfile = function () {
        var $form = $('.user-profile', this.el), userName = $('[name=user-profile-name]', $form).val(), userNo = $('[name=user-profile-no]', $form).val(), userFaculty = $('[name=user-profile-faculty]', $form).val(), originalUserNo = this.getOriginalUserNo();
        var stmt = squel.update().table('user').set('no', userNo).set('name', userName).set('faculty', userFaculty).where('no = ?', originalUserNo);
        try {
            DB.exec(stmt.toString());
            alert('更新成功');
            this.render(userNo);
        }
        catch (e) {
            console.log(e);
            alert('更新失败');
        }
        return true;
    };
    UserProfileView.prototype.removeProfile = function () {
        var userNo = this.getOriginalUserNo(), stmt = squel.delete().from('user').where('no = ?', userNo);
        if (!this.queryCanDelete(userNo)) {
            alert('不能删除读者记录');
            return true;
        }
        try {
            DB.exec(stmt.toString());
            alert('删除成功');
            location.href = '/#reader/query';
        }
        catch (e) {
            console.log(e);
            alert('删除失败');
        }
        return true;
    };
    UserProfileView.prototype.getOriginalUserNo = function () {
        return $('.user-profile', this.el).data('user-no');
    };
    return UserProfileView;
})(Backbone.View);
var ReturnBookView = (function (_super) {
    __extends(ReturnBookView, _super);
    function ReturnBookView() {
        _super.apply(this, arguments);
        this.tmpl = _.template(html.returnbook);
    }
    ReturnBookView.prototype.events = function () {
        return {
            'click #book-borrow-return-user-borrowing tbody tr': 'fillForm',
            'click .book-borrow-return-submit': 'submit'
        };
    };
    ReturnBookView.prototype.fillForm = function (e) {
        var $el = $(e.target.parentElement), $field = $('input[name=book-borrow-return-book-no]', this.el), bookNo = $el.data('book-no');
        $field.val(bookNo);
        return true;
    };
    ReturnBookView.prototype.submit = function () {
        var userNo = $('.book-borrow-return-form', this.el).data('user-no'), bookNo = $('input[name=book-borrow-return-book-no]', this.el).val();
        if (!userNo || !bookNo) {
            return true;
        }
        var stmt = squel.update().set('returned_at = CURRENT_DATE').table('book_borrowing_log').where('returned_at is null').where('book_no = ?', bookNo).where('user_no = ?', userNo);
        try {
            console.log(stmt.toString());
            DB.exec(stmt.toString());
            alert('归还成功');
            this.render(userNo);
        }
        catch (e) {
            console.log(e);
            alert('归还失败');
        }
        return true;
    };
    ReturnBookView.prototype.render = function (userNo) {
        var user = this.queryUser(userNo);
        if (!user) {
            alert("没有找到读者记录：" + userNo);
            location.href = "/#overview";
            return;
        }
        this.$el.html(this.tmpl({
            user: user
        }));
        this.renderBorrowingBooks(user);
        this.delegateEvents();
    };
    ReturnBookView.prototype.renderBorrowingBooks = function (user) {
        var $el = $('#book-borrow-return-user-borrowing tbody', this.el), rowTmpl = _.template(html.bookborrowreturnuserborrowingrow), books = this.queryBorrowingBooks(user.no);
        $el.html(_.map(books, rowTmpl).join(''));
    };
    ReturnBookView.prototype.queryUser = function (userNo) {
        var stmt = squel.select().from('user').where('no = ?', userNo);
        var rv = DB.prepare('user', stmt.toString()).execute();
        return rv.length > 0 ? rv[0] : null;
    };
    ReturnBookView.prototype.queryBorrowingBooks = function (userNo) {
        var stmt = squel.select().from('book').join('book_borrowing_log', 'log', 'log.book_no = book.no').where('log.user_no = ?', userNo).where('log.returned_at is null');
        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    };
    return ReturnBookView;
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
        _super.call(this);
        this.formView = new FormView({ el: $('#form') });
        this.headerView = new HeaderView({ el: $('#header') });
        this.booksColl = new BookCollection();
        this.usersColl = new UserCollection();
        this.booksColl.fetch();
        this.usersColl.fetch();
    }
    Route.prototype.routes = function () {
        return {
            '': 'overview',
            'overview': 'overview',
            'book/borrow': 'bookBorrow',
            'book/return/:readerNo': 'bookReturn',
            'book/query': 'bookQuery',
            'book/add': 'bookAdd',
            'book/:no': 'bookProfile',
            'reader/query': 'readerQuery',
            'reader/add': 'readerAdd',
            'reader/:no': 'readerProfile',
            'help': 'help'
        };
    };
    Route.prototype.overview = function () {
        this.headerView.switchViewWithTabName('overview');
        (new DashboardView({ el: $('#form') })).render();
    };
    Route.prototype.bookBorrow = function () {
        this.formView.render(html.bookborrow);
        this.headerView.switchViewWithTabName('bookborrow');
    };
    Route.prototype.bookReturn = function (readerNo) {
        (new ReturnBookView({ el: $('#form') })).render(readerNo);
    };
    Route.prototype.bookQuery = function () {
        this.headerView.switchViewWithTabName('bookquery');
        (new BookQueryView({ el: $('#form') })).render();
    };
    Route.prototype.bookAdd = function () {
        this.formView.render(html.bookadd);
        this.headerView.switchViewWithTabName('bookadd');
    };
    Route.prototype.bookProfile = function (bookNo) {
        (new BookProfileView({ el: $('#form') })).render(bookNo);
    };
    Route.prototype.readerQuery = function () {
        this.headerView.switchViewWithTabName('readerquery');
        (new UserQueryView({ el: $('#form') })).render();
    };
    Route.prototype.readerAdd = function () {
        this.formView.render(html.readeradd);
        this.headerView.switchViewWithTabName('readeradd');
    };
    Route.prototype.readerProfile = function (userNo) {
        (new UserProfileView({ el: $('#form') })).render(userNo);
    };
    Route.prototype.help = function () {
        this.formView.render(html.help);
        this.headerView.switchViewWithTabName('help');
    };
    return Route;
})(Backbone.Router);
$(function () {
    new StatView({ el: $('#stats'), model: DB.queryResult });
    (new Seeder(DB)).run();
    new Route();
    Backbone.history.start();
});
