import React from 'react';

import CalendarView from './view/calendar.jsx';

React.render(
    <CalendarView date={new Date()}/>,
    document.querySelector('body')
);
