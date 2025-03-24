/*
 * This source file was generated by the Gradle 'init' task
 */
package proj02;

import io.opentelemetry.api.trace.Span;
import io.opentelemetry.api.trace.Tracer;
import io.opentelemetry.api.trace.TracerProvider;
import io.opentelemetry.api.trace.SpanKind;
import io.opentelemetry.api.GlobalOpenTelemetry;

import io.opentelemetry.context.Context;
import io.opentelemetry.context.ContextKey;
import io.opentelemetry.context.Scope;

//import io.opentelemetry.sdk.OpenTelemetrySdk;
//import io.opentelemetry.sdk.trace.SdkTracerProvider;
//import io.opentelemetry.sdk.trace.export.SimpleSpanProcessor;
//import io.opentelemetry.exporter.logging.LoggingSpanExporter;

import xTel.OTelEnabler;

public class App {
    public String getGreeting() {
        return "Hello World from project 02!";
    }

    private static Tracer tracer = null;

    public static void main(String[] args) {
        System.out.println(new App().getGreeting());

        var xtel = new OTelEnabler();
        var oTelApi = xtel.initializeOpenTelemetry();

        System.out.println("Starting OpenTelemetry API-only application...");
        tracer = GlobalOpenTelemetry.getTracer("my-app-proj02");

        Span parentSpan = tracer.spanBuilder("parent-operation")
                .setSpanKind(SpanKind.INTERNAL)
                .startSpan();

        try (Scope scope = parentSpan.makeCurrent()) {
            performOperation();
        } finally {
            parentSpan.end(); // End the parent span
        }

        System.out.println("Application finished execution.");
    }

    private static void performOperation() {
        // Create a child span within the active context
        Span childSpan = tracer.spanBuilder("child-operation").startSpan();
        try (Scope scope = childSpan.makeCurrent()) {
            // Simulate work
            System.out.println("Performing some work inside child operation...");
        } finally {
            childSpan.end();
        }
    }
}
