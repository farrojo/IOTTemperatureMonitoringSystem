using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.EventHubs;
using Newtonsoft.Json;
using IoTDashboard.Models;

public static class EventHubReceiver
{
    private static readonly string eventHubConnectionString = ConfigManager.GetConnectionString();
    private static readonly EventHubClient eventHubClient = EventHubClient.CreateFromConnectionString(eventHubConnectionString);

    public static async Task ReceiveMessagesAsync()
    {
        var runtimeInfo = await eventHubClient.GetRuntimeInformationAsync();
        var partitions = runtimeInfo.PartitionIds;

        foreach (var partition in partitions)
        {
            ReceiveMessagesFromPartition(partition);
        }
    }

    private static async void ReceiveMessagesFromPartition(string partition)
    {
        var receiver = eventHubClient.CreateReceiver("$Default", partition, EventPosition.FromEnqueuedTime(DateTime.UtcNow));
        Console.WriteLine($"Escuchando en la partición: {partition}");

        while (true)
        {
            var events = await receiver.ReceiveAsync(100);
            if (events == null) continue;

            foreach (var eventData in events)
            {
                string data = Encoding.UTF8.GetString(eventData.Body.Array);
                var telemetry = JsonConvert.DeserializeObject<TelemetryData>(data);

                Console.WriteLine($"🌡️ {telemetry.DeviceId}: {telemetry.Temperature}°C - {telemetry.Timestamp}");

                if (telemetry.Temperature > 30)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("⚠️ ALERTA: Temperatura alta detectada!");
                    Console.ResetColor();
                }
            }
        }
    }
}
