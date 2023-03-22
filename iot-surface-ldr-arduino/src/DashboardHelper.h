//
// Created by Max on 22.03.23.
//

#ifndef SS2023_IOT_SURFACE_LDR_FRONTEND_H
#define SS2023_IOT_SURFACE_LDR_FRONTEND_H

const char *dashboard_header = "\
    HTTP/1.1 200 OK\n\
    Content-Type: text/html; charset=UTF-8\n\
    Connection: close\n";

const char *dashboard_content = "<!DOCTYPE html>\
    <html>\
    <head>\
        <title>IoT Surface LDR</title>\
        <script src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/4.2.1/chart.umd.min.js\"></script>\
        <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.5.0/semantic.min.css\">\
    </head>\
    <body>\
        <div class=\"ui container\">\
            <h1>IoT Surface LDR Dashboard</h1>\
            <button class=\"ui fluid button primary\" style=\"margin: 1rem\">Start Measurement</button>\
            <canvas id=\"mainChart\"></canvas>\
        </div>\
        <script>\
            const canvas = document.getElementById(\"mainChart\");\
            \
            new Chart(canvas, {\
                type: \"bar\",\
                data: {\
                    labels: [\"Red\", \"Blue\", \"Green\"],\
                    datasets: [{\
                        label: \"Values\",\
                        data: [12, 19, 3],\
                        borderWidth: 1\
                    }]\
                },\
                options: {\
                    scales: {\
                        y: {\
                            beginAtZero: true\
                        }\
                    }\
                }\
            });\
        </script>\
    </body>\
    </html>";

#endif //SS2023_IOT_SURFACE_LDR_FRONTEND_H