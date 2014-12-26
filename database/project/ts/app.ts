/// <reference path="type/sql.d.ts" />
/// <reference path="type/squel.d.ts" />
/// <reference path="type/jquery.d.ts" />
/// <reference path="type/underscore.d.ts" />
/// <reference path="type/backbone.d.ts" />

/// <reference path="partials/html.ts" />
/// <reference path="partials/sqlQuery.ts" />

// ----------------------------------------------------------------------------
// Models & Collections
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

class BookModel extends Backbone.Model {

    idAttribute = 'no'
    
    defaults() {
        return {
            no: '',
            title: '',
            isbn: '',
            category: '',
            description: '',
            created_at: '',
            updated_at: ''
        };
    }
}

class UserModel extends Backbone.Model {

    idAttribute = 'no'

    defaults() {
        return {
            name: '',
            gender: '',
            faculty: '',
            created_at: '',
            updated_at: ''
        };
    }
}

class BaseCollection<TModel extends Backbone.Model> extends
    Backbone.Collection<Backbone.Model>
{

    table: string;

    fetch(options?: Backbone.CollectionFetchOptions): any {
        options = options ? _.clone(options) : {};

        var rv = DB.prepare(this.table, 'select * from ' + this.table).execute();
        var method = options.reset ? 'reset' : 'set';
        this[method](rv, options);

        this.trigger('sync', this, rv, options);
    }

}

class BookCollection extends BaseCollection<BookModel> {

    table = 'book';

}

class UserCollection extends BaseCollection<UserModel> {

    table = 'user'

}

// ----------------------------------------------------------------------------
// DB proxy
// ----------------------------------------------------------------------------
class StatmentProxy {

    private db
    private table
    private queryResultModel
    private stmtString
    private stmt
    
    constructor(table: string, db, queryResultModel: QueryResultModel,
                stmtString: string
    ) {
        this.db = db;
        this.table = table;
        this.queryResultModel = queryResultModel;
        this.stmtString = stmtString;
        this.stmt = db.prepare(stmtString);
    }

    bind(params: any): any {
        return this.stmt.bind(params);
    }

    execute(params?: any): any {
        var rv: any[] = [],
            columnNames = this.getTableColumns();

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
    }

    private getTableColumns(): string[] {
        var rv = this.db.exec('PRAGMA table_info("' + this.table + '")');

        if (rv.length < 1) {
            return [];
        }

        return _.map(rv[0].values, (i) => { return i[1]; });
    }
}

// TODO use interface to define db manager.
var DB = {
    db: new SQL.Database(),
    queryResult: new QueryResultModel(),

    run(stmt: string): any {
        return this.db.run(stmt);
    },

    exec(stmt: string): any {
        return this.db.exec(stmt);
    },

    prepare(table: string, stmt: string): StatmentProxy {
        return new StatmentProxy(table, this.db, this.queryResult, stmt);
    }
};

// ----------------------------------------------------------------------------
// Seeder
// ----------------------------------------------------------------------------
class Seeder {

    constructor(private db: any) {}

    run(): void {
        console.log('Seeding database...');
        this.seedTables();
        this.seedBooks();
        this.seedUsers();
        this.seedBookBorrowingLogs();
    }

    private seedTables(): void {
        this.db.exec(sqlQuery.createtable);
    }

    private seedBooks(): void {
        this.db.exec(sqlQuery.initbook);
    }

    private seedUsers(): void {
        this.db.exec(sqlQuery.inituser);
    }

    private seedBookBorrowingLogs(): void {
        this.db.exec(sqlQuery.initbookborrowinglog);
    }
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

class DashboardView extends Backbone.View<Backbone.Model> {

    private tmpl = _.template(html.overview)

    render(): DashboardView {
        $(this.el).html(this.tmpl({
            books: this.queryBookCount(),
            users: this.queryUserCount()
        }));

        return this;
    }

    // FIXME should separate view & model/collection.
    private queryUserCount(): number {
        var rv = DB.prepare('user', 'select count(*) as count from user').execute();

        return rv[0].count;
    }

    private queryBookCount(): number {
        var rv = DB.prepare('book', 'select count(*) as count from book').execute();

        return rv[0].count;
    }
}

class QueryView<TModel extends Backbone.Model> extends
    Backbone.View<Backbone.Model>
{
    protected table = ''
    protected emptyValue = ''

    // Query fields.
    protected fields(): any {
        return {};
    }

    protected query(): any[] {
        var stmt = DB.prepare(this.table, this.generateQuery().toString());

        return stmt.execute();
    }

    protected generateQuery(): any {
        var queryClauses: string[] = this.grabUserInput(),
            stmt = squel.select().from(this.table);
        
        for (var i = 0; i < queryClauses.length; i++) {
            stmt = stmt.where(queryClauses[i]);
        }

        return stmt;
    }

    protected grabUserInput(): string[] {
        var definedFields = _.extend({}, this.fields()),
            queryFields: string[] = [],
            $form = $('form[role=form]', this.el);

        _.each(definedFields, (q: (...data: any[]) => string, fieldName) => {
            var userInput = $('input[name=' + fieldName + ']', $form).val();

            if (! userInput || userInput === this.emptyValue) {
                return;
            }

            queryFields.push(q({ value: userInput }));
        });

        return queryFields;
    }
}

class BookQueryView extends QueryView<BookModel> {

