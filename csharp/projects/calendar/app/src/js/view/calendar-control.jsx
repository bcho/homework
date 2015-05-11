import React from 'react';

let monthNames = [
    'January', 'February', 'March', 'April', 'May', 'June',
    'July', 'Auguest', 'September', 'October', 'November', 'December'
];

let CalendarControl = React.createClass({

    jumpToPrevMonth: function() {
        let year = this.props.date.getFullYear(),
            month = this.props.date.getMonth();
        if (month == 0) {
            year = year - 1;
            month = 12;
        }
        this.props.calendar.setDate(year, month);
    },

    jumpToNextMonth: function() {
        let year = this.props.date.getFullYear(),
            month = this.props.date.getMonth() + 2;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
        this.props.calendar.setDate(year, month);
    },

    jumpToToday: function() {
        let date = new Date();
        this.props.calendar.setDate(
            date.getFullYear(),
            date.getMonth() + 1
        );
    },

    render: function() {
        let month = monthNames[this.props.date.getMonth()],
            year = this.props.date.getFullYear();
        return (
            <header className="calendar-control">
                <div className="calendar-navigate">
                    <a className="calendar-navigate-btn" onClick={this.jumpToPrevMonth}>﹤</a>
                    <a className="calendar-navigate-btn" onClick={this.jumpToToday}>Today</a>
                    <a className="calendar-navigate-btn" onClick={this.jumpToNextMonth}>﹥</a>
                </div>
                <h1 className="calendar-now-date">
                    <span className="month">{month}</span>
                    &nbsp;<span className="year">{year}</span>
                </h1>
            </header>
        );
    }

})

export default CalendarControl;
