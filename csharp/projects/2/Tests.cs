using System;

using Contact.Model;
using Contact.Model.Manager;

namespace Contact.Tests
{
    class TestContactModelManager
    {
        protected String TestFile = "/tmp/contact.manager.xml";

        public TestContactModelManager TestDumpAndRestore()
        {
            var manager = CreateManager();
            manager.Dump();

            var anotherManager = CreateManager();
            anotherManager.Restore();

            Assert.Test(manager.Contacts.Count ==
                    anotherManager.Contacts.Count);

            return this;
        }

        public TestContactModelManager TestCreateUser()
        {
            var manager = CreateManager();
            var username = "test";
            var role = User.UserRole.Readable;

            var user = manager.CreateUser(username, role);
            Assert.Test(user.Username == username);
            Assert.Test(user.Role == role);

            return this;
        }

        public TestContactModelManager TestAddUser()
        {
            var manager = CreateManager();
            var user = manager.CreateUser("test", User.UserRole.Admin);
            manager.AddUser(user);

            Assert.Test(manager.Users.Count == 1);

            return this;
        }

        public TestContactModelManager TestCreateContact()
        {
            var manager = CreateManager();
            var name = "test";
            var gender = ContactUser.ContactGender.Male;
            var address = "test street";
            var birthday = new DateTime(1993, 1, 1);
            var company = "test company";
            var mobile = "test mobile phone";
            var contact = manager.CreateContact(
                name,
                gender,
                address,
                birthday,
                company,
                mobile
            );

            Assert.Test(contact.Name == name);
            Assert.Test(contact.Gender == gender);
            Assert.Test(contact.Address == address);
            Assert.Test(contact.Birthday == birthday);
            Assert.Test(contact.Company == company);
            Assert.Test(contact.Mobile == mobile);

            return this;
        }

        protected TestContactModelManager TestAddContact()
        {
            var manager = CreateManager();
            var name = "test";
            var gender = ContactUser.ContactGender.Male;
            var address = "test street";
            var birthday = new DateTime(1993, 1, 1);
            var company = "test company";
            var mobile = "test mobile phone";
            var contact = manager.CreateContact(
                name,
                gender,
                address,
                birthday,
                company,
                mobile
            );

            manager.AddContact(contact);
            
            Assert.Test(manager.Contacts.Count == 1);

            return this;
        }

        protected TestContactModelManager TestRemoveContact()
        {
            var manager = CreateManager();
            var name = "test";
            var gender = ContactUser.ContactGender.Male;
            var address = "test street";
            var birthday = new DateTime(1993, 1, 1);
            var company = "test company";
            var mobile = "test mobile phone";
            var contact = manager.CreateContact(
                name,
                gender,
                address,
                birthday,
                company,
                mobile
            );

            Assert.Test(manager.RemoveContact(contact) == false);
            
            manager.AddContact(contact);
            Assert.Test(manager.RemoveContact(contact));

            return this;
        }

        protected TestContactModelManager TestFindContact()
        {
            var manager = CreateManager();
            var name = "test";
            var gender = ContactUser.ContactGender.Male;
            var address = "test street";
            var birthday = new DateTime(1993, 1, 1);
            var company = "test company";
            var mobile = "test mobile phone";
            var contact = manager.CreateContact(
                name,
                gender,
                address,
                birthday,
                company,
                mobile
            );

            Assert.Test(manager.FindContact(x => x.Name == name) == null);

            manager.AddContact(contact);
            Assert.Test(manager.FindContact(x => x.Name == name) == contact);

            return this;
        }

        protected TestContactModelManager TestCreateComment()
        {
            var manager = CreateManager();
            var name = "test";
            var gender = ContactUser.ContactGender.Male;
            var address = "test street";
            var birthday = new DateTime(1993, 1, 1);
            var company = "test company";
            var mobile = "test mobile phone";
            var contact = manager.CreateContact(
                name,
                gender,
                address,
                birthday,
                company,
                mobile
            );

            var content = "test";
            var comment = manager.CreateComment(contact, content);

            Assert.Test(comment.Content == content);
            Assert.Test(comment.CreatedAt == DateTime.Today);

            return this;
        }

        protected ContactManager CreateManager(String file = null)
        {
            if (file == null)
            {
                file = TestFile;
            }

            return new ContactManager(file);
        }

        public static void Test()
        {
            var test = new TestContactModelManager();

            test.TestDumpAndRestore()
                .TestCreateUser()
                .TestAddUser()
                .TestCreateContact()
                .TestAddContact()
                .TestRemoveContact()
                .TestFindContact()
                .TestCreateComment();
        }
    }
    
    public class Tests
    {
        public static void Main(string[] args)
        {
            TestContactModelManager.Test();
        }
    }
}