    protected table = 'book';
    private tmpl = html.bookquery
    private $resultTable: JQuery
    private resultRowTmpl = _.template(html.bookresultrow)

    constructor(options?: any) {
        super(options);

        $(this.el).html(this.tmpl);
        this.$resultTable = $('.book-query-stats table', this.el);
    }

    events() {
        return {
            'click .book-query-actions .btn-success': 'render'
        };
    }

    protected fields() {
        return {
            'book-query-title': _.template('title like "%<%= value %>%"'),
            'book-query-no': _.template('no = "<%= value %>"'),
            'book-query-isbn': _.template('isbn = "<%= value %>"')
        }; 
    }

    render(): BookQueryView {
        var books = this.query();

        this.renderResultTable(books);

        return this;
    }

    protected renderResultTable(books: any[]): void {
        var $tbody = $('tbody', this.$resultTable);

        $tbody.html(_.map(books, this.resultRowTmpl).join(''));
    }
}

class BookProfileView extends Backbone.View<BookModel> {

    protected tmpl = _.template(html.bookprofile);

    events(): any {
        return {
            'click a.book-profile-update': 'updateProfile',
            'click a.book-profile-remove': 'removeProfile'
        };
    }

    render(bookNo: string): BookProfileView {
        var book = this.query(bookNo);

        if (book) {
            this.renderProfile(book);
        } else {
            this.renderNotFound(bookNo);
        }

        return this;
    }

    private renderProfile(book: any): void {
        var $el = $(this.el),
            rowTmpl = _.template(html.bookborrowlogrow),
            borrowLogs: string[];

        borrowLogs = _.map(this.queryBorrowLogs(book.no), rowTmpl);

        book['borrow_times'] = borrowLogs.length;
        book['can_borrow'] = this.queryCanBorrow(book.no) ? '' : 'hide';

        $el.html(this.tmpl(book));
        $('.book-profile-stats tbody', $el).html(borrowLogs.join(''));

        this.delegateEvents();
    }

    private renderNotFound(bookNo: string): void {
        $(this.el).html(_.template(html.bookprofilenotfound)({no: bookNo}));
    }

    private query(bookNo: string): any {
        var stmt = squel.select().from('book')
                .where('no = ?',  bookNo);

        var rv = DB.prepare('book', stmt.toString()).execute();
        if (rv.length < 1) {
            return null;
        }

        return rv[0];
    }

    private queryBorrowLogs(bookNo: string): any {
        var stmt = squel.select()
            .from('book_borrowing_log', 'log')
            .where('log.book_no = ?', bookNo)
            .left_join('user', null, 'user.no = log.user_no');

        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    }

    private queryCanBorrow(bookNo: string): boolean {
        var stmt = squel.select()
            .field('count(*)', 'not_returned')
            .from('book_borrowing_log', 'log')
            .where('log.book_no = ?', bookNo)
            .where('log.returned_at is null');

        var rv = DB.prepare('book_borrowing_log', stmt.toString()).execute();

        return rv[0]['not_returned'] <= 0;
    }

    private updateProfile(): boolean {
        var $form = $('.book-profile', this.el),
            bookTitle = $('[name=book-profile-title]', $form).val(),
            bookNo = $('[name=book-profile-no]', $form).val(),
            bookIsbn = $('[name=book-profile-isbn]', $form).val(),
            originalBookNo = this.getOriginalBookNo();

        var stmt = squel.update()
            .table('book')
            .set('no', bookNo)
            .set('isbn', bookIsbn)
            .set('title', bookTitle)
            .where('no = ?', originalBookNo);

        try {
            DB.exec(stmt.toString());
            alert('更新成功');

            this.render(bookNo);
        } catch (e) {
            console.log(e);

            alert('更新失败');
        }

        return true;
    }

    private removeProfile(): boolean {
        var bookNo = this.getOriginalBookNo();

        if (! this.queryCanBorrow(bookNo)) {
            alert('不能删除本书记录');

            return true;
        }

        var stmt = squel.delete()
            .from('book')
            .where('no = ?', bookNo);

        try {
            DB.exec(stmt.toString());
            alert('删除成功');
            location.href = '/#book/query';
        } catch (e) {
            console.log(e);

            alert('删除失败');
        }

        return true;
    }

    private getOriginalBookNo(): string {
        return $('.book-profile', this.el).data('book-no');
    }

}

class UserQueryView extends QueryView<UserModel> {

