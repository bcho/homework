import storage from '../lib/storage';

import ps from '../lib/ps';
import CalendarModel from '../model/calendar';

const cacheKey = 'calendar';
let cached = storage.restore(cacheKey) || [];

let calendar = CalendarModel.restore(cached);

ps.sub('model:calendar:addTodo', function() {
    storage.store(cacheKey, calendar);
});


export default calendar;
