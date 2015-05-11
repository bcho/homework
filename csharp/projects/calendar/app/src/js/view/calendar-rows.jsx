import React from 'react';

import CalendarCell from './calendar-cell.jsx';
import Cal from '../lib/cal';


let CalendarRow = React.createClass({

    render: function() {
        return (
            <tr className='calendar-row'>
            {this.props.dates.map(function(date, i) {
                return <CalendarCell date={date} key={i} />
            })}
            </tr>
        );
    }

});


let CalendarRows = React.createClass({

    render: function() {
        let month = this.props.date.getMonth() + 1,
            year = this.props.date.getFullYear(),
            calendar = Cal.getCalendar(year, month);

        return (
            <table className="calendar-cells">
                <thead>
                    <tr className="calendar-row calendar-row-header">
                        <th className="calendar-cell">Sun</th>
                        <th className="calendar-cell">Mon</th>
                        <th className="calendar-cell">Tue</th>
                        <th className="calendar-cell">Wed</th>
                        <th className="calendar-cell">Thu</th>
                        <th className="calendar-cell">Fri</th>
                        <th className="calendar-cell">Sat</th>
                    </tr>
                </thead>
                <tbody>
                {calendar.map(function(row, i) {
                    return <CalendarRow dates={row} key={i} />;
                })}
                    <tr className="calendar-row"></tr>
                </tbody>
            </table>
        );
    }

});

export default CalendarRows;