    protected table = 'user';
    private tmpl = html.readerquery
    private $resultTable: JQuery
    private resultRowTmpl = _.template(html.readerresultrow)

    constructor(options?: any) {
        super(options);

        $(this.el).html(this.tmpl);
        this.$resultTable = $('.user-query-stats table', this.el);
    }

    events() {
        return {
            'click .user-query-actions .btn-success': 'render'
        };
    }

    protected fields() {
        return {
            'user-query-name': _.template('name like "%<%= value %>%"'),
            'user-query-no': _.template('no = "<%= value %>"'),
            'user-query-faculty': _.template('faculty like "%<%= faculty %>%"')
        };
    }

    render(): UserQueryView {
        var users = this.query();

        this.renderResultTable(users);

        return this;
    }

    protected renderResultTable(users: any[]): void {
        var $tbody = $('tbody', this.$resultTable);

        $tbody.html(_.map(users, this.resultRowTmpl).join(''));
    }
}

class UserProfileView extends Backbone.View<UserModel> {

    protected tmpl = _.template(html.userprofile);

    events(): any {
        return {
            'click a.user-profile-update': 'updateProfile',
            'click a.user-profile-remove': 'removeProfile'
        };
    }

    render(userNo: string): UserProfileView {
        var user = this.query(userNo);

        if (user) {
            this.renderProfile(user);
        } else {
            this.renderNotFound(userNo);
        }

        return this;
    }

    private renderProfile(user: any): void {
        var $el = $(this.el);

        $el.html(this.tmpl(user));

        this.delegateEvents();
    }

    private renderNotFound(userNo: string): void {
        $(this.el).html(_.template(html.userprofilenotfound)({no: userNo}));
    }

    private query(userNo: string): any {
        var stmt = squel.select().from('user')
                .where('no = ?',  userNo);

        var rv = DB.prepare('user', stmt.toString()).execute();
        if (rv.length < 1) {
            return null;
        }

        return rv[0];
    }

    private updateProfile(): boolean {
        var $form = $('.user-profile', this.el),
            userName = $('[name=user-profile-name]', $form).val(),
            userNo = $('[name=user-profile-no]', $form).val(),
            userFaculty = $('[name=user-profile-faculty]', $form).val(),
            originalUserNo = this.getOriginalUserNo();

        var stmt = squel.update()
            .table('user')
            .set('no', userNo)
            .set('name', userName)
            .set('faculty', userFaculty)
            .where('no = ?', originalUserNo);

        try {
            DB.exec(stmt.toString());
            alert('更新成功');

            this.render(userNo);
        } catch (e) {
            console.log(e);

            alert('更新失败');
        }

        return true;
    }

    private removeProfile(): boolean {
        return true;
    }

    private getOriginalUserNo(): string {
        return $('.user-profile', this.el).data('user-no');
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

    private booksColl: BookCollection
    private usersColl: UserCollection

    constructor() {
        super()

        this.formView = new FormView({el: $('#form')});
        this.headerView = new HeaderView({el: $('#header')});

        this.booksColl = new BookCollection();
        this.usersColl = new UserCollection();

        this.booksColl.fetch();
        this.usersColl.fetch();
    }
    
    routes() {
        return {
            '': 'overview',
            'overview': 'overview',
            'book/borrow': 'bookBorrow',
            'book/return': 'bookReturn',
            'book/query': 'bookQuery',
            'book/add': 'bookAdd',
            'book/:no': 'bookProfile',
            'reader/query': 'readerQuery',
            'reader/add': 'readerAdd',
            'reader/:no': 'readerProfile',
            'help': 'help'
        };
    }

    overview(): void {
        this.headerView.switchViewWithTabName('overview');

        (new DashboardView({el: $('#form')})).render();
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
        this.headerView.switchViewWithTabName('bookquery');

        (new BookQueryView({el: $('#form')})).render();
    }

    bookAdd(): void {
        this.formView.render(html.bookadd);
        this.headerView.switchViewWithTabName('bookadd');
    }

    bookProfile(bookNo): void {
        (new BookProfileView({el: $('#form')})).render(bookNo);
    }

    readerQuery(): void {
        this.headerView.switchViewWithTabName('readerquery');

        (new UserQueryView({el: $('#form')})).render();
    }

    readerAdd(): void {
        this.formView.render(html.readeradd);
        this.headerView.switchViewWithTabName('readeradd');
    }

    readerProfile(userNo): void {
        (new UserProfileView({el: $('#form')})).render(userNo);
    }

    help(): void {
        this.formView.render(html.help);
        this.headerView.switchViewWithTabName('help');
    }

}

$(() => {
    new StatView({el: $('#stats'), model: DB.queryResult});
    (new Seeder(DB)).run();

    new Route();
    Backbone.history.start();
});
