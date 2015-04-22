using System;
using System.Collections.Generic;

namespace Contact.Model
{
    // System user.
    public class User
    {
        public enum UserRole { Illegal, Readable, Writeable, Admin }

        public UserRole Role { get; set; }
        public String Username { get; set; }

        public User()
        {
            Role = UserRole.Illegal;
            Username = "";
        }

        public User(String username, UserRole role)
        {
            Role = role;
            Username = username;
        }
    }

    // Contact item.
    public class ContactUser
    {
        public enum ContactGender { Male, Female }

        public String Name { get; set; }
        public ContactGender Gender { get; set; }
        public String Address { get; set; }
        public DateTime Birthday { get; set; }
        public String Company { get; set; }
        public String Mobile { get; set; }
        public List<ContactUserComment> Comments { get; set; }

        public ContactUser()
        {
            Comments = new List<ContactUserComment>();
        }
    }

    // Contact item comment.
    public class ContactUserComment
    {
        public String Content { get; set; }
        public DateTime CreatedAt { get; set; }
        public DateTime UpdatedAt { get; set; }
    }
}
