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
class StatementProxy {

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

        try {
            this.stmt = db.prepare(stmtString);
        } catch (e) {
            console.log(stmtString);

            throw e;
        }
    }

    bind(params: any): any {
        return this.stmt.bind(params);
    }

    execute(params?: any): any {
        try {
            return this._execute(params);
        } catch (e) {
            console.log(this.stmtString);
            console.log(this.stmt);

            throw e;
        }
    }

    protected _execute(params?: any): any {
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

    prepare(table: string, stmt: string): StatementProxy {
        return new StatementProxy(table, this.db, this.queryResult, stmt);
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
        this.seedViews();
        this.seedBooks();
        this.seedUsers();
        this.seedBookBorrowingLogs();
    }

    private seedTables(): void {
        this.db.exec(sqlQuery.createtable);
    }

    private seedViews(): void {
        this.db.exec(sqlQuery.createview);
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

var headerView = new HeaderView({el: $('#header')});

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
        headerView.switchViewWithTabName('overview');

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
        headerView.switchViewWithTabName('bookquery');
        this.renderResultTable(this.query());

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

        headerView.switchViewWithTabName('bookquery');

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

            this.undelegateEvents();
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

            this.undelegateEvents();
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
        headerView.switchViewWithTabName('readerquery');
        this.renderResultTable(this.query());

        return this;
    }

    protected renderResultTable(users: any[]): void {
        var $tbody = $('tbody', this.$resultTable);

        $tbody.html(_.map(users, this.resultRowTmpl).join(''));
    }
}

class UserProfileView extends Backbone.View<UserModel> {

    protected tmpl = _.template(html.readerprofile);

    events(): any {
        return {
            'click a.user-profile-update': 'updateProfile',
            'click a.user-profile-remove': 'removeProfile'
        };
    }

    render(userNo: string): UserProfileView {
        var user = this.query(userNo);

        headerView.switchViewWithTabName('readerquery');

        if (user) {
            this.renderProfile(user);
        } else {
            this.renderNotFound(userNo);
        }

        return this;
    }

    private renderProfile(user: any): void {
        var $el = $(this.el),
            hasBorrowingBooks = this.queryHasBorrowingBooks(user.no);

        user['disable_return_book_btn'] = hasBorrowingBooks ? '' : 'disabled';
        user['disable_remove_btn'] = hasBorrowingBooks ? 'disabled' : '';
        $el.html(this.tmpl(user));

        this.renderBorrowingBooks(user);
        this.renderBorrowedBooks(user);

        this.delegateEvents();
    }

    private renderBorrowingBooks(user: any): void {
        var $el = $('#user-profile-borrowing tbody', this.el),
            rowTmpl = _.template(html.readerborrowlogrow),
            books = this.queryBorrowingBooks(user.no);

        $el.html(_.map(books, rowTmpl).join(''));
    }

    private renderBorrowedBooks(user: any): void {
        var $el = $('#user-profile-borrowed tbody', this.el),
            rowTmpl = _.template(html.readerborrowlogrow),
            books = this.queryBorrowedBooks(user.no);

        $el.html(_.map(books, rowTmpl).join(''));
    }

    private renderNotFound(userNo: string): void {
        $(this.el).html(_.template(html.readerprofilenotfound)({no: userNo}));
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

    private queryBorrowingBooks(userNo: string): any[] {
        var stmt = squel.select()
            .from('book')
            .join('book_borrowing_log', 'log', 'log.book_no = book.no')
            .where('log.user_no = ?', userNo)
            .where('log.returned_at is null');

        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    }

    private queryBorrowedBooks(userNo: string): any[] {
        var stmt = squel.select()
            .from('book')
            .join('book_borrowing_log', 'log', 'log.book_no = book.no')
            .where('log.user_no = ?', userNo);

        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    }

    private queryCanDelete(userNo: string): boolean {
        return (! this.queryHasBorrowingBooks(userNo));
    }

    private queryHasBorrowingBooks(userNo: string): boolean {
        var stmt = squel.select()
            .field('count(*)', 'not_returned')
            .from('book_borrowing_log', 'log')
            .where('log.user_no = ?', userNo)
            .where('log.returned_at is null');

        var rv = DB.prepare('book_borrowing_log', stmt.toString()).execute();

        return rv[0]['not_returned'] > 0;
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

            this.undelegateEvents();
            this.render(userNo);
        } catch (e) {
            console.log(e);

            alert('更新失败');
        }

        return true;
    }

    private removeProfile(): boolean {
        var userNo = this.getOriginalUserNo(),
            stmt = squel.delete()
            .from('user')
            .where('no = ?', userNo);

        if (! this.queryCanDelete(userNo)) {
            alert('不能删除读者记录');

            return true;
        }

        try {
            DB.exec(stmt.toString());

            alert('删除成功');

            this.undelegateEvents();
            location.href = '/#reader/query';
        } catch (e) {
            console.log(e);

            alert('删除失败');
        }

        return true;
    }

