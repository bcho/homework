insert into book_borrowing_log
    (book_no, user_no, expire_at, created_at, returned_at)
values
    ("E0094868", "3112005816", CURRENT_TIMESTAMP + 1000, CURRENT_TIMESTAMP, null),
    ("E0094868", "3112005817", CURRENT_TIMESTAMP + 8000, CURRENT_TIMESTAMP, null),
    ("A1840127", "3112005816", CURRENT_TIMESTAMP + 1000, CURRENT_TIMESTAMP, null);
