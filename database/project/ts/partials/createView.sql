create view not_returned_book as select book.* from book join book_borrowing_log `log` on `log`.book_no = book.no where `log`.returned_at is null;
