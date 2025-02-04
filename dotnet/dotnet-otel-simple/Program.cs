var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", () =>
{
    string s1 = "Hello World!";
    string s2 = " Hello again!!!";
    return s1 + s2;
});

app.Run();
