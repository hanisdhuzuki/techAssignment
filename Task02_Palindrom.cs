using System;

class Program
{
    static void Main()
    {
        string inputString;
        string trashSymbolsString;

        Console.Write("InputString: ");
        inputString = Console.ReadLine();

        Console.Write("TrashSymbolsString: ");
        trashSymbolsString = Console.ReadLine();

        // Convert inputString to lowercase to avoid case-sensitive strings.
        inputString = inputString.ToLower();

        // Create a temporary string for comparison.
        string temp = "";

        // If any trash is present, it will not be added to the temporary string.
        foreach (char c in inputString)
        {
            if (trashSymbolsString.Contains(c.ToString()))
            {
                continue;
            }
            else
            {
                temp += c; // Store input after removing trash.
            }
        }

        // Check if the temporary string is a palindrome after removing trash.
        char[] tempArray = temp.ToCharArray();
        Array.Reverse(tempArray);
        string reversedTemp = new string(tempArray);
        if (temp == reversedTemp)
        {
            Console.WriteLine("true");
        }
        else
        {
            Console.WriteLine("false");
        }
    }
}
