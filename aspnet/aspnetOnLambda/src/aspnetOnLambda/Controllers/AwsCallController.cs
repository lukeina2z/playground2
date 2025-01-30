using System.Diagnostics;
using System.Threading.Tasks;
using Amazon.S3;
using Microsoft.AspNetCore.Mvc;

namespace aspnetOnLambda.Controllers;

[ApiController]
[Route("[controller]")]
public class AwsCallController : ControllerBase
{
    private readonly AmazonS3Client s3Client = new AmazonS3Client();
    private readonly HttpClient httpClient = new HttpClient();

    [HttpGet]
    [Route("/outgoing-http-call")]
    public string OutgoingHttp()
    {
        _ = this.httpClient.GetAsync("https://aws.amazon.com").Result;
        return this.GetTraceId();
    }

    [HttpGet]
    [Route("/aws-sdk-call")]
    public string AwsSdkCall()
    {
        _ = this.s3Client.ListBucketsAsync().Result;
        return this.GetTraceId();
    }

    [HttpGet]
    [Route("/aws-sdk-call2")]
    public async System.Threading.Tasks.Task<IActionResult> AWSSDKCall2()
    {
        try
        {
            string retVal = this.GetTraceId();

            var tracer = LambdaEntryPoint.tracerProvider.GetTracer("my-app-x");
            // Create a span
            using (var span = tracer.StartSpan("ExampleSpan"))
            {
                Console.WriteLine("Span is being executed...");

                // Optionally, add attributes to the span
                span.SetAttribute("my-attribute", "value");

                // Simulate work being done
                // System.Threading.Thread.Sleep(1000); // Simulate some work

                retVal = this.GetTraceId();
                retVal += "\n\n";
                var result = await this.s3Client.ListBucketsAsync();
                foreach (var bucket in result.Buckets)
                {
                    retVal += bucket.BucketName;
                    retVal += "\n\n";
                }

                // Optionally, add events to the span
                span.AddEvent("Span completed");
            }

            // Return the response
            return Ok(retVal);
        }
        catch (HttpRequestException ex)
        {
            return StatusCode(500, new { message = ex.Message });
        }
    }

    private string GetTraceId()
    {
        var traceId = Activity.Current.TraceId.ToHexString();
        var version = "1";
        var epoch = traceId.Substring(0, 8);
        var random = traceId.Substring(8);
        return "{" + "\"traceId\"" + ": " + "\"" + version + "-" + epoch + "-" + random + "\"" + "}";
    }
}
