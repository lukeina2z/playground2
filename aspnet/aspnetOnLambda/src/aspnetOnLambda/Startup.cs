namespace aspnetOnLambda;

public class Startup
{
    private readonly Amazon.S3.AmazonS3Client s3Client = new Amazon.S3.AmazonS3Client();

    public Startup(IConfiguration configuration)
    {
        Configuration = configuration;
    }

    public IConfiguration Configuration { get; }

    // This method gets called by the runtime. Use this method to add services to the container
    public void ConfigureServices(IServiceCollection services)
    {
        services.AddControllers();
    }

    // This method gets called by the runtime. Use this method to configure the HTTP request pipeline
    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {
        // if (env.IsDevelopment())
        {
            app.UseDeveloperExceptionPage();
        }

        app.UseHttpsRedirection();

        app.UseRouting();

        app.UseAuthorization();

        app.UseEndpoints(endpoints =>
        {
            endpoints.MapControllers();
            endpoints.MapGet("/", async context =>
            {
                _ = this.s3Client.ListBucketsAsync().Result;
                string str = this.GetTraceId()  + "\n\n Running ASP.NET Core on AWS Lambda";
                await context.Response.WriteAsync(str);
            });
        });
    }

    private string GetTraceId()
    {
        var traceId = System.Diagnostics.Activity.Current.TraceId.ToHexString();
        var version = "1";
        var epoch = traceId.Substring(0, 8);
        var random = traceId.Substring(8);
        return "{" + "\"traceId\"" + ": " + "\"" + version + "-" + epoch + "-" + random + "\"" + "}";
    }
}