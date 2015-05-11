import React from 'react';

import CalendarControl from './calendar-control.jsx';
import CalendarRows from './calendar-rows.jsx'


let Calendar = React.createClass({

    setDate: function(year, month) {
        this.setProps({'date': new Date(`${year} ${month}`)});

        return this;
    },

    render: function() {
        return (
            <div className="calendar">
                <CalendarControl date={this.props.date} calendar={this} />
                <CalendarRows date={this.props.date} />
            </div>
        );
    },

});

export default Calendar;
