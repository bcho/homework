import Calendar from '../../model/calendar';
import Todo from '../../model/todo';

describe('model:calendar', function() {

    it('should serialize and restore correctly', function() {
        let todos = [
            new Todo('test', new Date()),
            new Todo('test', new Date())
        ],
            calendar = new Calendar(todos);

        let serialized = calendar.serialize();
        serialized.length.should.be.exactly(todos.length);
        
        let restoredCalendar = Calendar.restore(serialized);
        restoredCalendar.serialize().length.should.be.exactly(todos.length);
    });

    it('should add a new todo', function() {
        let date = new Date(),
            todo = new Todo('test', date),
            calendar = new Calendar([]);

        calendar.addTodo(todo).should.be.exactly(calendar);
        calendar.todos[date.toISOString()].length.should.be.exactly(1);
    });

    it ('should get todo for specify date', function() {
        let date = new Date(),
            todo = new Todo('test', date),
            calendar = new Calendar([todo]);

        calendar.getTodos(date)[0].should.be.exactly(todo);
    });

});
