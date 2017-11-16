#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main()
{
  uWS::Hub h;

  PID pid;
  PID throttle_pid;
  // TODO: Initialize the pid variable.
  // Kp: 0.798209 Kd: 9.08019 Ki: 0.0001981
  // pid.Init(0.4, 0.0002, 15.0, 0.1, 0.00005, 1.0, 2100);
  pid.Init(0.798209, 0.0001981, 9.08019, 0.1, 0.00005, 1.0, 2100);
  // throttle_pid.Init(0.5, 0.0, 4, 0.1, 0.001, 1.0, 200);

  h.onMessage([&pid, &throttle_pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());
          double steer_value;
          double throttle;
          /*
          * TODO: Calcuate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */
          pid.UpdateError(cte);
          steer_value = pid.TotalError();
          if (steer_value > 1) {
            steer_value = 1;
          } else if (steer_value < -1) {
            steer_value = -1;
          }

          // double speed_coeff = -2.801120448;
          // double speed_offset = 80.02801120448;
          // if (fabs(angle) < 0.001) {
            // angle = 0.001;
          // }
          // double req_speed = speed_coeff * fabs(angle) + speed_offset;
          // double speed_cte = speed - req_speed;

          // throttle_pid.UpdateError(speed_cte);
          // throttle = throttle_pid.TotalError();
          // if (throttle > 0.8) {
            // throttle = 0.8;
          // } else if (throttle < 0.1) {
            // throttle = 0.1;
          // }

          // std::cout << angle << " " << throttle << " " << speed_cte << " " << req_speed << std::endl;
          // std::cout << throttle_pid.Kp << " " << throttle_pid.Kd << " " << throttle_pid.Ki << std::endl;
          throttle = 0.3;
          // DEBUG
          // if (pid.counter == pid.max_count || true) {
            // std::cout << pid.loop_num << " - " << pid.counter << " - CTE: " << cte;
            // std::cout << " Total CTE: " << pid.total_abs_cte << " Best CTE: " << pid.best_total_cte << std::endl;
            // // std::cout << " Steering Value: " << steer_value << std::endl;
            // // std::cout << pid.Kp << " " << pid.Kd << " " << pid.Ki << std::endl;
          // }
          // std::cout << speed << std::endl;
          // std::cout << angle << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle;  // 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          // std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
