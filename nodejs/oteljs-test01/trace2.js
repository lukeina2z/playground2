const { trace } = require("@opentelemetry/api");
const { BasicTracerProvider, ConsoleSpanExporter, SimpleSpanProcessor } = require("@opentelemetry/sdk-trace-base");

// Create and register an SDK
const provider = new BasicTracerProvider({
    spanProcessors: [new SimpleSpanProcessor(new ConsoleSpanExporter())]
});
trace.setGlobalTracerProvider(provider);

// Acquire a tracer from the global tracer provider which will be used to trace the application
const name = 'my-application-name';
const version = '0.1.0';
const tracer = trace.getTracer(name, version);

let firstRun = true;

// Trace your application by creating spans
async function operation() {
    const span = tracer.startSpan("do operation");

    // mock some work by sleeping 1 second
    await new Promise((resolve, reject) => {
        let waitTime = 10000;
        if (firstRun) {
            waitTime = 100;
            firstRun = false;
        }
        setTimeout(resolve, waitTime);
    })

    span.end();
}

async function main() {
    while (true) {
        await operation();
    }
}

main();