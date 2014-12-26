create table book(
    no string,
    title string,
    isbn string,
    category string,
    description text,
    created_at timestamp default (CURRENT_TIMESTAMP),
    updated_at timestamp,

    primary key(no),
    unique(isbn)
);

create table user(
    no string,
    name string,
    gender string,
    faculty string,
    created_at timestamp default (CURRENT_TIMESTAMP),
    updated_at timestamp,

    primary key(no)
);

create table book_borrowing_log(
    id integer auto increment,
    book_no string,
    user_no string,
    expire_at date,
    returned_at date,
    borrowed_at date default (CURRENT_DATE),

    primary key(id),
    foreign key(book_no) references book(no),
    foreign key(user_no) references user(no)
);
