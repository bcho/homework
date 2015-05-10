import Todo from '../../model/todo';

describe('model:todo', function() {

    it('should serialize and restore correctly', function() {
        let expectedContent = 'test',
            expectedDate = new Date(),
            todo = new Todo(expectedContent, expectedDate);

        let serialized = todo.serialize();
        serialized.content.should.be.exactly(expectedContent);
        serialized.dueDate.should.be.exactly(expectedDate.toISOString());

        let restoredTodo = Todo.restore(serialized);
        restoredTodo.content.should.be.exactly(todo.content);
        restoredTodo.dueDate.toISOString()
            .should.be.exactly(todo.dueDate.toISOString());
    });

});
