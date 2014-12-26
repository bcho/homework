module sqlQuery {
 export var createtable = 'create table book(    no string,    title string,    isbn string,    category string,    description text,    created_at timestamp default (CURRENT_TIMESTAMP),    updated_at timestamp,    primary key(no),    unique(isbn));create table user(    no string,    name string,    gender string,    faculty string,    created_at timestamp default (CURRENT_TIMESTAMP),    updated_at timestamp,    primary key(no));create table book_borrowing_log(    id integer auto increment,    book_no string,    user_no string,    expire_at date,    returned_at date,    borrowed_at date default (CURRENT_DATE),    primary key(id),    foreign key(book_no) references book(no),    foreign key(user_no) references user(no));'
export var initbookborrowinglog = 'insert into book_borrowing_log    (book_no, user_no, expire_at)values    ("E0094868", "3112005816", date("now", "+3 months")),    ("A1840127", "3112005816", date("now", "+3 months"));'
export var inituser = 'insert into user    (no, name, gender, faculty)values    ("3112005816", "张三", "男", "计算机学院"),    ("3112005817", "李四", "男", "计算机学院");'
export var initbook = 'insert into book    (no, title, isbn, category, description)values    ("E0094868", "A first course in database systems", "9787111247333", "", ""),    ("A0836869", "编译原理", "7302089795", "", ""),    ("A1840127", "数据库系统概论", "704007494X", "", "");' }