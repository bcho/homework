// todo item.

export default class Todo {
    
    constructor(content, dueDate) {
        this.content = content;
        this.dueDate = dueDate;
    }

    serialize() {
        return {
            content: this.content,
            dueDate: this.dueDate.toISOString()
        };
    }

    static restore(src) {
        return new Todo(src['content'], new Date(src['dueDate']));
    }

}
