// Calendar.

import ps from '../lib/ps';
import Todo from './todo';

export default class Calendar {

    constructor(todos) {
        this.todos = {};

        for (let i = 0; i < todos.length; i++) {
            this.addTodo(todos[i], true);
        }
    }

    addTodo(todo, silent) {
        let dueDate = todo.dueDate.toISOString();
        if (! (dueDate in this.todos)) {
            this.todos[dueDate] = [];
        }
        this.todos[dueDate].push(todo);

        silent = silent || false;
        if (! silent) {
            ps.pub('model:calendar:addTodo', todo);
        }

        return this;
    }

    getTodos(date) {
        return this.todos[date.toISOString()] || [];
    }

    serialize() {
        let todos = [];
        for (let dueDate in this.todos) {
            let t = this.todos[dueDate];
            for (let i = 0; i < t.length; i++) {
                todos.push(t[i].serialize());
            }
        }
        return todos;
    }

    static restore(src) {
        let todos = [];
        for (let i = 0; i < src.length; i++) {
            todos.push(Todo.restore(src[i]));
        }

        return new Calendar(todos);
    }

}
