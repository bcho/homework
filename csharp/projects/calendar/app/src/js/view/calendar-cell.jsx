import React from 'react';

import TodoModel from '../model/todo';
import calendarManager from '../manager/calendar';


let weekDayNames = [
    'sunday', 'monday', 'tuesday', 'wednesday', 'thrusday', 'frieday',
    'saturday'
];

let TodoItem = React.createClass({

    render: function() {
        return <li className="calendar-todo">{this.props.todo.content}</li>
    }

});

let AddTodoItem = React.createClass({

    getInitialState: function() {
        return {
            showDialog: false,
            content: ''
        };
    },

    showDialog: function() {
        this.setState({showDialog: true});
    },

    addTodo: function() {
        let content = this.state.content;
        calendarManager.addTodo(new TodoModel(content, this.props.date));

        // FIXME anti-pattern
        this.props.todos.forceUpdate();
        this.setState({
            showDialog: false,
            content: ''
        });
    },

    updateContent: function(e) {
        this.setState({content: e.target.value});
    },

    render: function() {
        let dialogClassName = [
            'calendar-todo-dialog',
            this.state.showDialog ? '' : 'hide'
        ].join(' ');
        return (
            <li className="calendar-todo">
                <a href="#" onClick={this.showDialog}>add</a>
                <div className={dialogClassName}>
                    <h4 className="calendar-todo-dialog-header">Add todo</h4>
                    <form>
                        <div className="form-control">
                            <input type="text" name="content" value={this.state.content} onChange={this.updateContent}/>
                        </div>
                        <div className="form-control">
                            <a href="#" onClick={this.addTodo}>add</a>
                        </div>
                    </form>
                </div>
            </li>
        );
    }

});

let Todos = React.createClass({

    render: function() {
        let todos = calendarManager.getTodos(this.props.date);
        return (
            <ul className="calendar-todos">
                {todos.map(function(todo, i) {
                    return <TodoItem todo={todo} key={i} />
                })}
                <AddTodoItem date={this.props.date} todos={this} />
            </ul>
        );
    }

});

let CalendarCell = React.createClass({
    
    render: function() {
        let weekDay = weekDayNames[this.props.date.getDay()],
            className = `calendar-cell ${weekDay}`;

        return (
            <td className={className}>
                <h3 className="calendar-date">
                    {this.props.date.getDate()}
                </h3>
                <Todos date={this.props.date} />
            </td>
        );
    }

});

export default CalendarCell;
