import React from 'react';

let monthNames = [
    'January', 'February', 'March', 'April', 'May', 'June',
    'July', 'Auguest', 'September', 'October', 'November', 'December'
];

let CalendarControl = React.createClass({

    render: function() {
        let month = monthNames[this.props.date.getMonth()],
            year = this.props.date.getFullYear();
        return (
            <header className="calendar-control">
                <h1 className="calendar-now-date">
                    <span className="month">{month}</span>
                    &nbsp;<span className="year">{year}</span>
                </h1>
            </header>
        );
    }

})

export default CalendarControl;
