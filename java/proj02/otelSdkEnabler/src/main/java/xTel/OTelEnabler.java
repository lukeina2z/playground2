package xTel;

import io.opentelemetry.api.GlobalOpenTelemetry;
import io.opentelemetry.api.OpenTelemetry;
import io.opentelemetry.api.common.AttributeKey;
import io.opentelemetry.api.logs.Severity;
import io.opentelemetry.api.trace.Span;

import io.opentelemetry.context.Scope;

// import io.opentelemetry.exporter.otlp.logs.OtlpGrpcLogRecordExporter;

import io.opentelemetry.sdk.OpenTelemetrySdk;
import io.opentelemetry.sdk.logs.SdkLoggerProvider;
import io.opentelemetry.sdk.logs.export.BatchLogRecordProcessor;
import io.opentelemetry.sdk.resources.Resource;
import io.opentelemetry.sdk.trace.export.BatchSpanProcessor;
import io.opentelemetry.sdk.trace.export.SimpleSpanProcessor;
// import io.opentelemetry.sdk.trace.export.SpanExporter;
import io.opentelemetry.sdk.trace.samplers.Sampler;
import io.opentelemetry.sdk.trace.SdkTracerProvider;

import io.opentelemetry.exporter.logging.LoggingSpanExporter;
import io.opentelemetry.exporter.otlp.http.trace.OtlpHttpSpanExporter;
import io.opentelemetry.exporter.otlp.http.trace.OtlpHttpSpanExporterBuilder;

import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

public class OTelEnabler {
  public OpenTelemetry initializeOpenTelemetry() {

    OtlpHttpSpanExporterBuilder httpBuilder = OtlpHttpSpanExporter.builder();
    httpBuilder.setEndpoint("http://localhost:4318/v1/traces");

    SdkTracerProvider tracerProvider = SdkTracerProvider.builder()
        .addSpanProcessor(SimpleSpanProcessor.create(LoggingSpanExporter.create()))
        .addSpanProcessor(SimpleSpanProcessor.create(httpBuilder.build()))
        .setSampler(Sampler.alwaysOn()) // Enables tracing for all requests
        .build();

    OpenTelemetrySdk openTelemetry = OpenTelemetrySdk.builder()
        .setTracerProvider(tracerProvider)
        .build();

    // Add shutdown hook to close tracer provider
    Runtime.getRuntime().addShutdownHook(new Thread(tracerProvider::shutdown));

    // Set OpenTelemetry globally so other parts of the app can access it
    GlobalOpenTelemetry.set(openTelemetry);
    return openTelemetry;
  }
}
