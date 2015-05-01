using System;
using System.IO;
using System.Console;

using Contact.Model;
using Contact.Model.Manager;

namespace Contact.UI
{
    // Commandline interface.
    class CLI
    {
        protected String DefaultRecordsFile = @"records.xml";
        private ContactManager Manager;

        public CLI(String recordsFile)
        {
            Manager = new ContactManager(recordsFile);
        }

        public CLI()
        {
            Manager = new ContactManager(DefaultRecordsFile);

            var user = Manager.CreateUser(
                "admin",
                User.UserRole.Admin
            );
            Manager.AddUser(user);

            var contact = Manager.CreateContact(
                "小明",
                ContactUser.ContactGender.Male,
                "Earth (for now)",
                DateTime.Today,
                "GDUT",
                "13800138000"
            );
            Manager.AddContact(contact);

            var comment = Manager.CreateComment(
                contact,
                "This is a test 😀"
            );

            Manager.Dump();
        }

        public void ShowUsers()
        {
            Console.WriteLine("Users:");
            foreach (var user in Manager.Users)
            {
                Console.WriteLine("{0}", user.Username);
                Console.WriteLine("\tRole: {0}", user.Role);
            }
        }

        public void ShowContacts()
        {
            Console.WriteLine("Contacts:");
            foreach (var contact in Manager.Contacts)
            {
                Console.WriteLine();
                ShowContact(contact);
                Console.WriteLine();
            }
        }

        public void ShowContact(ContactUser contact)
        {
            Console.WriteLine("{0}\t{1}", contact.Name, contact.Mobile);
            Console.WriteLine("\tGender: {0}\tBirthday: {1}",
                    contact.Gender, contact.Birthday);
            Console.WriteLine("\tCompany: {0}\tAddress: {1}",
                    contact.Company, contact.Address);

            Console.WriteLine("\tUser Comments:");
            foreach (var comment in contact.Comments)
            {
                Console.WriteLine("\t\t{0}", comment.Content);
            }
        }

        static void Main(string[] args)
        {
            CLI cli;

            if (args.Length >= 1)
            {
                cli = new CLI(args[args.Length - 1]);
            }
            else
            {
                cli = new CLI();
            }

            cli.ShowUsers();
            cli.ShowContacts();
        }
    }
}
