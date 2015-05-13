using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

using Todo.Model;

namespace Todo.Model.Manager
{
    public class TodoManager
    {
        public class Document
        {
            public List<Todo> Todos;

            public Document()
            {
                Todos = new List<Todo>();
            }
        }

        public String Fielname { get; protected set; }
        public List<Todo> Todos {
            get { return Data.Todos; }
            set { Data.Todos = value; }
        }
        protected Document Data;

        public TodoManager(String filename)
        {
            Filename = filename;
            Data = new Document();

            if (File.Exists(Filename))
            {
                Restore();
            }
            else
            {
                Dump();
            }
        }

        public TodoManager Dump()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Document));
            TextWriter writer = new StreamWriter(Filename);
            serializer.Serialize(writer, Data);
            writer.Close();

            return this;
        }

        public TodoManager Restore()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Document));
            FileStream fs = new FileStream(Filename, FileMode.Open);
            Data = (Document) serializer.Deserialize(fs);
            fs.Close();

            return this;
        }

        public Todo AddTodo(String content, DateTime dueDate)
        {
            var todo = new Todo();
            todo.Content = content;
            todo.DueDate = dueDate;

            Todos.Add(todo);
        }

        public List<Todo> GetTodoByDueDate(DateTime dueDate)
        {
            var todosAtThisDate = new List<Todo>();
            foreach (var todo in Todos)
            {
                if (todo.DueDate == dueDate)
                {
                    todosAtThisDate.Add(todo);
                }
            }
            return todosAtThisDate;
        }
    }
}
