module html {
 export var bookborrow = '                <div class="page-header">                    <h3>借出图书</h3>                </div>                <form action="#" role="form" class="book-borrow-return">                    <div class="row form-group">                        <div class="col-xs-8">                            <label for="book-borrow-return-user-name">读者姓名</label>                            <input name="book-borrow-return-user-name" type="text" class="form-control" placeholder="读者姓名" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-borrow-return-book-no">书籍编码</label>                            <input name="book-borrow-return-book-no" type="text" class="form-control" placeholder="书籍编码" />                        </div>                        <div class="col-xs-4">                            <label for="book-borrow-return-book-title">书籍名称</label>                            <input name="book-borrow-return-book-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                    </div>                    <div class="user-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">借出</a>                        </div>                    </div>                </form>'
export var bookquery = '                <div class="page-header">                    <h3>查询条件</h3>                </div>                <form action="#" role="form" class="book-query">                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-query-title">书籍名称</label>                            <input name="book-query-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-query-no">书籍编号</label>                            <input name="book-query-no" type="text" class="form-control" placeholder="书籍编号" />                        </div>                        <div class="col-xs-4">                            <label for="book-query-isbn">ISBN 编码</label>                            <input name="book-query-isbn" type="text" class="form-control" placeholder="ISBN 编码" />                        </div>                    </div>                    <div class="book-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success">查询</a>                        </div>                    </div>                </form>                <div class="book-query-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>查询结果</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>书籍 ISBN</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>'
export var readerquery = '                <div class="page-header">                    <h3>查询条件</h3>                </div>                <form action="#" role="form" class="user-query">                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="user-query-name">读者姓名</label>                            <input name="user-query-name" type="text" class="form-control" placeholder="读者姓名" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="user-query-no">读者学号</label>                            <input name="user-query-no" type="text" class="form-control" placeholder="读者学号" />                        </div>                        <div class="col-xs-4">                            <label for="user-query-faculty">读者学院</label>                            <input name="user-query-faculty" type="text" class="form-control" placeholder="读者学院" />                        </div>                    </div>                    <div class="user-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">查询</a>                        </div>                    </div>                </form>                <div class="user-query-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>查询结果</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>读者姓名</td>                                    <td>读者学号</td>                                    <td>读者学院</td>                                </tr>                            </thead>                            <tbody>                            </tbody>                        </table>                    </div>                </div>'
export var overview = '                <div class="page-header">                    <h1>藏书情况</h1>                </div>                <div>                    <p>共有藏书 <%= books %> 册</p>                </div>                <div class="page-header">                    <h1>读者情况</h1>                </div>                <div>                    <p>共有登记读者 <%= users %> 名</p>                </div>'
export var bookreturn = '                <div class="page-header">                    <h3>归还图书</h3>                </div>                <form action="#" role="form" class="book-borrow-return">                    <div class="row form-group">                        <div class="col-xs-8">                            <label for="book-borrow-return-user-name">读者姓名</label>                            <input name="book-borrow-return-user-name" type="text" class="form-control" placeholder="读者姓名" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-4">                            <label for="book-borrow-return-book-no">书籍编码</label>                            <input name="book-borrow-return-book-no" type="text" class="form-control" placeholder="书籍编码" />                        </div>                        <div class="col-xs-4">                            <label for="book-borrow-return-book-title">书籍名称</label>                            <input name="book-borrow-return-book-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                    </div>                    <div class="user-query-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">归还</a>                        </div>                    </div>                </form>'
export var readeradd = '                <div class="page-header">                    <h3>读者详情</h3>                </div>                <form action="#" role="form" class="user-profile">                    <div class="row form-group">                        <div class="col-xs-4 user-profile-title">                            <label for="user-profile-title">姓名</label>                            <input name="user-profile-title" type="text" class="form-control" placeholder="张三" />                        </div>                        <div class="col-xs-4 user-profile-no">                            <label for="user-profile-no">学号</label>                            <input name="user-profile-no" type="text" class="form-control" placeholder="3112005816" />                        </div>                        <div class="col-xs-4 user-profile-faculty">                            <label for="user-profile-isbn">学院</label>                            <input type="text" class="form-control" placeholder="计算机学院" />                        </div>                    </div>                    <div class="user-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">新增</a>                        </div>                    </div>                </form>                <div class="user-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>持书情况</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>大学数学</td>                                    <td>TP 12345</td>                                    <td>2014/10/1</td>                                    <td>2014/11/5</td>                                </tr>                                <tr>                                    <td>大学英语</td>                                    <td>TP 67890</td>                                    <td>2014/11/12</td>                                    <td>2014/12/15</td>                                </tr>                            </tbody>                        </table>                    </div>                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅记录</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>书籍名称</td>                                    <td>书籍编号</td>                                    <td>借阅时间</td>                                    <td>归还时间</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>大学数学</td>                                    <td>TP 12345</td>                                    <td>2014/9/1</td>                                    <td>2014/10/1</td>                                </tr>                            </tbody>                        </table>                    </div>                </div>'
export var readerresultrow = '<tr>    <td>        <a href="/#reader/<%= no %>"><%= name %></a>    </td>    <td><%= no %></td>    <td><%= faculty %></td></tr>'
export var bookresultrow = '<tr>    <td>        <a href="/#book/<%= no %>"><%= title %></a>    </td>    <td><%= no %></td>    <td><%= isbn %></td></tr>'
export var help = '<article class="help-article">    <h1>图书馆书籍管理系统使用帮助</h1>    <section id="article-overview" class="help-article-section">        <h3>系统概况</h3>        <p>write something...</p>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>借阅图书</h3>    </section>    <section id="article-borrow-book" class="help-article-section">        <h3>归还图书</h3>    </section>    <section id="article-enter-book" class="help-article-section">        <h3>登记图书</h3>    </section>    <section id="article-enter-user" class="help-article-section">        <h3>登记读者</h3>    </section>    <section id="article-book-profile" class="help-article-section">        <h3>图书详情</h3>    </section>    <section id="article-user-profile" class="help-article-section">        <h3>读者详情</h3>    </section></article>'
export var bookadd = '                <div class="page-header">                    <h3>图书详情</h3>                </div>                <form action="#" role="form" class="book-profile">                    <div class="row form-group">                        <div class="col-xs-8 book-profile-title">                            <label for="book-profile-title">书籍名称</label>                            <input name="book-profile-title" type="text" class="form-control" placeholder="书籍名称" />                        </div>                        <div class="col-xs-4 book-profile-no">                            <label for="book-profile-no">书籍编码</label>                            <input name="book-profile-no" type="text" class="form-control" placeholder="书籍编码" />                        </div>                    </div>                    <div class="row form-group">                        <div class="col-xs-6 book-profile-isbn">                            <label for="book-profile-isbn">ISBN 编码</label>                            <input type="text" class="form-control" placeholder="ISBN 编码" />                        </div>                    </div>                    <div class="book-profile-actions row">                        <div class="btn-group col-md-4" role="group">                            <a class="btn btn-success" href="#">借出</a>                            <a class="btn btn-success" href="#">归还</a>                            <a class="btn btn-success" href="#">新增</a>                        </div>                    </div>                </form>                <div class="book-profile-stats row">                    <div class="col-md-12">                        <div class="page-header">                            <h3>借阅情况</h3>                        </div>                        <table class="table">                            <thead>                                <tr>                                    <td>借阅时间</td>                                    <td>应归还时间</td>                                    <td>归还时间</td>                                    <td>借阅读者</td>                                </tr>                            </thead>                            <tbody>                                <tr>                                    <td>2014/10/1</td>                                    <td>2014/11/5</td>                                    <td>2014/11/10</td>                                    <td>张三</td>                                </tr>                                <tr>                                    <td>2014/11/12</td>                                    <td>2014/12/15</td>                                    <td>2014/12/1</td>                                    <td>张三</td>                                </tr>                                <tr>                                    <td>2014/12/5</td>                                    <td>2015/1/5</td>                                    <td></td>                                    <td>张三</td>                                </tr>                            </tbody>                        </table>                    </div>                </div>' }