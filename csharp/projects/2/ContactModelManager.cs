using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

using Contact.Model;

namespace Contact.Model.Manager
{
    // Records manager.
    public class ContactManager
    {
        public class Document
        {
            public List<User> Users;
            public List<ContactUser> Contacts;

            public Document()
            {
                Users = new List<User>();
                Contacts = new List<ContactUser>();
            }
        }

        public String Filename { get; protected set; }
        public List<User> Users {
            get { return Data.Users; }
            set { Data.Users = value; }
        }
        public List<ContactUser> Contacts {
            get { return Data.Contacts; }
            set { Data.Contacts = value; }
        }
        protected Document Data;

        public ContactManager(String filename)
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

        // Write to file.
        public ContactManager Dump()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Document));
            TextWriter writer = new StreamWriter(Filename);
            serializer.Serialize(writer, Data);
            writer.Close();

            return this;
        }

        // Restore from file.
        public ContactManager Restore()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Document));
            FileStream fs = new FileStream(Filename, FileMode.Open);
            Data = (Document) serializer.Deserialize(fs);
            fs.Close();

            return this;
        }

        public User CreateUser(
                String username,
                User.UserRole role = User.UserRole.Readable
        ) {
            return new User(username, role);
        }

        public ContactManager AddUser(User user)
        {
            Users.Add(user);

            return this;
        }

        public ContactUser CreateContact(
                String name,
                ContactUser.ContactGender gender,
                String address,
                DateTime birthday,
                String company,
                String mobile
        ) {
            var contact = new ContactUser();
            contact.Name = name;
            contact.Gender = gender;
            contact.Address = address;
            contact.Birthday = birthday;
            contact.Company = company;
            contact.Mobile = mobile;

            return contact;
        }

        public ContactManager AddContact(ContactUser contact)
        {
            Contacts.Add(contact);

            return this;
        }

        public bool RemoveContact(ContactUser contact)
        {
            return Contacts.Remove(contact);
        }

        public ContactUser FindContact(Predicate<ContactUser> match)
        {
            return Contacts.Find(match);
        }

        public ContactUserComment CreateComment(
                ContactUser contact,
                String content
        ) {
            var comment = new ContactUserComment();
            comment.Content = content;
            comment.CreatedAt = DateTime.Today;
            contact.Comments.Add(comment);

            return comment;
        }
    }
}
