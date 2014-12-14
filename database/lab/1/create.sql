use SC;

create table department (
    dno char(6),
    dept_name char(20) not null,
    header char(8),

    primary key(dno)
);

create table speciality (
    spno char(8),
    dno char(6) not null,
    spname char(20) not null,

    primary key(spno),
    foreign key(dno) references department(dno)
);

create table student (
    s_no char(8),
    sname char(8) not null,
    sex char(2),
    sbirthday smalldatetime,
    dno char(6),
    spno char(8),
    class_no char(4),

    primary key(s_no),
    foreign key(dno) references department(dno),
    foreign key(spno) references speciality(spno)
);

create table course (
    cno char(10),
    cname char(20) not null,
    spno char(8),
    ctno tinyint,       /* 0 for 必修，1 for 选修 */
    lecture tinyint,
    experiment tinyint,
    semester tinyint,
    credit tinyint,

    primary key(cno),
    foreign key(spno) references speciality(spno)
);

create table student_course (
    s_no char(8),
    tcid smallint,          /* references course? */
    score tinyint,

    primary key(s_no, tcid),
    foreign key(s_no) references student(s_no) on delete cascade
);

create table teacher (
    t_no char(8),
    t_name char(8) not null,
    t_sex char(2),
    t_birthday smalldatetime,
    dno char(6),
    teach_title char(10),

    primary key(t_no),
    foreign key(dno) references department(dno)
);

create table teacher_course (
    tcid smallint,
    t_no char(8),
    spno char(8),
    class_no char(4),
    cno char(10) not null,
    semester char(6),
    schoolyear char(10),

    primary key(tcid),
    foreign key(t_no) references teacher(t_no),
    foreign key(spno) references speciality(spno),
    foreign key(cno) references course(cno)
);

create table class (
    spno char(8),
    class_no char(4),
    header char(8),

    primary key(spno, class_no),
    foreign key(spno) references speciality(spno)
);
