import Calendar from '../../lib/cal';

describe('lib:calendar', function() {

    describe('isLeap', function() {
        it('should return right answer', function() {
            Calendar.isLeap(2015).should.not.be.ok;
            Calendar.isLeap(2016).should.be.ok;
            Calendar.isLeap(1900).should.not.be.ok;
            Calendar.isLeap(2000).should.be.ok;
        });
    });

    describe('getMonth', function() {
        it('should return correct days', function() {
            Calendar.getMonth(2016, 2).length.should.be.exactly(29);
            Calendar.getMonth(2015, 1).length.should.be.exactly(31);
        });
    });

    describe('getYear', function() {
        it('should return correct months', function() {
            for (var i = 1; i <= 12;i++) {
                Calendar.getYear(2015)[i].length.should.be.ok;
            }
        });
    });

});
