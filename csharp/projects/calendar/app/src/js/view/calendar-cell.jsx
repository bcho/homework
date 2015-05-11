import React from 'react';

let weekDayNames = [
    'sunday', 'monday', 'tuesday', 'wednesday', 'thrusday', 'frieday',
    'saturday'
];

let CalendarCell = React.createClass({
    
    render: function() {
        let weekDay = weekDayNames[this.props.date.getDay()],
            className = `calendar-cell ${weekDay}`;

        return (
            <td className={className}>
                <h3 className="calendar-date">
                    {this.props.date.getDate()}
                </h3>
            </td>
        );
    }

});

export default CalendarCell;
