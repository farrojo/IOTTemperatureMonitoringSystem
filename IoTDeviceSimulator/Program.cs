using System;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("Simulador de dispositivo IoT iniciado...");
        await DeviceClientService.SendTelemetryDataAsync();
    }
}
