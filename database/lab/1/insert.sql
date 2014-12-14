use SC;

/* department */
insert into department (dno, dept_name, header)
values ('ce', 'Computer', 'Mr. CS');

insert into department (dno, dept_name, header)
values ('in', 'Information', 'Mr. Info');

insert into department (dno, dept_name, header)
values ('en', 'English', 'Mrs. Eng');

insert into department (dno, dept_name, header)
values ('py', 'Physical', 'Mr. Phy');

insert into department (dno, dept_name, header)
values ('jp', 'Japaness', 'Mr. Jap');

/* speciality */
insert into speciality (spno, dno, spname)
values ('cs', 'ce', 'Computer Science');

insert into speciality (spno, dno, spname)
values ('se', 'ce', 'Software Engineering');

insert into speciality (spno, dno, spname)
values ('ne', 'ce', 'Network Engineering');

insert into speciality (spno, dno, spname)
values ('dm', 'ce', 'Digital Media');

insert into speciality (spno, dno, spname)
values ('be', 'en', 'Business English');

/* class */
insert into class (spno, class_no, header)
values ('cs', '1201', 'Mr. CS01');

insert into class (spno, class_no, header)
values ('cs', '1202', 'Mr. CS02');

insert into class (spno, class_no, header)
values ('se', '1201', 'Mr. SE01');

insert into class (spno, class_no, header)
values ('se', '1201', 'Mr. SE01');

insert into class (spno, class_no, header)
values ('ne', '1201', 'Mr. NE01');

/* student */
insert into student (s_no, sname, sex, sbirthday, dno, spno, class_no)
values ('120001', 'alex', 'M', '1993-01-01', 'ce', 'cs', '1202');

insert into student (s_no, sname, sex, sbirthday, dno, spno, class_no)
values ('120002', 'amy', 'F', '1993-02-01', 'ce', 'cs', '1202');

insert into student (s_no, sname, sex, sbirthday, dno, spno, class_no)
values ('120003', 'bob', 'M', '1993-03-01', 'ce', 'se', '1201');

insert into student (s_no, sname, sex, sbirthday, dno, spno, class_no)
values ('120004', 'daisy', 'F', '1993-04-01', 'ce', 'se', '1201');

insert into student (s_no, sname, sex, sbirthday, dno, spno, class_no)
values ('120005', 'alex', 'M', '1993-05-01', 'ce', 'ne', '1201');

/* course */
insert into course (cno, cname, spno, ctno, lecture, experiment, semester, credit)
values ('cs01', 'C Programming', 'cs', 0, 42, 30, 1, 2);

insert into course (cno, cname, spno, ctno, lecture, experiment, semester, credit)
values ('cs02', 'Data Structure', 'cs', 0, 42, 30, 2, 2);

insert into course (cno, cname, spno, ctno, lecture, experiment, semester, credit)
values ('cs03', 'Operating System', 'cs', 0, 30, 10, 1, 1);

insert into course (cno, cname, spno, ctno, lecture, experiment, semester, credit)
values ('cs04', 'Database', 'cs', 0, 30, 10, 1, 1);

insert into course (cno, cname, spno, ctno, lecture, experiment, semester, credit)
values ('cs05', 'Data Mining', 'cs', 1, 20, 0, 2, 1);

/* teacher */
insert into teacher (t_no, t_name, t_sex, t_birthday, dno, teach_title)
values ('t01', 'Mr. t01', 'M', '1980-01-01', 'ce', 'Proferssor');

insert into teacher (t_no, t_name, t_sex, t_birthday, dno, teach_title)
values ('t02', 'Ms. t02', 'F', '1985-02-01', 'ce', 'Lecturer');

insert into teacher (t_no, t_name, t_sex, t_birthday, dno, teach_title)
values ('t03', 'Mr. t03', 'M', '1975-01-01', 'ce', 'Professor');

insert into teacher (t_no, t_name, t_sex, t_birthday, dno, teach_title)
values ('t04', 'Ms. t04', 'F', '1965-02-01', 'ce', 'Professor');

insert into teacher (t_no, t_name, t_sex, t_birthday, dno, teach_title)
values ('t05', 'Mr. t05', 'M', '1983-01-01', 'ce', 'Lecturer');
