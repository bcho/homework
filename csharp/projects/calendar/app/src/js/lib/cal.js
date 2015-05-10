// Calendar.

let monthDays = {
    true: [
        31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    ],
    false: [
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    ]
}

// - month offset starts at 0 (same as `Date`).
export default {

    // { 1: [Date...], 2: [ate...], ... }
    getYear: function(year) {
        let years = {};

        for (let month = 1; month <= 12; month++) {
            years[month] = this.getMonth(year, month);
        }

        return years;
    },

    // [Date...]
    getMonth: function(year, month) {
        let date = new Date(`${year} ${month}`),
            thisMonth = monthDays[this.isLeap(year)][month - 1],
            days = [];

        for (let i = 1; i <= thisMonth; i++) {
            date.setDate(i);
            days.push(new Date(date));
        }

        return days;
    },

    isLeap: function(year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

};
