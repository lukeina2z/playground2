using System.Globalization;

using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", () =>
{
    string s1 = "Hello World!";
    string s2 = " Hello again!!!";
    return s1 + s2;
});

app.MapGet("/rolldice/{player?}", HandleRollDice);

string HandleRollDice([FromServices]ILogger<Program> logger, string? player)
{
    var result = RollDice();

    if (string.IsNullOrEmpty(player))
    {
        logger.LogInformation("Anonymous player is rolling the dice: {result}", result);
    }
    else
    {
        logger.LogInformation("{player} is rolling the dice: {result}", player, result);
    }

    return result.ToString(CultureInfo.InvariantCulture);
}

int RollDice()
{
    return Random.Shared.Next(1, 7);
}

app.Run();
