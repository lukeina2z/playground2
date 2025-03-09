#include <iostream>
#include <string>

#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"

#include "DiceServer.h"

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
    namespace otlp = opentelemetry::exporter::otlp;
    opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;

    if (argc > 1)
    {
        opts.url = argv[1];
        if (argc > 2)
        {
            std::string debug  = argv[2];
            opts.console_debug = debug != "" && debug != "0" && debug != "no";
        }

        if (argc > 3)
        {
            std::string binary_mode = argv[3];
            if (binary_mode.size() >= 3 && binary_mode.substr(0, 3) == "bin")
            {
                opts.content_type = otlp::HttpRequestContentType::kBinary;
            }
        }
    }
    else
    {
        std::cout << "Please provide OTLP HTTP endpoint." << std::endl;
        return 0;
    }

    mainDiceServer(opts);

    // if (opts.console_debug)
    // {
    //     internal_log::GlobalLogHandler::SetLogLevel(internal_log::LogLevel::Debug);
    // }

    // InitTracer();

    // foo_library();

    // CleanupTracer();
}