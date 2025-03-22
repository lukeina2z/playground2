#include <iostream>
#include <string>

#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/trace/context.h"

#include "DiceServer.h"
#include "xtrace.h"

/*
  Usage:
  - example_otlp_http
  - example_otlp_http <URL>
  - example_otlp_http <URL> <DEBUG>
  - example_otlp_http <URL> <DEBUG> <BIN>
  <DEBUG> = yes|no, to turn console debug on or off
  <BIN> = bin, to export in binary format
*/
int main(int argc, char *argv[])
{
    opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;
    if (argc > 1)
    {
        opts.url = argv[1];
        if (argc > 2)
        {
            std::string debug = argv[2];
            opts.console_debug = debug != "" && debug != "0" && debug != "no";
        }

        if (argc > 3)
        {
            std::string binary_mode = argv[3];
            if (binary_mode.size() >= 3 && binary_mode.substr(0, 3) == "bin")
            {
                opts.content_type = opentelemetry::exporter::otlp::HttpRequestContentType::kBinary;
            }
        }
    }
    else
    {
        std::cout << "Please provide OTLP HTTP endpoint." << std::endl;
        return 0;
    }

    XTrace::InitTracer(opts);
    auto tracer = XTrace::GetTracer();
    auto span = tracer->StartSpan("Main-Fn");
    
    // auto scope = tracer->WithActiveSpan(span);
    opentelemetry::v1::trace::Scope scope(span);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    mainDiceServer(opts);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    span->End();
    XTrace::CleanupTracer();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // if (opts.console_debug)
    // {
    //     internal_log::GlobalLogHandler::SetLogLevel(internal_log::LogLevel::Debug);
    // }

    // InitTracer();

    // foo_library();

    // CleanupTracer();
}