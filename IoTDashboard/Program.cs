using System;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("Dashboard IoT en ejecución...");
        await EventHubReceiver.ReceiveMessagesAsync();
    }
}