    private getOriginalUserNo(): string {
        return $('.user-profile', this.el).data('user-no');
    }

}

class ReturnBookView extends Backbone.View<Backbone.Model> {

    $el: JQuery
    tmpl = _.template(html.returnbook);

    events(): any {
        return {
            'click #book-borrow-return-user-borrowing tbody tr': 'fillForm',
            'click .book-borrow-return-submit': 'submit'
        };
    }

    fillForm(e: any): boolean {
        var $el = $(e.target.parentElement),
            $field = $('input[name=book-borrow-return-book-no]', this.el),
            bookNo = $el.data('book-no');

        $field.val(bookNo);

        return true;
    }

    submit(): boolean {
        var userNo = $('.book-borrow-return-form', this.el).data('user-no'),
            bookNo = $('input[name=book-borrow-return-book-no]', this.el).val();

        if (! userNo || ! bookNo) {
            alert('请填写书籍编号');

            return true;
        }

        var stmt = squel
            .update()
            .set('returned_at = CURRENT_DATE')
            .table('book_borrowing_log')
            .where('returned_at is null')
            .where('book_no = ?', bookNo)
            .where('user_no = ?', userNo);

        try {
            DB.exec(stmt.toString());
            alert('归还成功');

            this.render(userNo);
        } catch (e) {
            console.log(e);

            alert('归还失败');
        }

        return true;
    }

    render(userNo: string): ReturnBookView {
        var user = this.queryUser(userNo);

        headerView.render(html.readerquery);

        if (! user) {
            alert("没有找到读者记录：" + userNo);

            location.href = "/#overview";

            return;
        }

        this.$el.html(this.tmpl({
            user: user
        }));

        this.renderBorrowingBooks(user);

        this.delegateEvents();

        return this;
    }

    private renderBorrowingBooks(user: any): void {
        var $el = $('#book-borrow-return-user-borrowing tbody', this.el),
            rowTmpl = _.template(html.bookborrowreturnuserborrowingrow),
            books = this.queryBorrowingBooks(user.no);

        $el.html(_.map(books, rowTmpl).join(''));
    }

    private queryUser(userNo): any {
        var stmt = squel
            .select()
            .from('user')
            .where('no = ?', userNo);

        var rv = DB.prepare('user', stmt.toString()).execute();

        return rv.length > 0 ? rv[0] : null;
    }

    private queryBorrowingBooks(userNo: string): any[] {
        var stmt = squel.select()
            .from('book')
            .join('book_borrowing_log', 'log', 'log.book_no = book.no')
            .where('log.user_no = ?', userNo)
            .where('log.returned_at is null');

        return DB.prepare('book_borrowing_log', stmt.toString()).execute();
    }

}

class AddBookView extends Backbone.View<Backbone.Model> {

    tmpl = _.template(html.bookadd);

    events(): any {
        return {
            'click .btn-submit': 'submit'
        }
    }

    render(): AddBookView {
        headerView.switchViewWithTabName('bookadd');

        $(this.el).html(this.tmpl);

        return this;
    }

    submit(e: any): boolean {
        var $form = $('.book-profile', this.el),
            bookTitle = $('[name=book-profile-title]', $form).val(),
            bookNo = $('[name=book-profile-no]', $form).val(),
            bookISBN = $('[name=book-profile-isbn]', $form).val();
        
        if (!bookTitle || !bookNo || !bookISBN) {
            alert("书籍信息有误");
            return true;
        }

        var stmt = squel
            .insert()
            .into('book')
            .set('title', bookTitle)
            .set('no', bookNo)
            .set('isbn', bookISBN);

        try {
            DB.exec(stmt.toString());
            alert('创建成功');

            this.undelegateEvents();
            location.href = '/#book/' + bookNo;
        } catch (e) {
            console.log(e);

            alert('创建失败');
        }
        
        return true;
    }
}

class AddUserView extends Backbone.View<Backbone.Model> {

    tmpl = _.template(html.readeradd);

    events(): any {
        return {
            'click .btn-submit': 'submit'
        }
    }

    render(): AddBookView {
        headerView.switchViewWithTabName('readeradd');

        $(this.el).html(this.tmpl);

        return this;
    }

    submit(e: any): boolean {
        var $form = $('.user-profile', this.el),
            userName = $('[name=user-profile-name]', $form).val(),
            userNo = $('[name=user-profile-no]', $form).val(),
            userFaculty = $('[name=user-profile-faculty]', $form).val();
        
        if (!userName || !userNo || !userFaculty) {
            alert("读者信息有误");
            return true;
        }

        var stmt = squel
            .insert()
            .into('user')
            .set('name', userName)
            .set('no', userNo)
            .set('faculty', userFaculty);

        try {
            DB.exec(stmt.toString());
            alert('创建成功');

            this.undelegateEvents();
            location.href = '/#reader/' + userNo;
        } catch (e) {
            console.log(e);

            alert('创建失败');
        }
        
        return true;
    }

}

class BorrowBookView extends Backbone.View<Backbone.Model> {

