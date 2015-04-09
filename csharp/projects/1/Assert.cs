using System;

namespace CSharp.Utils
{
    class Assert
    {
        class FailedException: ApplicationException
        {
            public FailedException(string s): base(s) {}
        }

        public static void Test(bool predicate, string message = "failed")
        {
            if (predicate)
            {
                return;
            }

            Console.WriteLine(message);
            throw new FailedException(message);
        }    
    }
}
