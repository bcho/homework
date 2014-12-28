PRAGMA foreign_keys = ON;

create table book(
    no string primary key,
    title string,
    isbn string unique,
    category string,
    description text,
    created_at timestamp default (CURRENT_TIMESTAMP),
    updated_at timestamp
);

create table user(
    no string primary key,
    name string,
    gender string,
    faculty string,
    created_at timestamp default (CURRENT_TIMESTAMP),
    updated_at timestamp
);

create table book_borrowing_log(
    id integer primary key,
    book_no string references book(no) on delete restrict on update cascade,
    user_no string references user(no) on delete restrict on update cascade,
    expire_at date,
    returned_at date,
    borrowed_at date default (CURRENT_DATE)
);
