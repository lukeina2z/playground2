using System.Globalization;

using Microsoft.AspNetCore.Mvc;
using OpenTelemetry.Logs;
using OpenTelemetry.Metrics;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;

var builder = WebApplication.CreateBuilder(args);

const string serviceName = "roll-dice-service";
const string serviceVer = "1.1.0.0";

builder.Logging.AddOpenTelemetry(options =>
    {
        options.SetResourceBuilder(
                OpenTelemetry.Resources.ResourceBuilder.CreateDefault().AddService(
                    serviceName: serviceName,
                    serviceVersion: serviceVer))
            .AddConsoleExporter();
    });

builder.Services.AddOpenTelemetry()
    .ConfigureResource(resource => resource.AddService(serviceName))
    .WithTracing(tracing => tracing
          .AddAspNetCoreInstrumentation()
          .AddConsoleExporter())
    .WithMetrics(metrics => metrics
          .AddAspNetCoreInstrumentation()
          .AddConsoleExporter());

builder.Services.AddControllers();

var app = builder.Build();

app.MapGet("/", () =>
{
    string s1 = "Hello World!";
    string s2 = " Hello again!!!";
    return s1 + s2;
});

app.MapControllers();

app.Run();