    $el: JQuery;
    tmpl = _.template(html.bookborrow);

    events(): any {
        return {
            'click .book-borrow-return-submit': 'submit',
            'click #book-borrow-return-users tbody tr': 'fillForm'
        };
    }

    submit(e: any): boolean {
        var bookNo = $('.book-borrow-return', this.el).data('book-no'),
            userNo = $('[name=book-borrow-return-user-no]', this.el).val();

        if (! bookNo || ! userNo) {
            alert('请填写读者学号');

            return true;
        }

        var stmt = _.template(sqlQuery.borrowbook)({
            userNo: userNo,
            bookNo: bookNo
        });

        try {
            DB.exec(stmt);

            alert('借出成功');

            this.undelegateEvents();
            location.href = '/#book/' + bookNo;
        } catch (e) {
            console.log(e);

            alert('借出失败');
        }

        return true;
    }

    fillForm(e: any): boolean {
        var $el = $(e.target.parentElement),
            $field = $('[name=book-borrow-return-user-no]', this.el),
            userNo = $el.data('user-no');

        $field.val(userNo);

        return true;
    }

    render(bookNo: string): BorrowBookView {
        var book = this.queryBook(bookNo);

        headerView.switchViewWithTabName('bookquery');

        if (! book) {
            alert("没有找到图书：" + bookNo);

            location.href = "/#overview";

            return;
        }

        if (! this.queryBookCanBorrow(bookNo)) {
            alert("图书" + bookNo + "已被借出");

            location.href = "/#overview";

            return;
        }

        this.$el.html(this.tmpl({
            book: book
        }));

        this.renderUsers();

        this.delegateEvents();

        return this;
    }

    private renderUsers(): void {
        var $el = $('#book-borrow-return-users tbody', this.el),
            rowTmpl = _.template(html.bookborrowuserrow),
            users = this.queryUsers();

        $el.html(_.map(users, rowTmpl).join(''));
    }

    private queryBook(bookNo: string): any {
        var stmt = squel
            .select()
            .from('book')
            .where('no = ?', bookNo);

        var rv = DB.prepare('book', stmt.toString()).execute();

        return rv.length > 0 ? rv[0]: null;
    }

    private queryBookCanBorrow(bookNo: string): boolean {
        var stmt = squel.select()
            .field('count(*)', 'not_returned')
            .from('book_borrowing_log', 'log')
            .where('log.book_no = ?', bookNo)
            .where('log.returned_at is null');

        var rv = DB.prepare('book_borrowing_log', stmt.toString()).execute();

        return rv[0]['not_returned'] <= 0;
    }

    private queryUsers(): any {
        var stmt = squel
            .select()
            .from('user');

        var rv = DB.prepare('user', stmt.toString()).execute();

        return rv;
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
    private prevView;

    private booksColl: BookCollection
    private usersColl: UserCollection

    constructor() {
        super()

        this.formView = new FormView({el: $('#form')});

        this.booksColl = new BookCollection();
        this.usersColl = new UserCollection();

        this.booksColl.fetch();
        this.usersColl.fetch();

        this.prevView = null;
    }
    
    routes() {
        return {
            '': 'overview',
            'overview': 'overview',
            'book/:no/borrow': 'bookBorrow',
            'book/return/:readerNo': 'bookReturn',
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
        this.cleanUpView();
        this.prevView = (new DashboardView({el: $('#form')})).render();
    }

    bookBorrow(bookNo): void {
        this.cleanUpView();
        this.prevView = (new BorrowBookView({el: $('#form')})).render(bookNo);
    }

    bookReturn(readerNo): void {
        this.cleanUpView();
        this.prevView = (new ReturnBookView({el: $('#form')})).render(readerNo);
    }

    bookQuery(): void {
        this.cleanUpView();
        this.prevView = (new BookQueryView({el: $('#form')})).render();
    }

    bookAdd(): void {
        this.cleanUpView();
        this.prevView = (new AddBookView({el: $('#form')})).render();
    }

    bookProfile(bookNo): void {
        this.cleanUpView();
        this.prevView = (new BookProfileView({el: $('#form')})).render(bookNo);
    }

    readerQuery(): void {
        this.cleanUpView();
        this.prevView = (new UserQueryView({el: $('#form')})).render();
    }

    readerAdd(): void {
        this.cleanUpView();
        this.prevView = (new AddUserView({el: $('#form')})).render();
    }

    readerProfile(userNo): void {
        this.cleanUpView();
        this.prevView = (new UserProfileView({el: $('#form')})).render(userNo);
    }

    help(): void {
        this.prevView = this.formView.render(html.help);
        headerView.switchViewWithTabName('help');
    }

    private cleanUpView(): void {
        if (this.prevView) {
            this.prevView.undelegateEvents();
        }
    }

}

$(() => {
    new StatView({el: $('#stats'), model: DB.queryResult});
    (new Seeder(DB)).run();

    new Route();
    Backbone.history.start();
});
