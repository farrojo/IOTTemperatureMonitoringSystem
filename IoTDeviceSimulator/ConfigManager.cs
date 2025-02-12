using System.IO;
using Newtonsoft.Json.Linq;

public static class ConfigManager
{
    public static string GetConnectionString()
    {
        var json = File.ReadAllText("appsettings.json");
        var config = JObject.Parse(json);
        return config["IoTHubConnectionString"]?.ToString() ?? config["EventHubConnectionString"]?.ToString();
    }
}
