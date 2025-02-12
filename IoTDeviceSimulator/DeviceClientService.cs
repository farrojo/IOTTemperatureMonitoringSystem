using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.Devices.Client;
using Newtonsoft.Json;
using IoTDeviceSimulator.Models;

public static class DeviceClientService
{
    private static readonly string connectionString = ConfigManager.GetConnectionString();
    private static readonly DeviceClient deviceClient = DeviceClient.CreateFromConnectionString(connectionString, TransportType.Mqtt);

    public static async Task SendTelemetryDataAsync()
    {
        Random random = new Random();

        while (true)
        {
            var telemetry = new TelemetryData
            {
                DeviceId = "Sensor1",
                Temperature = Math.Round(20 + random.NextDouble() * 15, 2),
                Timestamp = DateTime.UtcNow
            };

            string messageString = JsonConvert.SerializeObject(telemetry);
            var message = new Message(Encoding.UTF8.GetBytes(messageString));

            await deviceClient.SendEventAsync(message);
            Console.WriteLine($"Datos enviados: {messageString}");

            await Task.Delay(5000); // Envía datos cada 5 segundos
        }
    }
}
