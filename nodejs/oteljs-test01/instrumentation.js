/*instrumentation.js*/
// Require dependencies
const { NodeSDK } = require('@opentelemetry/sdk-node');
const { ConsoleSpanExporter } = require('@opentelemetry/sdk-trace-node');

const { diag, DiagConsoleLogger, DiagLogLevel } = require('@opentelemetry/api');

// Set the logger and log level
diag.setLogger(new DiagConsoleLogger(), DiagLogLevel.DEBUG);

const {
    getNodeAutoInstrumentations,
} = require('@opentelemetry/auto-instrumentations-node');

const {
    PeriodicExportingMetricReader,
    ConsoleMetricExporter,
} = require('@opentelemetry/sdk-metrics');

const sdk = new NodeSDK({
    traceExporter: new ConsoleSpanExporter(),
    metricReader: new PeriodicExportingMetricReader({
        exporter: new ConsoleMetricExporter(),
    }),
    instrumentations: [getNodeAutoInstrumentations()],
});

sdk.start();


async function shutdown() {
    try {
        await sdk.shutdown();
        diag.debug('OpenTelemetry SDK terminated');
    } catch (error) {
        diag.error('Error terminating OpenTelemetry SDK', error);
    }
}

// Gracefully shutdown SDK if a SIGTERM is received
process.on('SIGTERM', shutdown);

// Gracefully shutdown SDK if Node.js is exiting normally
process.once('beforeExit', shutdown);

