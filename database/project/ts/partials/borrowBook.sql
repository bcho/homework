insert into book_borrowing_log
    (user_no, book_no, expire_at)
values
    ("<%= userNo %>", "<%= bookNo %>", date("now", "+3 months"));
