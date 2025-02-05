using System.Diagnostics;
using System.Net.Http;

using OpenTelemetry.Exporter;
using OpenTelemetry.Logs;
using OpenTelemetry.Metrics;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;


var builder = WebApplication.CreateBuilder(args);

// Register the Instrumentation class as a singleton in the DI container.
builder.Services.AddSingleton<Instrumentation>();

const string serviceName = "OTel-AspNet-Svc";
const string serviceVer = "1.1.0.0";

// builder.Logging.AddOpenTelemetry(options =>
//    {
//         options.SetResourceBuilder(
//         OpenTelemetry.Resources.ResourceBuilder.CreateDefault().AddService(
//                 serviceName: serviceName,
//                 serviceVersion: serviceVer))
//             .AddOtlpExporter()
//             .AddConsoleExporter();
//    });

const string LocalCollectorUrl = "http://localhost:4318";

builder.Services.AddOpenTelemetry()
    .ConfigureResource(resource => resource.AddService(serviceName))
    // .WithMetrics(metrics => metrics
    //     .AddAspNetCoreInstrumentation()
    //     .AddOtlpExporter()
    //     .AddConsoleExporter())
    .WithTracing(tracing => tracing
        .AddSource(Instrumentation.ActivitySourceName)
        .SetSampler(new AlwaysOnSampler())
        .AddHttpClientInstrumentation()
        .AddAspNetCoreInstrumentation()
        // .AddOtlpExporter()
        .AddOtlpExporter(options =>
        {
            options.Endpoint = new Uri(LocalCollectorUrl + "/v1/traces");
            options.Protocol = OtlpExportProtocol.HttpProtobuf;
        })
        .AddConsoleExporter());


builder.Services.AddControllers();

var app = builder.Build();

app.MapGet("/", () =>
{
    string s1 = "Hello World!";
    string s2 = " Hello again!!!";
    return s1 + s2;
});

var httpClient = new HttpClient();

app.MapGet("/pingaws", async () =>
{
    Instrumentation instru = new Instrumentation();
    using var activityParentOne = instru.ActivitySource.StartActivity("ping AWS");
    var html = await httpClient.GetStringAsync("https://aws.amazon.com/");
    if (string.IsNullOrWhiteSpace(html))
    {
        return "Hello, World!";
    }
    else
    {
        return html;
    }
});

app.MapControllers();

app.Run();
